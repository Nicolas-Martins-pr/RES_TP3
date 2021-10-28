#include "Framework.h"

class NetworkObject
{
public:
	virtual void write();
	virtual void read();
	virtual void destroy();

private:
};