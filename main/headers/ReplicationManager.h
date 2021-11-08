#pragma once
#include <unordered_set>
#include "networkObject.h"
#include "LinkingContext.h"
#include "ClassRegistry.h"
#include "Serializer.h"
#include "network/NetworkFramework.hpp"

class ReplicationManager
{

public : 
	ReplicationManager();
	void Update(std::vector<uqac::network::ConnectionWeakPtr> clientsList);
	void Decode(const char* buff, size_t size);
	void Create(uint32_t id);
	[[nodiscard]] std::unordered_set<NetworkObject*> GetPointObject()const { return alreadyReplicatedObjects; };
	[[nodiscard]] LinkingContext * GetLinkingContext ()const { return cont; };
private:

	int paquetID = 0;
	std::unordered_set<NetworkObject*> alreadyReplicatedObjects;
	LinkingContext *cont;

};
