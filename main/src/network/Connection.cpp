#include "../headers/network/Connection.hpp"

#include <array>

namespace uqac::network
{
	Connection::Connection(URL url, Config config) : m_config(config)
	{
		struct addrinfo* result = NULL,
			* ptr = NULL,
			hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
		auto iResult = getaddrinfo(url.ip.c_str(), url.port.c_str(), &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
		}

		ptr = result;

		if (iResult == 0) {
			m_socket = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);
		}

		iResult = connect(m_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			printf("Connect failed with error: %d\n", WSAGetLastError());
		}

		freeaddrinfo(result);

		ready = true;
	}

	Connection::Connection(SOCKET socket, Config config) : m_socket(socket), m_config(config)
	{
		ready = true;
	}

	Connection::~Connection()
	{
		shutdown(m_socket, SD_BOTH);
		closesocket(m_socket);
	}



	void Connection::Send(const char* buff, size_t size)
	{
		auto iResult = send(m_socket, buff, size, 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
		}
	}

	int Connection::Recv(char* buff, size_t size)
	{
		return recv(m_socket, buff, size, 0);
	}

	void Connection::Update()
	{
		std::array<char,0xFFFF> buffer;
		auto size = Recv(buffer.data(), 0xFFFF);
		if (size > 0) {
			m_config.OnReceive(shared_from_this(), buffer.data(), size);
		}


	}
}