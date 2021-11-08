#pragma once

#include "NetworkObject.h"

class Enemy : public NetworkObject
{

	public :

		Enemy();

		enum { ClassID = 2 };

		int GetClassID() override { return ClassID; };

		static NetworkObject * Create();

		void write(Serializer* ser) override;
		void read(Deserializer* des) override;

		void SetHealth(int newHealth);

		void UpdateValues() override;

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
