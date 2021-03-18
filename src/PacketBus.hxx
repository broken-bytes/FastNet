#pragma once

#include <map>
#include <vector>
#include <mutex>

#include "Packet.hxx"

namespace fastnet::internal {
		class PacketBus {
		public:
			PacketBus();
			auto Write(Packet packet) -> void;
			auto Read()->Packet*;
			auto Clear(Packet* target) -> void;
			
		private:
			std::vector<Packet> _bus;
			std::mutex _mutex;
	};
}
