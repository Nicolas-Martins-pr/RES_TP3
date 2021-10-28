#include "LinkingContext.h"

LinkingContext::LinkingContext()
{
}

void LinkingContext::AddPointerToGOandNetworkID(NetworkObject* networkObj, int id)
{
	PointertoIDMap.insert(std::pair<NetworkObject*, int>(networkObj, id));
	IDToPointerMap.insert(std::pair<int, NetworkObject*>(id, networkObj));
}


void LinkingContext::DeletePointer(NetworkObject* networkObj)
{
	int tempID = PointertoIDMap.at(networkObj);
	PointertoIDMap.erase(networkObj);
	IDToPointerMap.erase(tempID);
}

void LinkingContext::AddPointerToGO(NetworkObject* networkObj)
{
	//TODO Create network ID
	PointertoIDMap.insert(std::pair<NetworkObject*, int>(networkObj, 0));
	IDToPointerMap.insert(std::pair<int, NetworkObject*>(0, networkObj));
}
