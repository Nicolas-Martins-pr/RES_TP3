#include "../headers/Deserializer.h"



Deserializer::Deserializer(std::vector<char> container, size_t size) {
	containerToRead = container;
	sizeOfContainer = size;
}

