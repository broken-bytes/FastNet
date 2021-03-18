#include <iostream>

#include "../src/FastNet.hxx"
#include "../src/NetObject.hxx"
#include "../src/Peer.hxx"

using namespace std::chrono;
using namespace std::chrono_literals;

class Player : fastnet::NetObject {
public:
	Player() : NetObject(_TYPE, 0,0) {
		_health = fastnet::NetVar<float>(0.0f);
		RegisterNetVar(&_health);
	}
	auto Health() -> float {
		return _health.Value();
	}
	auto Position()->fastnet::Vector3 {
		return _position.Value();
	}
private:
	static const uint64_t _TYPE;
	fastnet::NetVar<float> _health;
	fastnet::NetVar<fastnet::Vector3> _position;
};

int main() {
	auto server = fastnet::Interface::CreatePeer();
	auto client = fastnet::Interface::CreatePeer();
	//server->Start(25655);
	client->Start();
	client->Connect("127.0.0.1", 40042);

	
	std::cout << "Is Server:" << fastnet::Interface::IsServer() << std::endl;
	std::cout << "Is Client:" << fastnet::Interface::IsClient() << std::endl;

	// TODO Implement multiple channels
	
	while(true) {
		std::this_thread::sleep_for(1s);
	}
}