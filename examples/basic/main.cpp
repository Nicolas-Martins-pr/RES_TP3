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

bool updateVals = false;
bool g_stop = false;
int countMsgReceive = 0;
int countClientConnected = 0;

std::vector<uqac::network::ConnectionWeakPtr> clientsPtr;

std::condition_variable cv;
std::mutex cv_m;

static constexpr char endpoint[] = "tcp//127.0.0.1:42666";


void UpdatePlayersAndEnemyValues()
{


	std::cout << "Press enter to update players and enemy values (not randomly) : ";
	std::cin.ignore();

	for (auto object : replicationManager->GetLinkingContext()->GetGOPointerToIDMap())
	{
		object.first->UpdateValues();
		
		std::cout << object.first->ClassID << std::endl;
	}

	replicationManager->Update(clientsPtr);

}

int Server()
{

	uqac::network::Config config;
	config.OnConnect = [](uqac::network::ConnectionWeakPtr connection) {
		std::cout << "A client is connecting : a new player is created" << std::endl;
		replicationManager->Create(Player::ClassID);
		clientsPtr.push_back(connection);
		countClientConnected++;

		if (countClientConnected == 2)
		{
			replicationManager->Create(Enemy::ClassID);
			std::cout << "Two players are connected : a new enemy is created" << std::endl;

			replicationManager->Update(clientsPtr);
		}

	};

	config.OnReceive = [](uqac::network::ConnectionWeakPtr connection, char* buffer, size_t size) {

		if (auto c = connection.lock()) {
			std::cout << "Server receiving : ";
			std::cout.write(buffer, size);
			std::cout << std::endl;
			//Send the message to all clients except the one we receive the message from
			for (auto clientPtr : clientsPtr) {
				auto clientConnection = clientPtr.lock();
				if (clientConnection != c)
					clientConnection->Send(buffer, size);
			}
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

		std::cout << "------------------------------------------------------------------------------" << std::endl;
		std::cout << "Client "<<id<<" receives data : " << std::endl;
		//On décode les données du serveur
		replicationManager->Decode(buffer, size);
		std::cout << "------------------------------------------------------------------------------" << std::endl;
		countMsgReceive++;
	};

	auto connection = network->Connect(endpoint, config);
	if (auto c = connection.lock()) {
		auto msg = " Hi I'm the player  " + std::to_string(id);
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
