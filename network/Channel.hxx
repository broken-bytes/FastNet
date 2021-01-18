#pragma once

namespace fastnet::internal {
	enum class ChannelType : uint8_t {
		Unreliable = 0x00,
		UnreliableSequenced = 0x01,
		UnreliableOrdered = 0x02,
		Reliable = 0x03,
		ReliableSequenced = 0x04,
		ReliableOrdered = 0x05,
		ReliableFragmented = 0x06
	};
	struct Channel {
		ChannelType Type;
		uint8_t Id;
	};
}
