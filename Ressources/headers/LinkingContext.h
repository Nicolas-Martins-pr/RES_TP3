#pragma once
#include <map>
#include <optional>
#include "networkObject.h"

class LinkingContext
{
public:

	LinkingContext();
	void AddGOPointerandNetworkID(NetworkObject* networkObj, int id);
	void DeletePointer(NetworkObject* networkObj);
	void AddGOPointer(NetworkObject* networkObj);
	std::optional<int> GetIdFromGOPointer(NetworkObject* networkObj);
	std::optional<NetworkObject*> GetGOPointerFromID(int id);
	std::map<NetworkObject*, int> GetGOPointerToIDMap() {
		return GOPointerToIDMap;};

private:

	std::map<NetworkObject*, int> GOPointerToIDMap;
	std::map<int, NetworkObject*> IDToGOPointerMap;

};
