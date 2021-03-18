#pragma once
#include <string>

namespace fastnet::internal {
	constexpr char ANY_IPv4[] = "000.000.000.000";
	constexpr char ANY_IPv6[] = "0000:0000:0000:0000:0000:0000:0000:0000";

	enum class AddressFamily {
		IPv4,
		IPv6
	};

	struct Address {
		AddressFamily Family;
		std::string Value;


		Address() {
			Family = AddressFamily::IPv4;
			Value = "";
		}
		
		Address(std::string address) {
			Value = address;
			Family = (address.size() > strlen(ANY_IPv4)) ?
				Family = AddressFamily::IPv6 :
				Family = AddressFamily::IPv4;
		}

		Address(std::string address, AddressFamily family) {
			Value = address;
			Family = family;
		}

		operator std::string() const {
			return Value;
		}

		friend auto operator==(const Address& lhs, const Address& rhs) {
			return lhs.Family == rhs.Family && lhs.Value == rhs.Value;
		}
	};
}
