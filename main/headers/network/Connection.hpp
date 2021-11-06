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

#include "NetworkFramework.hpp"

namespace uqac::network
{
	class Connection : public std::enable_shared_from_this<Connection>
	{
	public:
		Connection(URL url, Config config);
		Connection(SOCKET socket, Config config);
		~Connection();


		inline int ID() { return m_socket; }
		void Send(const char* buff, size_t size);

		
		void Update();


	private:
		int Recv(char* buff, size_t size);

		Config m_config;
		SOCKET m_socket;
		bool ready = false;
		bool first = true;
	};
}