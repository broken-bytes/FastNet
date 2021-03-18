#include "PacketBus.hxx"

#include <iostream>

namespace fastnet::internal {
	PacketBus::PacketBus() {
		_bus.reserve(100);
	}

	auto PacketBus::Write(Packet packet) -> void {
		_bus.emplace_back(packet);
	}

	auto PacketBus::Read()->Packet* {
		if(_bus.empty()) {
			return nullptr;
		}
		std::scoped_lock guard{ _mutex };
		return &_bus[0];
	}

	auto PacketBus::Clear(Packet* target) -> void {
		for(size_t x = 0; x < _bus.size(); x++) {
			if(target == &_bus[x]) {
				_bus.erase(_bus.begin() + x);
				return;
			}
		} 
	}
}
