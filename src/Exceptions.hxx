#pragma once
#include <exception>

namespace fastnet::exceptions {
	class InvalidChannelException : std::exception {
	public:
		InvalidChannelException() : std::exception("No channel found matching criteria") {}
	};

	class InvalidEndPointException : std::exception {
	public:
		InvalidEndPointException() : std::exception("The given endpoint is invalid") {}
	};

	class InvalidPeerConfigException : std::exception {
	public:
		InvalidPeerConfigException() : std::exception("This peer either has none, or an invalid configuration") {}
	};
}
