#pragma once
#include <cstdint>

namespace fastnet {
	struct PeerConfig {
		uint16_t PortIPv4;
		uint16_t PortIPv6;
	};
}
