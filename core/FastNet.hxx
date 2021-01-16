#pragma once
#include <memory>
#include <vector>
namespace fastnet {
	namespace types {
		class Peer;
	}
	
	class Interface {
	public:
		friend class types::Peer;
		auto static CreatePeer()->std::shared_ptr<types::Peer>;
		auto static IsServer() -> bool;
		auto static IsClient() -> bool;
		auto static ClientId()->uint64_t;
	private:
		static inline std::vector<types::Peer*> _peers;
		static inline bool _isServer;
		static inline bool _isClient;
		static inline uint64_t _clientId;
	};
}
