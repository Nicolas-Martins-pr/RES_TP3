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

#include <map>

//#include "uqacNetwork.hpp"
#include "NetworkFramework.hpp"


namespace uqac::network
{
	class Terminal
	{
	public:
		Terminal(URL url, Config config);

		inline SocketID ID() { return m_socket; }

		void Stop();

		void Update(const FD_SET& set);

		inline std::map<SocketID, ConnectionPtr> GetAllConnection()
		{
			return m_connections;
		}

	private:
		Config m_config;
		ConnectionID m_nextConnectionID = 0;
		
		SOCKET m_socket;
		bool ready = false;

		URL m_url;

		std::map<SocketID, ConnectionPtr> m_connections;	
	};
}