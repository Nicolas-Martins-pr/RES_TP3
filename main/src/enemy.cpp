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


void Enemy::SetHealth(int newHealth)
{
	if (newHealth < healthMin)
		health = healthMin;
	else if (newHealth > healthMax)
		health = healthMax;
	else
		health = newHealth;
}