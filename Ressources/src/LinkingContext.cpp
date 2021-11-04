#include "LinkingContext.h"

LinkingContext::LinkingContext()
{
}

void LinkingContext::AddGOPointerandNetworkID(NetworkObject* networkObj, int id)
{
	GOPointerToIDMap.insert(std::pair<NetworkObject*, int>(networkObj, id));
	IDToGOPointerMap.insert(std::pair<int, NetworkObject*>(id, networkObj));
}


void LinkingContext::DeletePointer(NetworkObject* networkObj)
{
	int tempID = GOPointerToIDMap.at(networkObj);
	GOPointerToIDMap.erase(networkObj);
	IDToGOPointerMap.erase(tempID);
}

void LinkingContext::AddGOPointer(NetworkObject* networkObj)
{
	int randomNetworkID = rand();

	//TODO Check if working
	while (IDToGOPointerMap.at(randomNetworkID))
	{
		randomNetworkID = rand();
	}
	GOPointerToIDMap.insert(std::pair<NetworkObject*, int>(networkObj, randomNetworkID));
	IDToGOPointerMap.insert(std::pair<int, NetworkObject*>(randomNetworkID, networkObj));
}

std::optional<int> LinkingContext::GetIdFromGOPointer(NetworkObject* networkObj)
{
	return GOPointerToIDMap.at(networkObj);
}

std::optional<NetworkObject*> LinkingContext::GetGOPointerFromID(int id)
{
	return IDToGOPointerMap.at(id);
}
