#pragma once
#include <memory>
#include <string>

#include "Channel.hxx"
#include "EndPoint.hxx"
#include "../src/NetVar.hxx"

namespace fastnet::internal {
	enum class PacketTypeSize : uint8_t {
		IntShort = 4, UIntShort = 4,
		Int = 8, UInt = 8,
		IntLong = 16, UIntLong = 16,
		Float = 8,
		Double = 16,
		Bool = 1
	};
	
	enum class PacketType: uint8_t {
		ConnectRequest = 0x00,
		ConnectResponse = 0x01,
		ConnectHandshake = 0x02,
		PingRequest = 0x04,
		PingResponse = 0x05,
		MessageAck = 0x06
	};

	class Packet {
	public:
		explicit Packet(PacketType type);
		explicit Packet(PacketType type, std::shared_ptr<internal::EndPoint> endpoint);
		~Packet();
		auto Raw()->std::string;
		auto Type()->PacketType;
		auto Channel()->uint8_t;
		auto EndPoint()const->std::shared_ptr<internal::EndPoint>;
		auto Open() -> void;
		auto Close() -> void;
		auto ReadIntShort()->int16_t;
		auto ReadUIntShort()->uint16_t;
		auto ReadInt()->int32_t;
		auto ReadUInt()->uint32_t;
		auto ReadIntLong()->int64_t;
		auto ReadUIntLong()->uint64_t;
		auto ReadFloat() -> float;
		auto ReadDouble() -> double;
		auto ReadString()->std::string;
		auto ReadVector2()->fastnet::Vector2;
		auto ReadVector3()->fastnet::Vector3;
		auto Type(PacketType type) -> void;
		auto Channel(fastnet::Channel channel) -> void;
		auto EndPoint(std::shared_ptr<internal::EndPoint> e)->void;
		auto WriteIntShort(int16_t data)->void;
		auto WriteUIntShort(uint16_t data)->void;
		auto WriteInt(int32_t data)->void;
		auto WriteUInt(uint32_t data)->void;
		auto WriteIntLong(int64_t data)->void;
		auto WriteUIntLong(uint64_t data)->void;
		auto WriteFloat(float data) -> void;
		auto WriteDouble(double data) ->void;
		auto WriteString(std::string data)->void;
		auto WriteVector2(Vector2 data)->void;
		auto WriteVector3(Vector3 data)->void;
		auto Deallocate() -> void;
	private:
		std::string _data = "";
		uint16_t _position = 0;
		std::shared_ptr<internal::EndPoint> _endpoint;
	};
}