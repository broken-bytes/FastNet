#include <iostream>
#include <memory>

#include "FastNet.hxx"
#include "Peer.hxx"
#include "Socket.hxx"

namespace fastnet {
	auto FastNet::CreatePeer() -> std::shared_ptr<Peer> {
		auto ptr = std::make_shared<Peer>();
		_peers.emplace_back(ptr); 
		return ptr;
	}

	auto FastNet::IsServer() -> bool {
		return _isServer;
	}

	auto FastNet::IsClient() -> bool {
		return _isClient;
	}

	auto FastNet::ClientId() -> uint64_t {
		return _clientId;
	}

	auto FastNet::SetServer(bool value) -> void {
		_isServer = value;
	}

	auto FastNet::SetClient(bool value) -> void {
		_isClient = value;
	}

}
