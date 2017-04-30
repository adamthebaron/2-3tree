#include <iostream>

#include "node.h"

using namespace std;

class Tree {
	Node* root;

	public:
	Tree(Node* node) {
		root = node;
	}

	Node* search(Node* node, int valToFind) {
		if (node == NULL)
			return NULL;
		while (!node->isLeaf()) {
			if (node->getValue(0) == valToFind || node->getValue(1) == valToFind)
				return NULL;
			if (node->getValue(0) == -1 || valToFind < node->getValue(0))
				node = node->getChild(0);
			else if (node->getValue(1) == -1 || valToFind < node->getValue(1))
				node = node->getChild(1);
			else
				node = node->getChild(2);
		}
		if (node->getValue(0) == valToFind)
			return NULL;
		return node->getParent();
	}

	bool insert(int valToAdd) {
		Node* node = new Node(valToAdd);
		Node* searchNode = root->getChild(0);
		if (searchNode->getChild(0) == NULL) {
			node->setParent(searchNode);
			searchNode->setChild(node, 0);
		} else {
			searchNode = search(searchNode, valToAdd);
			if (searchNode == NULL)
				return false;
			searchNode->absorb(new Node(valToAdd), valToAdd);
		}
		return true;
	}

	bool Delete(int valToKill) {
		return false;
	}

	void print() {

	}
};