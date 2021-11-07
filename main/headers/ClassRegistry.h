
#pragma once
#include <cstdint>
#include <functional>
#include <map>
#include "networkObject.h"

class ClassRegistry
{
private :
	static ClassRegistry* singleton;
	ClassRegistry();
	std::map<uint32_t, std::function<NetworkObject*()>> registre;

public :
	ClassRegistry(const ClassRegistry&) = delete; //empêche le constructeur par copie
	ClassRegistry& operator=(const ClassRegistry&) = delete; //empêche l'opérateur d'affectation

	//permet l'instanciation unique :
	static ClassRegistry* get()
{
	if (!singleton)
		singleton = new ClassRegistry;
	return singleton;

}
	NetworkObject * Create(uint32_t classID);

	template<class T>
	void saveClass()
	{
		registre.insert(std::pair<uint32_t, std::function<NetworkObject* ()>>(T::ClassID, T::Create));
	}

};
