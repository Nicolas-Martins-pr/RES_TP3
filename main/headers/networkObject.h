#pragma once
#include "Framework.h"

class NetworkObject
{
public:
	virtual ~NetworkObject() = default;
	virtual void write(Serializer* ser) = 0;
	virtual void read(Deserializer* ser) = 0;
	virtual void destroy();
	NetworkObject();

private:

};


