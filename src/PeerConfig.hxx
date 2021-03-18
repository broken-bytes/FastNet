#pragma once
#include <cstdint>

#include "Channel.hxx"

namespace fastnet {
	struct PeerConfig {
		uint16_t MaxConnections;
		std::vector<Channel> Channels;
		uint8_t SendRate;
	};
}
