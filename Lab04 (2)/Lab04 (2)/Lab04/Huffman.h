#include <string.h>
#include <iostream>
#include <unordered_map>
#include <map>
#include <fstream>
#include <iostream>
#include "Node.h"

using namespace std;

class Huffman {
    unordered_map<unsigned char, string> codeMap;
    map<unsigned char, int> frequencyMap;
    void encodeCharacters(Node* rootNode, string codeString);
    void writeHeader(ofstream& outputStream);
    void readHeader(ifstream& inputStream);
    Node* buildDecodingTree(unordered_map<unsigned char, string> encodingMap);

public:
    Node* huffer(map<unsigned char, int> frequencyMap);
    void deHuffer(string fileName, string decompressedFileName);
    void compressTofile(string InputfileName, string OutputfileName);
    void decompressToFile(string codeString, Node* rootNode, string decompressedFileName);
};