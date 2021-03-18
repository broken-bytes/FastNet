#pragma once
#include <cstdint>

#include "Channel.hxx"

namespace fastnet {
	struct DLL_EXPORT PeerConfig {		
		uint16_t MaxConnections;
		std::vector<Channel> Channels;
		uint8_t SendRate = 24;
	};
}
