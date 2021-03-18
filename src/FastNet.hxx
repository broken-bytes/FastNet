#pragma once
#include <memory>
#include <vector>

#include "Globals.hxx"
#include "Peer.hxx"

namespace fastnet {
	class DLL_EXPORT FastNet {
	public:
		friend class Peer;
		auto static CreatePeer()->std::shared_ptr<Peer>;
		auto static IsServer() -> bool;
		auto static IsClient() -> bool;
		auto static ClientId()->uint64_t;
	private:
		static inline std::vector<std::shared_ptr<Peer>> _peers;
		static inline uint64_t _clientId;
		static inline bool _isServer;
		static inline bool _isClient;

		auto static SetServer(bool value) -> void;
		auto static SetClient(bool value) -> void;
	};
}
