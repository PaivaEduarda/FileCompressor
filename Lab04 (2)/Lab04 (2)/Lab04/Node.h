#pragma once
#include <iostream>
#include <string>

using std::string;
using std::istream;
using std::ostream;

class Node {
    unsigned char character;
    int frequency;

public:
    int getFrequency() const;

private:
    Node* left, * right;

public:
    Node(unsigned char character, int frequency);
    Node(unsigned char character);

    Node* getLeft() const;
    Node* getRight() const;

    void setLeft(Node* left);
    void setRight(Node* right);
    void printTreeStructure(Node* root, int level = 0, char direction = 'C');

    unsigned char getCharacter() const;
};
