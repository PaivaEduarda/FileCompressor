#pragma once
#include <string>
#include <iostream>
#include <map>
#include <fstream>
using namespace std;

class FrequencyCounter {
    map<unsigned char, int> frequencyMap;

public:
    const map<unsigned char, int>& getFrequencyMap() const;
    void readFile(string fileName);


};