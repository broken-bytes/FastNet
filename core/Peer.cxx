#include <optional>

#include "Peer.hxx"


namespace fastnet::types {
	constexpr uint16_t ConnectTimeoutMs = 5000;
	auto Peer::Start(std::optional<uint16_t> port) -> void {
		_sendBus = std::make_shared<internal::PacketBus>();
		_receiveBus = std::make_shared<internal::PacketBus>();
		SetSendRate();
		_sockets = std::vector<std::unique_ptr<internal::Socket>>();
		if (port == std::nullopt) {
			Interface::_isClient = true;
			_sockets.emplace_back(std::make_unique<internal::Socket>(internal::AddressFamily::IPv4));
			_sockets[0]->SetReceiveBus(_receiveBus.get());
			_sockets[0]->SetSendBus(_sendBus.get());
			_sockets[0]->SetSendRate(_sendRate);
			_sockets.emplace_back(std::make_unique<internal::Socket>(internal::AddressFamily::IPv6));
			_sockets[1]->SetReceiveBus(_receiveBus.get());
			_sockets[1]->SetSendBus(_sendBus.get());
			_sockets[1]->SetSendRate(_sendRate);
			return;
		}
		Interface::_isServer = true;
		_sockets.emplace_back(
			std::make_unique <internal::Socket>(
				internal::AddressFamily::IPv6, port.value()
				)
		);
		_sockets[0]->SetReceiveBus(_receiveBus.get());
		_sockets[0]->SetSendBus(_sendBus.get());
		_sockets[0]->SetSendRate(_sendRate);
		_sockets.emplace_back(
			std::make_unique <internal::Socket>(
				internal::AddressFamily::IPv4, port.value()
				)
		);
		_sockets[1]->SetReceiveBus(_receiveBus.get());
		_sockets[1]->SetSendBus(_sendBus.get());
		_sockets[1]->SetSendRate(_sendRate);
		_readThread = std::thread([this] {
			this->Read();
		});
	}

	auto Peer::ClientId() -> uint64_t {
		return _clientId;
	}

	auto Peer::SetSendRate(uint8_t rate) -> void {
		_sendRate = 1000 / rate;
		for(auto& socket: _sockets) {
			socket->SetSendRate(_sendRate);
		}
	}

	auto Peer::Connect(internal::EndPoint endpoint) -> void {
		internal::Packet p{ internal::PacketType::ConnectRequest, std::move(endpoint) };
		p.Channel(internal::Channel::Reliable);
		_sendBus->Write(p);
	}

	auto Peer::Read() -> void {
		while(true) {
			for(auto& packet: _receiveBus->Read()) {
				packet.Open();
				switch (packet.Type()) {
				case internal::PacketType::ConnectRequest:
					internal::Packet accept {
						internal::PacketType::ConnectResponse,
						packet.EndPoint()
					};
					accept.Channel(internal::Channel::Unreliable);
					_sendBus->Write(accept);
					break;
				}
			}
		}
	}

	auto Peer::Send(
		std::vector<internal::Connection> connections,
		internal::Packet packet,
		internal::Channel channel
	) -> void {
		for (auto& con : connections) {
			packet.Channel(channel);
			packet.EndPoint(con.Endpoint);
			_sendBus->Write(packet);
		}
	}
}
