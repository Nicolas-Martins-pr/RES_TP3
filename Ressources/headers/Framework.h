#include <cstdint>
#include <iostream>
#include <algorithm>
#include "Serializer.h"
#include "Deserializer.h"

struct Quaternion
{
	float val_w;
	float val_x;
	float val_y;
	float val_z;

	void write(Serializer* ser) {
		ser->Serialize<float>(val_w, sizeof(val_w));
		ser->Serialize<float>(val_x, sizeof(val_x));
		ser->Serialize<float>(val_y, sizeof(val_y));
		ser->Serialize<float>(val_z, sizeof(val_z));
	}

	void read(Deserializer* des) {
		val_w = des->Read<float>();
		val_x = des->Read<float>();
		val_y = des->Read<float>();
		val_z = des->Read<float>();
	}

};

template <typename T>
struct Vector3 {

	float vx, vy, vz;

	void write(Serializer * ser) {
		ser->Serialize<T>(vx, sizeof(vx));
		ser->Serialize<T>(vy, sizeof(vy));
		ser->Serialize<T>(vz, sizeof(vz));
	}

	void read(Deserializer * des) {
		vx = des->Read<T>();
		vy = des->Read<T>();
		vz = des->Read<T>();
	}
};


enum class PlatformEndianness
{
	BigEndian,
	LittleEndian
};

constexpr PlatformEndianness DetectEndianness()
{

	union
	{
		uint32_t i;
		char c[4];
	} testEndian = { 0x01020304 };

	return (testEndian.c[0] == 1) ? PlatformEndianness::BigEndian : PlatformEndianness::LittleEndian;
}

template<typename T>
void SwapEndian(T &val)
{

	union U
	{
		T val;
		std::array<std::uint8_t, sizeof(T)> raw;
	} src, dst;

	src.val = val;
	std::reverse_copy(src.raw.begin(), src.raw.end(), dst.raw.begin());
	val = dst.val;
}