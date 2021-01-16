#pragma once
#include <string>

namespace fastnet::internal {
	enum class AddressFamily {
		IPv4,
		IPv6
	};

	struct Address {
		AddressFamily Family;
		std::string Value;

		friend auto operator==(const Address& lhs, const Address& rhs) {
			return lhs.Family == rhs.Family && lhs.Value == rhs.Value;
		}
	};

	constexpr char ANY_IPv4[] = "000.000.000.000";
	constexpr char ANY_IPv6[] = "0000:0000:0000:0000:0000:0000:0000:0000";
}
