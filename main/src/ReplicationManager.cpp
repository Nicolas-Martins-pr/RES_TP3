#include "../headers/ReplicationManager.h"



ReplicationManager::ReplicationManager()
{
	cont = new LinkingContext();
}

void ReplicationManager::Update()
{
	paquetID++;

	Serializer* ser = new Serializer();

	//serialiser identifiants de protocole (toujours tcp==1) et de paquet
	ser->Serialize<int>(1, sizeof(int));
	ser->Serialize<int>(paquetID, sizeof(paquetID));

	//boucle : pour chaque network object
		//serialiser identifiants d'objet
		//serialiser objet (identifiant de classe compris dans la fonction du player)
	for (std::pair<NetworkObject*, int> networkObj : cont->GetGOPointerToIDMap())
	{
		ser->Serialize<int>(networkObj.second, sizeof(networkObj.second));
		networkObj.first->write(ser);
	}



	//update le unordered_set
	//paquet counter


	//return somtehing to deserialize ???,
}

void ReplicationManager::Create(uint32_t id)
{
	NetworkObject * obj = ClassRegistry::get()->Create(id);
	cont->AddGOPointer(obj);

}
