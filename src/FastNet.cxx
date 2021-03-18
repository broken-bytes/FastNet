#include <iostream>
#include <memory>

#include "FastNet.hxx"
#include "Peer.hxx"

namespace fastnet {
	auto Interface::CreatePeer() -> std::shared_ptr<types::Peer> {
		auto ptr = std::make_shared<types::Peer>();
		_peers.emplace_back(ptr); 
		return ptr;
	}

	auto Interface::IsServer() -> bool {
		return _isServer;
	}

	auto Interface::IsClient() -> bool {
		return _isClient;
	}

	auto Interface::ClientId() -> uint64_t {
		return _clientId;
	}

}
