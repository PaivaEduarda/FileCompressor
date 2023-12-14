#include "Node.h"

Node::Node(unsigned char character, int frequency) : character(character), frequency(frequency), left(nullptr), right(nullptr) {
    // Nenhuma inicialização adicional necessária aqui
}

int Node::getFrequency() const {
    return frequency;
}

void Node::setLeft(Node* left) {
    this->left = left;
}

void Node::setRight(Node* right) {
    this->right = right;
}

Node* Node::getLeft() const {
    return left;
}

unsigned char Node::getCharacter() const {
    return character;
}

Node* Node::getRight() const {
    return right;
}

Node::Node(unsigned char character) : character(character), left(nullptr), right(nullptr) {
    // Nenhuma inicialização adicional necessária aqui
}

// Print tree structure
void Node::printTreeStructure(Node* root, int level, char direction) {
    if (root != nullptr) {
        printTreeStructure(root->getRight(), level + 1, 'R');
        for (int i = 0; i < level; i++) {
            std::cout << "    ";
        }
        std::cout << root->getCharacter() << " (" << root->getFrequency() << ") [" << direction << "]" << std::endl;
        printTreeStructure(root->getLeft(), level + 1, 'L');
    }
}