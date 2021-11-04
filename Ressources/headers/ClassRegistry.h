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
	ClassRegistry(const ClassRegistry&) = delete; //emp�che le constructeur par copie
	ClassRegistry& operator=(const ClassRegistry&) = delete; //emp�che l'op�rateur d'affectation

	//permet l'instanciation unique :
	static ClassRegistry* get()
{
	if (!singleton)
		singleton = new ClassRegistry;
	return singleton;

}
	void Create(uint32_t classID);

};
#endif // CLASSREGISTRY_H
