#pragma once

#include <map>
#include <optional>
#include "../network/Address.hxx"
#include "../Globals.hxx"
#include "FastNet.hxx"
#include "PeerConfig.hxx"
#include "../network/Connection.hxx"
#include "../network/EndPoint.hxx"
#include "../network/PacketBus.hxx"
#include "../network/Socket.hxx"

namespace fastnet::types {
	constexpr uint8_t SendRateDefault = 24;
	DLL_EXPORT class Peer {
	public:
		Peer() = default;
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
		auto Connect(internal::EndPoint endpoint) -> void;
		auto Read() -> void;
		auto Send(
			std::vector<internal::Connection> connections,
			internal::Packet packet,
			internal::Channel channel
		) -> void;
	private:
		friend class ::fastnet::Interface;
		std::vector<std::unique_ptr<internal::Socket>> _sockets;
		// The id of this peer as a client connected to a server
		uint64_t _clientId;
		std::shared_ptr<internal::PacketBus> _receiveBus;
		std::shared_ptr<internal::PacketBus> _sendBus;
		uint8_t _sendRate;
		std::thread _readThread;
		std::map<std::string, internal::Channel> _channels;
		std::vector<internal::Connection> _connections;

		auto SetupChannels() -> void;
	};
}
