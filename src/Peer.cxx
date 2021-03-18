#include <optional>

#include "Peer.hxx"

#include "Exceptions.hxx"

using namespace std::chrono;
using namespace std::chrono_literals;

namespace fastnet {
	constexpr char ChannelReliableDefault[] = "ChannelReliableDefault";
	constexpr char ChannelReliableSequencedDefault[] = "ChannelReliableSequencedDefault";
	constexpr char ChannelReliableOrderedDefault[] = "ChannelReliableOrderedDefault";
	constexpr char ChannelReliableFragmentedDefault[] = "ChannelReliableFragmentedDefault";
	constexpr char ChannelUnreliableDefault[] = "ChannelUnreliableDefault";
	constexpr char ChannelUnreliableSequencedDefault[] = "ChannelUnreliableSequencedDefault";
	constexpr char ChannelUnreliableOrderedDefault[] = "ChannelUnreliableOrderedDefault";
	constexpr char ChannelChat[] = "ChannelChat";
	
	constexpr uint16_t ConnectTimeoutMs = 5000;
	
	auto Peer::Setup(PeerConfig config) -> void {
		_config = std::make_unique<PeerConfig>(config);
		SetSendRate(_config->SendRate);
	}

	auto Peer::Start(std::optional<uint16_t> port) -> void {
		if(!_config) {
			throw exceptions::InvalidPeerConfigException(0);
		}

		if (_config->Channels.empty()) {
			throw exceptions::InvalidPeerConfigException(1);
		}

		Channel* unreliable = nullptr;

		for(auto& item: _config->Channels) {
			if(item.Type == ChannelType::Unreliable) {
				unreliable = &item;
				break;
			}
		}
		
		if (!unreliable) {
			throw exceptions::InvalidPeerConfigException(2);
		}
		
		_sendBus = std::make_shared<internal::PacketBus>();
		_receiveBus = std::make_shared<internal::PacketBus>();
		_sockets = std::vector<std::unique_ptr<internal::Socket>>();
		if (port == std::nullopt) {
			FastNet::SetClient(true);
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
		FastNet::SetServer(true);
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

	auto Peer::Connect(std::string address, uint16_t port) -> void {
		auto e = internal::EndPoint{ {address}, port };
		auto endpoint = std::make_shared<internal::EndPoint>(e);
		internal::Packet p{
			internal::PacketType::ConnectRequest,
			endpoint
	};

		Channel* unreliable = nullptr;

		for(auto& item: _config->Channels) {
			if(item.Type == ChannelType::Unreliable) {
				unreliable = &item;
			}
		}
		if(!unreliable) {
			throw exceptions::InvalidPeerConfigException(0);
		}
		
		p.Channel(*unreliable);
		_sendBus->Write(p);
	}

	auto Peer::Read() -> void {
		while(true) {
			auto* packet = _receiveBus->Read();
			while(packet != nullptr) {
				packet->Open();
				switch (packet->Type()) {
				case internal::PacketType::ConnectRequest:
					internal::Packet accept {
						internal::PacketType::ConnectResponse,
						packet->EndPoint()
					};
					Channel* unreliable = nullptr;

					for (auto& item : _config->Channels) {
						if (item.Type == ChannelType::Unreliable) {
							unreliable = &item;
						}
					}
					if (!unreliable) {
						throw exceptions::InvalidPeerConfigException(2);
					}
					accept.Channel(*unreliable);
					_sendBus->Write(accept);
					break;
				}
				_receiveBus->Clear(packet);
				packet = _receiveBus->Read();
			}

			std::this_thread::sleep_for(500us);
		}
	}

	auto Peer::Send(
		std::vector<internal::Connection> connections,
		internal::Packet packet,
		Channel channel
	) -> void {
		for (auto& con : connections) {
			packet.Channel(channel);
			packet.EndPoint(con.Endpoint);
			_sendBus->Write(packet);
		}
	}

	auto Peer::ChannelByName(std::string name) const -> Channel {
		for(const auto& item: _config->Channels) {
			if(item.Name == name) {
				return item;
			}
		}
		throw exceptions::InvalidChannelException(0);
	}
	auto Peer::ChannelById(uint8_t id) const -> Channel {
		for (const auto& item : _config->Channels) {
			if (item.Id == id) {
				return item;
			}
		}
		throw exceptions::InvalidChannelException(1);
	}
}
