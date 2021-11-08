#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define NOMINMAX
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


#include <chrono>
using namespace std::chrono_literals;
#include <map>
#include <mutex>
#include <optional>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

#include "NetworkFramework.hpp"

namespace uqac::network
{
	class Terminal;
	class Connection;

	class UQACNetwork
	{
	public:

		UQACNetwork();

		~UQACNetwork();

		void Update(std::chrono::milliseconds timeout);

		TerminalWeakPtr Listen(const std::string& url, Config config);

		ConnectionWeakPtr Connect(const std::string& url, Config config);


	private:
		bool ready = false;

		std::optional<URL> ValidateEndpoint(const std::string& endpoint);

		TerminalID m_nextTerminalID = 0;
		ConnectionID m_nextConnectionID = 0;

		std::map<SocketID, TerminalPtr> m_terminals;
		std::map<ConnectionID, ConnectionPtr> m_connections;

		std::mutex mtx;

		FD_SET m_writeSet;
		FD_SET m_readSet;
	};

}