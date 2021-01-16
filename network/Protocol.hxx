#pragma once

#include <string>

namespace Swiftrock {
	enum class TypeSize: uint64_t {
		Byte = 0x1,
		Long = 0x08,
		Magic = 0x10,
		Short = 0x02,
		UsignedShort = 0x02,
		Boolean = 0x01,
		Address = 0x07,
		UInt24 = 0x03
	};

	constexpr char Magic[] = { "00ffff00fefefefefdfdfdfd12345678" };

	struct ServerId {
		std::string Edition;
		std::string ServerName;
		std::string ProtocolVersion;
		std::string VersionName;
		uint8_t PlayerCount;
		uint8_t MaxPlayers;
		std::string GUID;
		std::string Level;
		std::string Mode;
		uint8_t ModeId;
		uint16_t PortV4;
		uint16_t PortV6;
	};

	auto inline ServerIdToString(ServerId id) ->std::string {
		return "" +
			id.Edition + ";" +
			id.ServerName + ";" +
			id.ProtocolVersion + ";" +
			id.VersionName + ";" +
			std::to_string(id.PlayerCount) + ";" +
			std::to_string(id.MaxPlayers) + ";" +
			id.GUID + ";" +
			id.Level + ";" +
			id.Mode + ";" +
			std::to_string(id.ModeId) + ";" +
			std::to_string(id.PortV4) + ";" +
			std::to_string(id.PortV6) + ";";
	}
}
