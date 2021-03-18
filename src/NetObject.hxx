#pragma once
#include <cstdint>
#include <vector>

#include "NetVar.hxx"
#include "Peer.hxx"

namespace fastnet {
	class NetObject {
	public:
		NetObject(uint64_t type, uint64_t id, uint64_t owner);
		auto IsOwner() -> bool;
		auto IsServer() -> bool;
		auto IsClient() -> bool;
		auto RegisterNetVar(INetVar* var) -> void;
	private:
		/// <summary>
		/// Used in order to distinguish and use network objects across server/client.
		/// Network object type index. 
		/// </summary>
		uint64_t _type;
		/// <summary>
		/// The Id of the owner. 0 means server
		/// </summary>
		uint64_t _ownerId;
		/// <summary>
		/// The unique Id of this object instance
		/// </summary>
		uint64_t _id;
		/// <summary>
		/// A vector of network variables this object carries
		/// </summary>
		std::vector <INetVar*> _netVars;
	};
}
