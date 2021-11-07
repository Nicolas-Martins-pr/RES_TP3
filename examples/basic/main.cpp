#include <chrono>
#include <mutex>
using namespace std::chrono_literals;
#include <iostream>
#include <thread>

#include "../headers/network/uqacNetwork.hpp"
#include "../headers/network/Terminal.hpp"
#include "../headers/network/Connection.hpp"
#include "../headers/ReplicationManager.h"
#include "../headers/enemy.h"
#include "../headers/player.h"


std::shared_ptr<uqac::network::UQACNetwork> network;
std::shared_ptr<ReplicationManager> replicationManager;

bool g_stop = false;
int countMsgReceive = 0;
int countClient = 0;

std::condition_variable cv;
std::mutex cv_m;

static constexpr char endpoint[] = "tcp//127.0.0.1:42666";

int Server()
{
	uqac::network::Config config;
	config.OnConnect = [](uqac::network::ConnectionWeakPtr connection) {
		std::cout << "SERVER OnConnect" << std::endl;;
		replicationManager->Create(Player::ClassID);
		countClient++;

	};

	if (countClient == 2)
	{
		replicationManager->Create(Enemy::ClassID);
	}

	config.OnReceive = [](uqac::network::ConnectionWeakPtr connection, char* buffer, size_t size) {

		if (auto c = connection.lock()) {
			std::cout << "SERVER RECEIVE : ";
			std::cout.write(buffer, size);
			std::cout << std::endl;
			c->Send(buffer, size);
		}
	};


	auto terminal = network->Listen(endpoint, config);

	cv.notify_all();

	return 0;
}


int Client(int id)
{
	uqac::network::Config config;

	config.OnReceive = [id](uqac::network::ConnectionWeakPtr connection, char* buffer, size_t size) {
		std::cout << "CLIENT "<<id<<" RECEIVE : ";
		std::cout.write(buffer, size);
		std::cout << std::endl;
		countMsgReceive++;
	};

	auto connection = network->Connect(endpoint, config);
	if (auto c = connection.lock()) { 
		auto msg = "HELLO WORLD ! FROM " + std::to_string(id);
		c->Send(msg.data(), msg.length());

	}
	return 0;
}



void Update()
{
	while (!g_stop)
	{
		network->Update(50ms);
		std::this_thread::yield();
	}
}

int main(int argc, char* argv[])
{
	replicationManager = std::make_shared<ReplicationManager>();
	ClassRegistry::get()->saveClass<Player>();
	ClassRegistry::get()->saveClass<Enemy>();

	network = std::make_shared<uqac::network::UQACNetwork>();
	std::thread server(Server);

	
	std::unique_lock<std::mutex> lk(cv_m);
	cv.wait(lk);

	std::thread client(Client,1);
	std::thread client2(Client,2);
	std::thread update(Update);

	while (countMsgReceive < 2)
	{

	}

	g_stop = true;

	if (server.joinable())
		server.join();

	if (client.joinable())
		client.join();

	if (client2.joinable())
		client2.join();

	if (update.joinable())
		update.join();

	return EXIT_SUCCESS;
}