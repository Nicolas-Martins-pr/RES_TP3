#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif
#define ASIO_STANDALONE

#include <iostream>
//#include <asio.hpp>
//#include <asio/ts/buffer.hpp>
//#include <asio/ts/internet.hpp>
#include "ClassRegistry.h"


int main()
{

	asio::error_code ec;

	//Create a "context" - essentially the platform specific interface
	asio::io_context context;

	//Get the address of somewhere we wish to connect to
	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("127.0.0.1", ec), 27000);

	//Create a socket, the context will deliver the implementation
	asio::ip::tcp::socket socket(context);

	//Tell socket to try and connect
	socket.connect(endpoint, ec);

	if(!ec)
	{
		std::cout << "Connected!" << std::endl;
	} else
	{
		std::cout << "Failed to connect to address : \n" << ec.message() << std::endl;
	}

	//Connection is open
	if (socket.is_open())
	{
		std::string sMessage = "Sending message to say hello";

		socket.write_some(asio::buffer(sMessage.data(), sMessage.size()), ec);

		size_t bytes = socket.available();
		std::cout << "Bytes available : " << bytes << std::endl;

		if(bytes > 0)
		{
			std::vector<char> vBuffer(bytes);
			socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()), ec);

			for (auto c : vBuffer)
			{
				std::cout << c;
			}
		}
	}

	std::cout << "Test" << std::endl;
	return 0;
}
