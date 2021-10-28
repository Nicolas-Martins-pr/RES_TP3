#include "Serializer.h"

Serializer::Serializer(int size) {
	container = std::vector<char>();
	position = 0;
	container.resize(size);
}

Serializer::Serializer()
{
	container = std::vector<char>();
	position = 0;
}


