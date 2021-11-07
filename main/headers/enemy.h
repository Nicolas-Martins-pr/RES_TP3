#pragma once

#include "NetworkObject.h"

class Enemy : public NetworkObject
{

	public :

		Enemy();

		enum { ClassID = 1 };

		static NetworkObject * Create();

		void SetHealth(int newHealth);

	private :

		Vector3<float> pos;
		enum type
		{
			Boss,
			Sbire
		} enemyType;

		Quaternion rot;
		int health;
		int healthMax = 1000;
		int healthMin = 0;
};
