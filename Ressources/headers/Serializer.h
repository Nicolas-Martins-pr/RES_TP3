#pragma once
#include <vector>

class Serializer {

public:
	Serializer(int size);
	Serializer();

    template<typename T>
	void Serialize(T val, size_t size)
	{

		if (container.size() <= position + size)
		{
			container.resize(container.size() + size);
		}

		memcpy(container.data() + position, & val, size);
		position += size;
	}

    std::vector<char> GetContainer() const {return container;}
private:
	std::vector<char> container;
	int position;
};