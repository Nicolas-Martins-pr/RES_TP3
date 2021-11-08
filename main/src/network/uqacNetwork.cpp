#include "../headers/network/uqacNetwork.hpp"
#include "../headers/network/Terminal.hpp"
#include "../headers/network/Connection.hpp"

#include <regex>
static constexpr char regex_endpoint_str[] = "(.*)(?://)(.*)(?::)((?:[0-9]+))";
static const std::regex regex_endpoint = std::regex(regex_endpoint_str);

namespace uqac::network
{
	UQACNetwork::UQACNetwork()
	{
		struct addrinfo* result = NULL;
		struct addrinfo hints;

		WSADATA wsaData;
		int iResult;

		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			throw std::runtime_error{ "WSAStartup failed : " + iResult };
		}

		FD_ZERO(&m_readSet);
		FD_ZERO(&m_writeSet);
	}

	UQACNetwork::~UQACNetwork()
	{
		// cleanup
		WSACleanup();
	}

	TerminalWeakPtr UQACNetwork::Listen(const std::string& url, Config config)
	{
		auto formatUrl = ValidateEndpoint(url);
		
		if (!formatUrl.has_value())
		{
			return {};
		}

		auto terminal = std::make_shared<Terminal>(formatUrl.value(), config);

		mtx.lock();
		FD_SET(terminal->ID(), &m_readSet);
		m_terminals.insert(std::make_pair(terminal->ID(), terminal));
		mtx.unlock();
		return terminal;
	}

	ConnectionWeakPtr UQACNetwork::Connect(const std::string& url, Config config)
	{
		auto formatUrl = ValidateEndpoint(url);

		if (!formatUrl.has_value())
		{
			return {};
		}

		auto connection = std::make_shared<Connection>(formatUrl.value(), config);

		mtx.lock();		
		FD_SET(connection->ID(), &m_readSet);
		m_connections.insert(std::make_pair(connection->ID(), connection));
		mtx.unlock();
		return connection;
	}

	void UQACNetwork::Update(std::chrono::milliseconds timeout)
	{
		mtx.lock();

		FD_ZERO(&m_readSet);

		for (auto& t : m_terminals)
		{
			FD_SET(t.first, &m_readSet);
			auto connections = t.second->GetAllConnection();
			for (auto& c : connections)
			{
				FD_SET(c.first, &m_readSet);
			}
		}

		for (auto& t : m_connections)
		{
			FD_SET(t.first, &m_readSet);
		}


		struct timeval selectTimeout;
		selectTimeout.tv_sec = 0;
		selectTimeout.tv_usec = timeout.count() * 1000;
		auto res = select(0, &m_readSet, NULL, NULL, &selectTimeout);

		if (res == SOCKET_ERROR)
		{
			printf("select() returned with error %d\n", WSAGetLastError());
			mtx.unlock();
			std::this_thread::yield();
			return;
		}

		if (res == 0)
		{
			mtx.unlock();
			std::this_thread::yield();
			return;
		}


		for (auto& t : m_terminals)
		{
			t.second->Update(m_readSet);
		}

		for (auto& c : m_connections)
		{
			if (auto x = FD_ISSET(c.first, &m_readSet))
			{
				c.second->Update();
			}
		}

		mtx.unlock();
		std::this_thread::yield();
	}

	std::optional<URL> UQACNetwork::ValidateEndpoint(const std::string& endpoint)
	{
		std::smatch m;
		std::regex_search(endpoint, m, regex_endpoint);

		if (m.size() == 4)
		{
			URL url{ m[0],m[1] ,m[2] ,m[3] };
			return url;
		}

		return {};
	}

}