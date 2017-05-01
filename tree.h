#include <iostream>

#include "node.h"

using namespace std;

class Tree {
    private:
        Node *root;
        Node* search(Node *node, int valToFind) {
            if (node == NULL) 
				return NULL;
            while (!node->isLeaf()) {
                if (node->values[0] == valToFind || node->values[1] == valToFind)
                    return NULL;
                if (node->values[0] == -1 || valToFind < node->values[0])
                    node = node->children[0];
                else if (node->values[1] == -1 || valToFind < node->values[1])
                    node = node->children[1];
                else
                    node = node->children[2];
            }

            if (node->values[0] == valToFind) 
				return NULL;
            return node->parent;
        }

    public:
        Tree() {
            root = new Node();
            root->children[0] = new Node();
            root->children[0]->parent = root;
        }

        bool insert(int valToAdd) {
            Node *newNode = new Node(valToAdd);
            Node *searchNode = root->children[0];

            if (searchNode->children[0] == NULL) {
                newNode->parent = searchNode;
                searchNode->children[0] = newNode;
            }
            else {
                searchNode = search(searchNode, valToAdd);
                if (searchNode == NULL) 
					return false;
            
                searchNode->insert(new Node(valToAdd), valToAdd);
            }

            return true;
        }
};