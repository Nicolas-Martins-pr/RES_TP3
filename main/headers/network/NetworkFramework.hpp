#pragma once

#include <functional>
#include <memory>
#include <winsock2.h>

namespace uqac::network
{
	using ConnectionID = uint16_t;
	using TerminalID = uint16_t;
	using SocketID = SOCKET;

	struct URL
	{
		const std::string completeURL;
		const std::string protocol;
		const std::string ip;
		const std::string port;
	};

	class Connection;
	class Terminal;

	using ConnectionPtr = std::shared_ptr<Connection>;
	using ConnectionWeakPtr = std::weak_ptr<Connection>;

	using TerminalPtr = std::shared_ptr<Terminal>;
	using TerminalWeakPtr = std::weak_ptr<Terminal>;

	struct Config
	{
		std::function<void(ConnectionWeakPtr)> OnConnect;
		std::function<void(ConnectionWeakPtr, char*, size_t)> OnReceive;
	};

}
