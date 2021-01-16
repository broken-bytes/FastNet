#include "NetObject.hxx"

namespace fastnet {
	NetObject::NetObject(uint64_t type, uint64_t id, uint64_t owner) {}
	auto NetObject::IsOwner() -> bool {
		// TODO: Implement owner system
		if(_ownerId == Interface::ClientId()) {
			return true;
		}
		return false;
	}
	auto NetObject::IsServer() -> bool {
		// TODO Add server detection
		return Interface::IsServer();
	}

	auto NetObject::IsClient() -> bool {
		return Interface::IsClient();
	}

	auto NetObject::RegisterNetVar(INetVar* var) -> void {
		_netVars.emplace_back(var);
	}
}
