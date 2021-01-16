#pragma once
#include <string>
#include <type_traits>

#include "../network/Address.hxx"

namespace fastnet::internal {
	struct EndPoint {
		Address Address;
		uint16_t Port;

		friend auto operator==(const EndPoint& lhs, const EndPoint& rhs) {
			return lhs.Address == rhs.Address && lhs.Port == rhs.Port;
		}
	};
}