#include "../headers/network/Terminal.hpp"
#include "../headers/network/Connection.hpp"

namespace uqac::network
{
	Terminal::Terminal(URL url, Config config) : m_url(url), m_config(config)
	{
		struct addrinfo* result = NULL,
			* ptr = NULL,
			hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM; 
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		// Resolve the server address and port
		auto iResult = getaddrinfo(url.ip.c_str(), url.port.c_str(), &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
		}

		// Create a SOCKET for connecting to server
		m_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (m_socket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			freeaddrinfo(result);
		}

		// Setup the TCP listening socket
		iResult = bind(m_socket, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
		}

		freeaddrinfo(result);

		iResult = listen(m_socket, SOMAXCONN);
		if (iResult == SOCKET_ERROR) {
			printf("listen failed with error: %d\n", WSAGetLastError());
		}

		ready = true;

	}



	void Terminal::Update(const FD_SET& set)
	{

		if (auto x = FD_ISSET(m_socket, &set))
		{
			auto  socketClient = accept(m_socket, NULL, NULL);
			if (socketClient == INVALID_SOCKET) {
				printf("accept failed with error: %d\n", WSAGetLastError());
			}

			auto connection = std::make_shared<Connection>(socketClient, m_config);
			m_connections.insert(std::make_pair(socketClient, connection));
			m_config.OnConnect(connection);
 		}


		for (auto& c : m_connections)
		{
			if (auto x = FD_ISSET(c.first, &set))
			{
				c.second->Update();
			}
		}
			


	}
}