#include "../headers/Player.h"

Player::Player(Vector3<float> position, Vector3<float> taille, Quaternion rotation, int hp, int armor, float money,
	char* playerName)
{
	name = new char[129];
	SetPosition(position);
	SetTaille(taille);
	SetRotation(rotation);
	SetHealth(hp);
	SetArmor(armor);
	SetMoney(money);
	SetName(playerName);
}

Player::Player()
{
	name = new char[129];
	Vector3<float> defaultPosition;
	defaultPosition.vx = 0.0;
	defaultPosition.vy = 0.0;
	defaultPosition.vz = 0.0;
	SetPosition(defaultPosition);
	Vector3<float> defaultTaille;
	defaultTaille.vx = 1.0;
	defaultTaille.vy = 1.0;
	defaultTaille.vz = 1.0;
	SetTaille(defaultTaille);
	Quaternion defaultRotation;
	defaultRotation.val_w = 0.194;
	defaultRotation.val_x = -0.003;
	defaultRotation.val_y = -0.931;
	defaultRotation.val_z = 0.310;
	SetRotation(defaultRotation);
	SetHealth(150);
	SetArmor(25);
	SetMoney(0);
	SetName("Patrick");
}

void Player::write(Serializer* ser) {
	
	position.write(ser);
	taille.write(ser);
	rotation.write(ser);
	ser->Serialize<int>(health, sizeof(health));
	ser->Serialize<int>(armor, sizeof(armor));
	ser->Serialize<float>(money, sizeof(money));
	ser->Serialize<char*>(name, sizeof(name));
}

void Player::read(Deserializer* des)
{
	position.read(des);
	taille.read(des);
	rotation.read(des);
	health = des->Read<int>();
	armor = des->Read<int>();
	money = des->Read<float>();
	name = des->Read<char*>();

	printInfos();
}

void Player::printInfos()
{

	std::cout << "Informations sur le joueur " << name << std::endl;
	std::cout << "Position : " << position.vx << "/" << position.vy << "/" << position.vz << std::endl;
	std::cout << "Taille : " << taille.vx << "/" << taille.vy << "/" << taille.vz << std::endl;
	std::cout << "Rotation : " << rotation.val_w << "/" << rotation.val_x << "/" << rotation.val_y << "/" << rotation.val_z << std::endl;
	std::cout << "Vie : " << health << std::endl;
	std::cout << "Armure : " << armor << std::endl;
	std::cout << "Argent : " << money << std::endl;
}

void Player::SetPosition(Vector3<float> newPosition)
{
	if (newPosition.vx < -500)
		position.vx = -500;
	else if (newPosition.vx > 500)
		position.vx = 500;
	else
		position.vx = newPosition.vx;
	if (newPosition.vy < -500)
		position.vy = -500;
	else if (newPosition.vy > 500)
		position.vy = 500;
	else
		position.vy = newPosition.vy;
	if (newPosition.vz < 0)
		position.vz = 0;
	else if (newPosition.vz > 100)
		position.vz = 100;
	else
		position.vz = newPosition.vz;

}

void Player::SetTaille(Vector3<float> newTaille)
{
	taille = newTaille;
}

void Player::SetRotation(Quaternion newRotation)
{
	rotation = newRotation;
}

void Player::SetHealth(int newHealth)
{
	if (newHealth < healthMin)
		health = healthMin;
	else if (newHealth > healthMax)
		health = healthMax;
	else
		health = newHealth;
}

void Player::SetArmor(int newArmor)
{
	if (newArmor < armorMin)
		armor = armorMin;
	else if (newArmor > armorMax)
		armor = armorMax;
	else
		armor = newArmor;
}

void Player::SetMoney(float newMoney)
{
	if (newMoney < moneyMin)
		money = moneyMin;
	else if (newMoney > moneyMax)
		money = moneyMax;
	else
		money = newMoney;
}

void Player::SetName(char* newName)
{
	if (strlen(newName) >= nameMaxSize)
	{
		memcpy(name, newName, nameMaxSize);
		name[128] = '\0';
	}
	else
		name = newName;


}

NetworkObject* Player::Create()
{
	return new Player();
}

void Player::UpdateValues()
{
	name = new char[129];
	Vector3<float> newPosition;
	newPosition.vx = 200.0;
	newPosition.vy = 100.0;
	newPosition.vz = 50.0;
	SetPosition(newPosition);
	Vector3<float> newTaille;
	newTaille.vx = 1.5;
	newTaille.vy = 1.5;
	newTaille.vz = 1.5;
	SetTaille(newTaille);
	Quaternion newRotation;
	newRotation.val_w = 0.310;
	newRotation.val_x = -0.003;
	newRotation.val_y = -0.310;
	newRotation.val_z = -0.931;
	SetRotation(newRotation);
	SetHealth(50);
	SetArmor(0);
	SetMoney(15000);
	SetName("Jack");
}
