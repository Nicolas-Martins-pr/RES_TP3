#include "../headers/ReplicationManager.h"

#include "../headers/network/Connection.hpp"
#include "../headers/networkObject.h"


ReplicationManager::ReplicationManager()
{
	cont = new LinkingContext();
}

void ReplicationManager::Update(std::vector<uqac::network::ConnectionWeakPtr> clientsPtrList)
{
	paquetID++;

	Serializer* ser = new Serializer();

	//serialiser identifiants de protocole (toujours tcp==1) et de paquet
	ser->Serialize<int>(1, sizeof(int));
	ser->Serialize<int>(paquetID, sizeof(paquetID));

	//boucle : pour chaque network object
		//serialiser identifiants d'objet et de classe
		//serialiser objet 
	for (std::pair<NetworkObject*, int> networkObj : cont->GetGOPointerToIDMap())
	{
		//We send the class ID
		ser->Serialize<int>(networkObj.first->GetClassID(), sizeof(networkObj.first->GetClassID()));
		ser->Serialize<int>(networkObj.second, sizeof(networkObj.second));
		networkObj.first->write(ser);
	}

	//On envoie le buffer de données à tous les clients
	for (auto clientPtr : clientsPtrList) {
		auto clientConnection = clientPtr.lock();
		clientConnection->Send(ser->GetContainer().data(), ser->GetContainer().size());
	}
	
}


void ReplicationManager::Decode(const char* buff, size_t size)
{

	std::vector<char> container(buff, buff + size);

	Deserializer* des = new Deserializer(container, container.size());

	//deserialiser identifiants de protocole et de paquet 
	int idProtocol = des->Read<int>();
	int idPaquet = des->Read<int>();

	std::cout << "Protocole du paquet : "<< idProtocol << ".ID du paquet : " << idPaquet << std::endl;


	int firstClass = des->Read<int>();

	//Tant qu'il y'a des joueurs et des enemis a déserialiser
	while (firstClass == 1 || firstClass == 2)
	{

		std::cout << "---------------------------------------------------- " << std::endl;

		int objectNetworkID = des->Read<int>();

		std::cout << "Network ID de l'objet : " << objectNetworkID << std::endl;

		std::function<NetworkObject* ()> constructor = ClassRegistry::get()->GetRegistre().at(firstClass);
		auto newNetworkObject = constructor();
		newNetworkObject->read(des);

		//Si l'objet existe dans notre liste d'objets déjà répliqués (en passant par linkingcontext pour récupérer le pointeur correspondant)
		std::optional<NetworkObject*> tempObject = cont->GetGOPointerFromID(objectNetworkID);
		if (alreadyReplicatedObjects.find(tempObject.value()) == alreadyReplicatedObjects.end())
		{
			//On met à jour l'objet existant
			std::optional<NetworkObject*> alreadyReplicatedObject = cont->GetGOPointerFromID(objectNetworkID);
			alreadyReplicatedObject = newNetworkObject;
		} else
		{
			//Ajouter l'objet dans le linkingcontext et les objets répliqués du réplicationManager
			cont->AddGOPointerandNetworkID(newNetworkObject, objectNetworkID);
			alreadyReplicatedObjects.insert(newNetworkObject);
		}
		firstClass = des->Read<int>();

		
	}

}



void ReplicationManager::Create(uint32_t id)
{
	NetworkObject * obj = ClassRegistry::get()->Create(id);
	alreadyReplicatedObjects.insert(obj);
	cont->AddGOPointer(obj);

}
