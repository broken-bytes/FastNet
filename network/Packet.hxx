#pragma once
#include <string>


#include "EndPoint.hxx"
#include "../core/NetVar.hxx"

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
		PingRequest = 0x02,
		PingResponse = 0x03,
		MessageAck = 0x04
	};

	enum class Channel: uint8_t {
		Unreliable = 0x00,
		UnreliableSequenced = 0x01,
		UnreliableOrdered = 0x02,
		Reliable = 0x03,
		ReliableSequenced = 0x04,
		ReliableOrdered = 0x05,
	};

	class Packet {
	public:
		explicit Packet(PacketType type);
		explicit Packet(PacketType type, EndPoint endpoint);
		auto Raw()->std::string;
		auto Type()->PacketType;
		auto Channel()->Channel;
		auto EndPoint()->EndPoint;
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
		auto Channel(internal::Channel channel) -> void;
		auto EndPoint(internal::EndPoint e)->void;
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
	private:
		std::string _data = "";
		uint16_t _position = 0;
		internal::EndPoint _endpoint;
	};
}