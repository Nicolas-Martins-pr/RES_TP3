#include "../headers/Enemy.h"

Enemy::Enemy()
{
	Vector3<float> defaultPosition;
	defaultPosition.vx, defaultPosition.vy, defaultPosition.vz = 0;
	pos = defaultPosition;
	Quaternion defaultRotation;
	defaultRotation.val_w = 0.194;
	defaultRotation.val_x = -0.003;
	defaultRotation.val_y = -0.931;
	defaultRotation.val_z = 0.310;
	rot = defaultRotation;
	enemyType = Sbire;
	SetHealth(1000);
}

NetworkObject* Enemy::Create()
{
	return new Enemy();
}

void Enemy::write(Serializer* ser)
{
	//We send the class ID
	ser->Serialize<int>(static_cast<int>(this->ClassID), sizeof static_cast<int>(this->ClassID));
	pos.write(ser);
	rot.write(ser);
	ser->Serialize<type>(enemyType, sizeof(enemyType));
	ser->Serialize<int>(health, sizeof(health));
}

void Enemy::read(Deserializer* des)
{
	pos.read(des);
	rot.read(des);
	enemyType = des->Read<type>();
	health = des->Read<int>();
}


void Enemy::SetHealth(int newHealth)
{
	if (newHealth < healthMin)
		health = healthMin;
	else if (newHealth > healthMax)
		health = healthMax;
	else
		health = newHealth;
}
