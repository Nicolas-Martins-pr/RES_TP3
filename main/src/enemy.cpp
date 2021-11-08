#include "../headers/Enemy.h"

Enemy::Enemy()
{
	Vector3<float> defaultPosition;
	defaultPosition.vx = 0.0;
	defaultPosition.vy = 0.0;
	defaultPosition.vz = 0.0;
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


	std::cout << "Informations sur l'ennemi " << std::endl;
	std::cout << "Position : " << pos.vx << "/" << pos.vy << "/" << pos.vz << std::endl;
	std::cout << "Rotation : " << rot.val_w << "/" << rot.val_x << "/" << rot.val_y << "/" << rot.val_z << std::endl;
	std::cout << "Type : " << enemyType << std::endl;
	std::cout << "Vie : " << health << std::endl;
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

void Enemy::UpdateValues()
{

	SetHealth(0);
	Vector3<float> newPos;
	newPos.vx = 50;
	newPos.vy = 50;
	newPos.vz = 50;
	pos = newPos;
	Quaternion newRot;
	newRot.val_w = 0.021;
	newRot.val_x = 0.035;
	newRot.val_y = 0.849;
	newRot.val_z = 0.745;
	rot = newRot;
	enemyType = type::Boss;
}
