#include "../headers/ReplicationManager.h"



ReplicationManager::ReplicationManager()
{
	cont = new LinkingContext();
}

void ReplicationManager::Update()
{
	Serializer* ser = new Serializer();

	//serialiser identifiants protocole et paquet

	//boucle : pour chaque objet (soit par linkingcontext soit par id et cont.at())
		//serialiser identifiants classe et objet
		//serialiser objet
	for (std::pair<NetworkObject*, int> networkObj : cont->GetGOPointerToIDMap())
	{
		ser->Serialize(networkObj.second, sizeof(networkObj.second));
		//networkObj.first->write(ser);
	}

	//update le unordered_set
}

void ReplicationManager::Create(uint32_t id)
{
	NetworkObject obj = ClassRegistry::get()->Create(id);
	cont->AddGOPointer(&obj);

}
