#include <unordered_set>
#include "NetworkObject.h"
#include "LinkingContext.h"
#include "asio.hpp"
class ReplicationManager
{

public : 
	ReplicationManager();
	void Update();
	std::unordered_set<NetworkObject*> GetPointObject()const { return pointObject; };
private:

	std::unordered_set<NetworkObject*> pointObject;
	LinkingContext cont;

};