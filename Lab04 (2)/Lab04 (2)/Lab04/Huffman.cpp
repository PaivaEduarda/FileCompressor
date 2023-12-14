#include "Huffman.h"
#include <queue>
#include <bitset>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#define INTERNAL_NODE_CHARACTER char(128)
#define PSEUDO_EOF char(129)
#define CHARACTER_CODE_SEPERATOR char(130)
#define HEADER_ENTRY_SEPERATOR char(131)
#define HEADER_TEXT_SEPERATOR char(132)

struct myCompartor {
	bool operator()(Node* const& node1, Node* const& node2) {
		return node1->getFrequency() > node2->getFrequency();
	}
};

Node* Huffman::huffer(map<unsigned char, int> frequencyMap) {
	this->frequencyMap = frequencyMap;
	priority_queue <Node*, vector<Node*>, myCompartor> HufferQueue;
	string tempString;
	Node* leftNode, * rightNode, * newNode;
	for (const auto& item : frequencyMap)
		HufferQueue.push(new Node(item.first, item.second));
	while (HufferQueue.size() != 1) {
		leftNode = HufferQueue.top();
		HufferQueue.pop();
		rightNode = HufferQueue.top();
		HufferQueue.pop();
		newNode = new Node('#', leftNode->getFrequency() + rightNode->getFrequency());
		HufferQueue.push(newNode);
		newNode->setLeft(leftNode);
		newNode->setRight(rightNode);
	}
	encodeCharacters(HufferQueue.top(), tempString);

	return HufferQueue.top();
}

void Huffman::encodeCharacters(Node* rootNode, string codeString) {

	if (!rootNode)
		return;
	if (rootNode->getLeft() == nullptr && rootNode->getRight() == nullptr) {
		codeMap[rootNode->getCharacter()] = codeString;
	}

	encodeCharacters(rootNode->getLeft(), codeString + "0");
	encodeCharacters(rootNode->getRight(), codeString + "1");
}

void Huffman::compressTofile(string InputfileName, string OutputfileName) {
	char character;
	string file;
	ifstream inputStream(InputfileName, ios::binary);
	ofstream outputStream(OutputfileName, ios::binary);

	// Verifica se os arquivos foram abertos corretamente
	if (!inputStream.is_open() || !outputStream.is_open()) {
		cerr << "Erro ao abrir o arquivo de entrada ou saída." << endl;
		return;
	}

	// Escreve o cabeçalho no arquivo de saída
	writeHeader(outputStream);

	// Lê o arquivo de entrada e constrói a string de bits
	while (inputStream.get(character)) {
		if (codeMap.find(character) != codeMap.end()) {
			file += codeMap[character];
		}
		else {
			cerr << "Erro: caractere não encontrado no mapa de códigos." << endl;
			return;
		}
	}

	// Adiciona zeros para garantir um número completo de bytes
	unsigned int remainder = file.size() % 8;
	if (remainder != 0) {
		file += string(8 - remainder, '0');
	}

	// Write remainder to file:
	outputStream.write(reinterpret_cast<const char*>(&remainder), sizeof(remainder));

	// Converte a string de bits para bytes e escreve no arquivo de saída
	for (size_t i = 0; i < file.size(); i += 8) {
		bitset<8> bits(file.substr(i, 8));
		outputStream.put(static_cast<char>(bits.to_ulong()));
	}

	inputStream.close();
	outputStream.close();
}


void Huffman::writeHeader(ofstream& outputStream) {
	int size = frequencyMap.size();
	outputStream.write(reinterpret_cast<const char*>(&size), sizeof(size));
	for (const auto& item : frequencyMap) {
		outputStream << item.first;
		outputStream.write(reinterpret_cast<const char*>(&item.second), sizeof(item.second));
	}
}

void Huffman::deHuffer(string compressedFileName, string decompressedFileName) {
	char character;
	string codeString;
	//ifstream inputStream;
	//inputStream.open(compressedFileName, ios::binary);
	ifstream input(compressedFileName, ios::binary);
	if (!input)
	{
		cerr << "Erro! Arquivo não localizado.";
		exit(-2);
	}
	readHeader(input);

	int remainder;
	input.read(reinterpret_cast<char*>(&remainder), sizeof(remainder));

	while (input.get(character)) {
		bitset<8> bits(character);
		codeString += bits.to_string();
	}

	codeString = codeString.substr(0, codeString.size() - remainder);

	Node* rootNode = huffer(frequencyMap);

	decompressToFile(codeString, rootNode, decompressedFileName);
}

void Huffman::readHeader(ifstream& inputStream) {
	frequencyMap.clear();
	unsigned char character;

	// Lê a quantidade de caracteres no cabeçalho
	int numberOfCharacters;
	inputStream.read(reinterpret_cast<char*>(&numberOfCharacters), sizeof(numberOfCharacters));

	// Lê o cabeçalho
	for (int i = 0; i < numberOfCharacters; i++) {
		// Ler char
		inputStream.read(reinterpret_cast<char*>(&character), sizeof(character));

		// ler int
		int frequency;
		inputStream.read(reinterpret_cast<char*>(&frequency), sizeof(frequency));

		frequencyMap[character] = frequency;
	}
}

Node* Huffman::buildDecodingTree(unordered_map<unsigned char, string> encodingMap) {

	Node* rootNode = new Node(INTERNAL_NODE_CHARACTER);
	Node* previousNode;

	for (const auto& item : encodingMap) {
		previousNode = rootNode;
		Node* newNode = new Node(item.first);
		string characterCode = item.second;

		for (int i = 0; i < characterCode.size(); ++i) {
			if (characterCode[i] == '0') {
				if (i == characterCode.size() - 1)
					previousNode->setLeft(newNode);
				else {
					if (!previousNode->getLeft()) {
						previousNode->setLeft(new Node(INTERNAL_NODE_CHARACTER));
					}

					previousNode = previousNode->getLeft();
				}
			}
			else {
				if (i == characterCode.size() - 1)
					previousNode->setRight(newNode);
				else {
					if (!previousNode->getRight()) {
						previousNode->setRight(new Node(INTERNAL_NODE_CHARACTER));
					}

					previousNode = previousNode->getRight();
				}
			}
		}

	}
	return rootNode;
}

void Huffman::decompressToFile(string codeString, Node* rootNode, string decompressedFileName) {
	ofstream outputStream;
	outputStream.open(decompressedFileName, ios::binary);
	Node* traversingPointer = rootNode;

	for (int i = 0; codeString[i] != '\0'; ++i) {
		if (codeString[i] == '0')
			traversingPointer = traversingPointer->getLeft();
		else
			traversingPointer = traversingPointer->getRight();

		// Verificando se é uma folha:
		if (traversingPointer->getLeft() == nullptr && traversingPointer->getRight() == nullptr) {
			outputStream << traversingPointer->getCharacter();
			traversingPointer = rootNode;
		}
	}

	outputStream.close();
}