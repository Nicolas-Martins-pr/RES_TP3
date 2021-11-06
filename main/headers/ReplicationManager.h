#pragma once
#include <unordered_set>
#include "NetworkObject.h"
#include "LinkingContext.h"
#include "ClassRegistry.h"
#include "Serializer.h"

class ReplicationManager
{

public : 
	ReplicationManager();
	void Update();
	void Create(uint32_t id);
	[[nodiscard]] std::unordered_set<NetworkObject*> GetPointObject()const { return pointObject; };
private:

	std::unordered_set<NetworkObject*> pointObject;
	LinkingContext *cont;

};