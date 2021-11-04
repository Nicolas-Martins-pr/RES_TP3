#include "LinkingContext.h"

LinkingContext::LinkingContext()
{
}

void LinkingContext::AddGOPointerandNetworkID(NetworkObject* networkObj, int id)
{
	GOPointertoIDMap.insert(std::pair<NetworkObject*, int>(networkObj, id));
	IDToGOPointerMap.insert(std::pair<int, NetworkObject*>(id, networkObj));
}


void LinkingContext::DeletePointer(NetworkObject* networkObj)
{
	int tempID = GOPointertoIDMap.at(networkObj);
	GOPointertoIDMap.erase(networkObj);
	IDToGOPointerMap.erase(tempID);
}

void LinkingContext::AddGOPointer(NetworkObject* networkObj)
{
	//TODO Create network ID
	GOPointertoIDMap.insert(std::pair<NetworkObject*, int>(networkObj, 0));
	IDToGOPointerMap.insert(std::pair<int, NetworkObject*>(0, networkObj));
}

std::optional<int> LinkingContext::GetIdFromGOPointer(NetworkObject* networkObj)
{
	return GOPointertoIDMap.at(networkObj);
}

std::optional<NetworkObject*> LinkingContext::GetGOPointerFromID(int id)
{
	return IDToGOPointerMap.at(id);
}
