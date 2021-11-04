#ifndef CLASSREGISTRY_H
#define CLASSREGISTRY_H

class ClassRegistry
{
private :
	static ClassRegistry* singleton;
	ClassRegistry();

public :
	static ClassRegistry* get()
{
	if (!singleton)
		singleton = new ClassRegistry;
	return singleton;

}

};
#endif // CLASSREGISTRY_H
