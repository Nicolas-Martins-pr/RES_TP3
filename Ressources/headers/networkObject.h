#ifndef NETWORKOBJECT_H
#define NETWORKOBJECT_H


#include "Framework.h"

class NetworkObject
{
public:
	virtual void write();
	virtual void read();
	virtual void destroy();
	NetworkObject();

private:
};

#endif // NETWORKOBJECT_H
