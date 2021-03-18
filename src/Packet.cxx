#include "Packet.hxx"

#include <iomanip>
#include <sstream>

namespace fastnet::internal {
	Packet::Packet(PacketType type) : Packet(type, nullptr) {
	}

	Packet::Packet(PacketType type, std::shared_ptr<internal::EndPoint> endpoint) {
		Type(type);
		_endpoint = endpoint;
	}

	Packet::~Packet() {
		_endpoint = nullptr;
	}

	auto Packet::Raw() -> std::string {
		return _data;
	}

	auto internal::Packet::Type() -> PacketType {
		return PacketType(ReadUIntShort());;
	}

	auto internal::Packet::Channel() -> uint8_t {
		return ReadUIntShort();
	}

	auto Packet::EndPoint() const -> std::shared_ptr<internal::EndPoint> {
		return _endpoint;
	}

	auto internal::Packet::Open() -> void {
		_position = 0;
	}
	auto internal::Packet::Close() -> void {
		_position = 0;
	}

	auto internal::Packet::ReadIntShort() -> int16_t {
		const size_t size = static_cast<uint8_t>(PacketTypeSize::IntShort);
		auto val = std::stoi(
			_data.substr(_position, size),
			nullptr,
			16
		);
		_position += size;
		return val;
	}
	auto internal::Packet::ReadUIntShort() -> uint16_t {
		const size_t size = static_cast<uint8_t>(PacketTypeSize::UIntShort);
		auto val = std::stoul(
			_data.substr(_position, size),
			nullptr,
			16
		);
		_position += size;
		return val;
	}

	auto internal::Packet::ReadInt() -> int32_t {
		const size_t size = static_cast<uint8_t>(PacketTypeSize::Int);
		auto val = std::stoi(
			_data.substr(_position, size),
			nullptr,
			16
		);
		_position += size;
		return val;
	}
	auto internal::Packet::ReadUInt() -> uint32_t {
		const size_t size = static_cast<uint8_t>(PacketTypeSize::UInt);
		auto val = std::stoul(
			_data.substr(_position, size),
			nullptr,
			16
		);
		_position += size;
		return val;
	}
	auto internal::Packet::ReadIntLong() -> int64_t {
		const size_t size = static_cast<uint8_t>(PacketTypeSize::IntLong);
		auto val = std::stoll(
			_data.substr(_position, size),
			nullptr,
			16
		);
		_position += size;
		return val;
	}
	auto internal::Packet::ReadUIntLong() -> uint64_t {
		const size_t size = static_cast<uint8_t>(PacketTypeSize::UIntLong);
		auto val = std::stoull(
			_data.substr(_position, size),
			nullptr,
			16
		);
		_position += size;
		return val;
	}
	auto internal::Packet::ReadFloat() -> float {
		const size_t size = static_cast<uint8_t>(PacketTypeSize::Float);
		auto val = std::stof(
			_data.substr(_position, size),
			nullptr
		);
		_position += size;
		return val;
	}
	auto internal::Packet::ReadDouble() -> double {
		const size_t size = static_cast<uint8_t>(PacketTypeSize::Double);
		auto val = std::stod(
			_data.substr(_position, size),
			nullptr
		);
		_position += size;
		return val;
	}
	auto internal::Packet::ReadString() -> std::string {
		const size_t size = static_cast<uint8_t>(PacketTypeSize::UIntShort);
		auto len = ReadUIntShort();
		auto str = _data.substr(_position, len);
		_position += str.length();
		return str;
	}
	auto internal::Packet::ReadVector2() -> fastnet::Vector2 {
		return { ReadFloat(), ReadFloat() };
	}
	auto internal::Packet::ReadVector3() -> fastnet::Vector3 {
		return { ReadFloat(), ReadFloat(), ReadFloat() };
	}

	auto Packet::Type(PacketType type) -> void {
		WriteUIntShort(static_cast<uint8_t>(type));
	}

	auto Packet::Channel(fastnet::Channel channel) -> void {
		std::stringstream str;
		const size_t size = static_cast<uint8_t>(PacketTypeSize::UIntShort);
		str << std::setfill('0') << std::setw(size)
			<< std::hex << std::to_string(channel.Id);
		_data.insert(size, str.str());
	}

	auto Packet::EndPoint(std::shared_ptr<internal::EndPoint> e) -> void {
		_endpoint = e;
	}

	auto internal::Packet::WriteIntShort(int16_t data) -> void {
		std::stringstream str;
		const size_t size = static_cast<uint8_t>(PacketTypeSize::IntShort);
		str << std::setfill('0') << std::setw(size)
			<< std::hex << data;
		_data.append(str.str());
	}
	auto internal::Packet::WriteUIntShort(uint16_t data) -> void {
		std::stringstream str;
		const size_t size = static_cast<uint8_t>(PacketTypeSize::UIntShort);
		str << std::setfill('0') << std::setw(size)
			<< std::hex << data;
		_data.append(str.str());
	}
	auto internal::Packet::WriteInt(int32_t data) -> void {
		std::stringstream str;
		const size_t size = static_cast<uint8_t>(PacketTypeSize::Int);
		str << std::setfill('0') << std::setw(size)
			<< std::hex << data;
		_data.append(str.str());
	}
	auto internal::Packet::WriteUInt(uint32_t data) -> void {
		std::stringstream str;
		const size_t size = static_cast<uint8_t>(PacketTypeSize::UInt);
		str << std::setfill('0') << std::setw(size)
			<< std::hex << data;
		_data.append(str.str());
	}
	auto internal::Packet::WriteIntLong(int64_t data) -> void {
		std::stringstream str;
		const size_t size = static_cast<uint8_t>(PacketTypeSize::IntLong);
		str << std::setfill('0') << std::setw(size)
			<< std::hex << data;
		_data.append(str.str());
	}
	auto internal::Packet::WriteUIntLong(uint64_t data) -> void {
		std::stringstream str;
		const size_t size = static_cast<uint8_t>(PacketTypeSize::UIntLong);
		str << std::setfill('0') << std::setw(size)
			<< std::hex << data;
		_data.append(str.str());
	}
	auto internal::Packet::WriteFloat(float data) -> void {
		_data.append(std::to_string(data));
	}
	auto internal::Packet::WriteDouble(double data) -> void {
		_data.append(std::to_string(data));
	}
	auto internal::Packet::WriteString(std::string data) -> void {
		WriteUIntShort(data.length());
		_data.append(data);
	}
	auto internal::Packet::WriteVector2(Vector2 data) -> void {
		WriteFloat(data.X);
		WriteFloat(data.Y);
	}
	auto internal::Packet::WriteVector3(Vector3 data) -> void {
		WriteFloat(data.X);
		WriteFloat(data.Y);
		WriteFloat(data.Z);
	}

	auto Packet::Deallocate() -> void {}
}
