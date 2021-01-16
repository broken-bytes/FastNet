#pragma once
#include "Address.hxx"
#include "EndPoint.hxx"

namespace fastnet::internal {
	struct Connection {
		/// <summary>
		/// The Id of this connection, relative to server. 0  = Server, 1 = first client etc.
		/// </summary>
		uint64_t Id;
		/// <summary>
		/// The last ping of this connection
		/// </summary>
		uint16_t Ping;
		/// <summary>
		/// The endpoint this connection is bound to
		/// </summary>
		EndPoint Endpoint;
		/// <summary>
		/// The socket number associated with this connection
		/// </summary>
		uint8_t Socket;
	};
}
