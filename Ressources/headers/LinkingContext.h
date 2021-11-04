#ifndef LINKINGCONTEXT_H
#define LINKINGCONTEXT_H

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

private:

	std::map<NetworkObject*, int> GOPointertoIDMap;
	std::map<int, NetworkObject*> IDToGOPointerMap;

};
#endif // LINKINGCONTEXT_H
