#ifndef CLASSREGISTRY_H
#define CLASSREGISTRY_H
#include <cstdint>

class ClassRegistry
{
private :
	static ClassRegistry* singleton;
	ClassRegistry();
	//std::map<uint32_t, >

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
	void Create(uint32_t classID);

	template<typename T>
	T saveClass(const T& myClass)
	{
		//todo: enregistrer myClass dans le registre
	}

};
#endif // CLASSREGISTRY_H
