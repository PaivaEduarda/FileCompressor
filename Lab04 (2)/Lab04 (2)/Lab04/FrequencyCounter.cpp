#include "FrequencyCounter.h"

void FrequencyCounter::readFile(string fileName) {
	unsigned char character;
	ifstream inputFile;

	inputFile.open(fileName, ios::binary);

	while (inputFile.read(reinterpret_cast<char*>(&character), sizeof(character)))
		frequencyMap[character]++;

	inputFile.close();
}


const map<unsigned char, int>& FrequencyCounter::getFrequencyMap() const {
	return frequencyMap;
}