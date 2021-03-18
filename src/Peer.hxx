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

namespace fastnet::types {
	constexpr uint8_t SendRateDefault = 24;
	DLL_EXPORT class Peer {
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
		/// Sets the number of sends per second
		/// </summary>
		/// <param name="rate"></param>
		/// <returns></returns>
		auto SetSendRate(uint8_t rate = SendRateDefault) -> void;
		auto Connect(std::string address, uint16_t port) -> void;
		auto Read() -> void;
		auto Send(
			std::vector<internal::Connection> connections,
			internal::Packet packet,
			Channel channel
		) -> void;
	private:
		friend class ::fastnet::Interface;
		std::vector<std::unique_ptr<internal::Socket>> _sockets;
		PeerConfig _config;
		// The id of this peer as a client connected to a server
		uint64_t _clientId;
		std::shared_ptr<internal::PacketBus> _receiveBus;
		std::shared_ptr<internal::PacketBus> _sendBus;
		uint8_t _sendRate;
		std::thread _readThread;
		std::vector<internal::Connection> _connections;

		auto ChannelByName(std::string name) const -> Channel;
		auto ChannelById(uint8_t id) const -> Channel;
	};
}
