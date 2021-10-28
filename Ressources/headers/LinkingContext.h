#include <map>

#include "NetworkObject.h"


class LinkingContext
{
public:
	LinkingContext();
	void AddPointerToGOandNetworkID(NetworkObject* networkObj, int id);
	void DeletePointer(NetworkObject* networkObj);
	void AddPointerToGO(NetworkObject* networkObj);

private:

	std::map<NetworkObject*, int> PointertoIDMap;

	std::map<int, NetworkObject*> IDToPointerMap;

};