#include "../headers/ClassRegistry.h"

#include "../headers/player.h"


ClassRegistry* ClassRegistry::singleton = nullptr;

ClassRegistry::ClassRegistry()
{
	registre = std::map<uint32_t, std::function<NetworkObject*()>>();

}

NetworkObject * ClassRegistry::Create(uint32_t classID)
{
	std::function<NetworkObject*()> classConstruct = registre.at(classID);
	return classConstruct();
}
