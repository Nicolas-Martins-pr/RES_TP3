#include "ClassRegistry.h"

ClassRegistry* ClassRegistry::singleton = nullptr;

ClassRegistry::ClassRegistry()
{
}

NetworkObject ClassRegistry::Create(uint32_t classID)
{
	std::function<NetworkObject()> classConstruct = registre.at(classID);
	return classConstruct();

}
