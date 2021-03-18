#pragma once
#include <exception>

namespace fastnet::exceptions {
	/// <summary>
	/// This exception is thrown when a channel was requested that does not exist\n
	/// \b Codes -\n
	/// 0: Requested bad name\n
	/// 1: Requested bad id\n
	/// </summary>
	class DLL_EXPORT InvalidChannelException : std::exception {
	public:
		InvalidChannelException(uint64_t code) : std::exception("No channel found matching criteria", code) {}
	};

	/// <summary>
	/// This exception is thrown when an invalid endpoint operation was requested\n
	/// \b Codes - \n
	/// 0: The endpoint is bad \n
	/// </summary>
	class DLL_EXPORT InvalidEndPointException : std::exception {
	public:
		InvalidEndPointException(uint64_t code) : std::exception("The given endpoint is invalid", code) {}
	};

	/// <summary>
	/// This exception is thrown when a peer has an invalid config\n
	/// \b Codes -\n
	/// 0: No Config\n
	/// 1: No Channels\n
	/// 2: No Unreliable Channel\n
	/// 3: Max Connections < 1\n
	/// 4: Send Rate < 1\n
	/// </summary>
	class DLL_EXPORT InvalidPeerConfigException : std::exception {
	public:
		InvalidPeerConfigException(uint64_t code) : std::exception("This peer either has none, or an invalid configuration", code) {}
	};
}
