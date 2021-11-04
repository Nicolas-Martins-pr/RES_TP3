#ifndef ENEMY_H
#define ENEMY_H

#include "NetworkObject.h"

class Enemy : public NetworkObject
{
	public :

private :

	enum { ClassID = 1 };
	Vector3<float> pos;
	enum Type
	{
		Boss,
		Sbire
	};

	Quaternion rot;
	int health;
	int healthMax = 1000;
	int healthMin = 0;
};
#endif // ENEMY_H
