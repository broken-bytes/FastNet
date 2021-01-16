#include "../Socket.hxx"

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#include "../EndPoint.hxx"

#pragma comment(lib, "Ws2_32.lib")


using namespace std::chrono;
using namespace std::chrono_literals;
namespace fastnet::internal {
	Socket::Socket(AddressFamily family, uint16_t port) {
		_family = family;
		_port = port;
		if (!isInit) {
			WSADATA data;
			int result;
			result = WSAStartup(2, &data);
			if (result != 0) {
				printf("WSAStartup failed with error: %d\n", result);
				return;
			}
		}

		Start();
	}
	Socket::~Socket() {}
	auto Socket::SetSendRate(uint8_t rate) -> void {
		_sendRate = rate;
	}

	auto Socket::SetSendBus(PacketBus* bus) -> void {
		_sendBus = std::shared_ptr<PacketBus>(bus);
	}
	auto Socket::SetReceiveBus(PacketBus* bus) -> void {
		_receiveBus = std::shared_ptr<PacketBus>(bus);
	}

	auto Socket::Send(
		const char* data,
		size_t len,
		EndPoint endpoint
	) -> void {
		sockaddr_in in{};
		in.sin_family = (endpoint.Address.Family == AddressFamily::IPv4) ? AF_INET : AF_INET6;
		in.sin_port = htons(endpoint.Port);
		inet_pton(
			in.sin_family,
			endpoint.Address.Value.c_str(),
			&in.sin_addr
		);
		sendto(
			_socket,
			data,
			len,
			0,
			reinterpret_cast<sockaddr*>(&in),
			sizeof(sockaddr_in)
		);
	}

	auto Socket::Start() -> void {
		_isActive = true;
		sockaddr_in6 local6{};
		local6.sin6_addr = IN6ADDR_ANY_INIT;
		local6.sin6_port = htons(_port);
		local6.sin6_family = AF_INET6;
		sockaddr_in local{};
		local.sin_family = (_family == AddressFamily::IPv4) ? AF_INET : AF_INET6;
		local.sin_addr.S_un.S_addr = ADDR_ANY;
		local.sin_port = htons(_port);
		_socket = INVALID_SOCKET;

		_socket = socket(
			(_family == AddressFamily::IPv4) ? AF_INET : AF_INET6,
			SOCK_DGRAM,
			IPPROTO_UDP
		);

		if (_family == AddressFamily::IPv6) {
			setsockopt(_socket, SOL_SOCKET, IPV6_V6ONLY, 0, 1);
		}

		if (_socket == INVALID_SOCKET) {
			printf("Error at socket(): %d\n", WSAGetLastError());
			WSACleanup();
			return;
		}
		int err = 0;

		if (_family == AddressFamily::IPv6) {
			err = bind(
				_socket,
				reinterpret_cast<sockaddr*>(&local6),
				static_cast<int>(sizeof(local6))
			);
		}
		else {
			err = bind(
				_socket,
				reinterpret_cast<sockaddr*>(&local),
				static_cast<int>(sizeof(local))
			);
		}

		if (err == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			closesocket(_socket);
			WSACleanup();
			return;
		}
		_readThread = std::thread([this] {
			this->ReadLoop();
			});
		_sendThread = std::thread([this] {
			this->SendLoop();
			});
	}
	auto Socket::Stop() -> void {
		_isActive = false;
		_sendThread.join();
		_readThread.join();
	}
	auto Socket::ReadLoop() -> void {
		int err = 0;
		sockaddr_in sender{};
		int senderLen = (_family == AddressFamily::IPv6) ?
			sizeof(sockaddr_in6) :
			sizeof(sockaddr_in);
		int64_t recSize = 0;
		char recvbuf[READ_BUFFER_LEN];
		char addr[46];
		
		while (_isActive) {
			if (recSize = recvfrom(
				_socket,
				recvbuf,
				READ_BUFFER_LEN,
				0,
				reinterpret_cast<sockaddr*>(&sender),
				&senderLen
			); recSize == -1) {
				printf("recv failed with error: %d\n", WSAGetLastError());
			}
			std::string parsed(recvbuf);
			inet_ntop(
				(_family == AddressFamily::IPv4) ? AF_INET : AF_INET6,
				&sender.sin_addr.S_un,
				addr,
				46
			);
			EndPoint e{
				_family, addr,
				htons(sender.sin_port)
			};
			Packet p{ PacketType(std::stoi(parsed.substr(0, 4))), e };
			_receiveBus->Write(p);
		}
	}

	auto Socket::SendLoop() -> void {
		while (_isActive) {
			for (auto& packet : _sendBus->Read()) {
				if (packet.EndPoint().Address.Family != _family) {
					continue;
				}
				Send(
					packet.Raw().c_str(),
					packet.Raw().length(),
					packet.EndPoint()
				);
			}
			std::this_thread::sleep_for(milliseconds(_sendRate));
		}
	}
}
