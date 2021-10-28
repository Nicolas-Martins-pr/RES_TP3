#ifndef RES_TP2_DESERIALIZER_H
#define RES_TP2_DESERIALIZER_H


#include <vector>

class Deserializer {

public:
	Deserializer(std::vector<char> container, size_t size);
    template<typename T>
	T Read() {
		T val;
		memcpy(&val, containerToRead.data() + position, sizeof(val));
		position += sizeof(val);
		return val;
	}

	int GetPosition() const { return position; }
	std::vector<char> GetContainerToRead() const { return containerToRead; }
private:
	int position = 0;
	std::vector<char> containerToRead;
	size_t sizeOfContainer;
};



#endif //RES_TP2_DESERIALIZER_H