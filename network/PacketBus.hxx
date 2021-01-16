#pragma once

#include <vector>
#include <mutex>

#include "Packet.hxx"

namespace fastnet::internal {
		class PacketBus {
		public:
			auto Write(Packet packet) -> void {
				std::scoped_lock guard{ _mutex };
				_bus.emplace_back(packet);
			}

			auto Read()->std::vector<Packet> {
				std::scoped_lock guard{ _mutex };
				return _bus;
			}
		private:
			std::vector<Packet> _bus;
			std::mutex _mutex;
	};
}
