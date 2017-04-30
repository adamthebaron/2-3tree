#include <iostream>

#include "node.h"

using namespace std;

class Tree {
	Node* root;

	public:
	Tree(Node* node) {
		root = node;
	}

	Node* search(int valToFind) {
		return NULL;
	}

	bool insert(int valToAdd) {
		return false;
	}

	bool delete(int valToKill) {
		return false;
	}

	void absorb(Node* newChild, Node* tree) {

	}

	void print() {

	}
};