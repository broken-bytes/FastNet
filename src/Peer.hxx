#pragma once

#include <map>
#include <optional>
#include "../src/Address.hxx"
#include "../src/Globals.hxx"
#include "FastNet.hxx"
#include "PeerConfig.hxx"
#include "../src/Connection.hxx"
#include "../src/EndPoint.hxx"
#include "../src/PacketBus.hxx"
#include "../src/Socket.hxx"

namespace fastnet {
	class DLL_EXPORT Peer {
	public:
		Peer() = default;
		/// <summary>
		/// Sets the parameters for this peer
		/// </summary>
		/// <param name="config"></param>
		/// <returns></returns>
		auto Setup(PeerConfig config) -> void;
		auto Start(std::optional<uint16_t> port = std::nullopt) -> void;
		/// <summary>
		/// Get the Id of the local peer. Used to detect ownership
		/// </summary>
		/// <returns></returns>
		auto ClientId()->uint64_t;
		/// <summary>
		/// Connects to a remote endpoint
		/// </summary>
		/// <param name="address"></param>
		/// <param name="port"></param>
		/// <returns></returns>
		auto Connect(std::string address, uint16_t port) -> void;
		auto Read() -> void;
		auto Send(
			std::vector<internal::Connection> connections,
			internal::Packet packet,
			Channel channel
		) -> void;
	private:
		std::vector<std::unique_ptr<internal::Socket>> _sockets;
		std::unique_ptr<PeerConfig> _config;
		// The id of this peer as a client connected to a server
		uint64_t _clientId;
		std::shared_ptr<internal::PacketBus> _receiveBus;
		std::shared_ptr<internal::PacketBus> _sendBus;
		uint8_t _sendRate;
		std::thread _readThread;
		std::vector<internal::Connection> _connections;

		auto ChannelByName(std::string name) const -> Channel;
		auto ChannelById(uint8_t id) const -> Channel;
		auto SetSendRate(uint8_t rate = 0) -> void;
	};
}
