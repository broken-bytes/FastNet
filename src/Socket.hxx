#pragma once


#include <cstdint>
#include <queue>
#include <string>
#include <thread>
#include <winsock2.h>



#include "Address.hxx"
#include "Packet.hxx"
#include "PacketBus.hxx"
#include "../src/Globals.hxx"

namespace fastnet::internal {
	struct EndPoint;
	constexpr uint16_t READ_BUFFER_LEN = 1024;
#ifdef _WIN32
	typedef SOCKET RawSocket;
#endif
	
	class Socket {
	public:
		Socket(AddressFamily family = AddressFamily::IPv6, uint16_t port = 0);
		~Socket() = default;

		auto SetSendRate(uint8_t rate) -> void;
		auto SetSendBus(PacketBus* bus) -> void;
		auto SetReceiveBus(PacketBus* bus) -> void;

		
		auto Send(
			const char* data,
			size_t len,
			EndPoint* endpoint
		) -> void;

	private:
		static inline bool isInit;
		RawSocket _socket;
		std::thread _readThread;
		std::thread _sendThread;

		bool _isActive;
		AddressFamily _family;
		uint16_t _port;
		std::shared_ptr<internal::PacketBus> _receiveBus;
		std::shared_ptr<internal::PacketBus> _sendBus;
		uint8_t _sendRate;

		
		auto Start() -> void;
		auto Stop() -> void;
		auto ReadLoop() -> void;
		auto SendLoop() -> void;
	};
}
