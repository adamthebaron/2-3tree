#include <iostream>

#include "node.h"

using namespace std;

class Tree {
    private:
        Node *root;
        Node* findSpot(Node *node, int data) {
            if (node == NULL) return NULL;

            while (!node->isLeaf()) {
                if (node->values[0] == data || node->values[1] == data)
                    return NULL;
                if (node->values[0] == -1 || data < node->values[0])
                    node = node->children[0];
                else if (node->values[1] == -1 || data < node->values[1])
                    node = node->children[1];
                else
                    node = node->children[2];
            }

            if (node->values[0] == data) return NULL;
            return node->parent;
        }

        void print(Node *node, int tabs = 0) {
            for (int i = 0; i < tabs; ++i) {
                cout << "\t";
            }

            if (node == NULL) {
                cout << "`--> NULL" << endl;
                return;
            }

            cout << "`--> " << node->sibNumber()
                 << ": ( " << node->values[0] << ", " << node->values[1] << ")" << endl;

            if (!node->isLeaf()) {
                ++tabs;
                print(node->children[0], tabs);
                print(node->children[1], tabs);
                print(node->children[2], tabs);
            }
        }

    public:
        Tree() {
            root = new Node();
            root->children[0] = new Node();
            root->children[0]->parent = root;
        }

        bool insert(int data) {
            Node *newNode = new Node(data);
            Node *spot = root->children[0];

            if (spot->children[0] == NULL) {
                newNode->parent = spot;
                spot->children[0] = newNode;
            }
            else {
                spot = findSpot(spot, data);
                if (spot == NULL) return false;
            
                spot->insert(new Node(data), data);
            }

            return true;
        }

        void print() {
            print(root->children[0]);
            cout << endl;
        }
};