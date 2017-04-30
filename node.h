#include <iostream>

using namespace std;

class Node {
	private:
        int smallest() {
            Node *node = this;
            while (!node->isLeaf()) 
				node = node->children[0];
            return node->values[0];
        }

        void insert1Siblings(Node *newChild, int newSmallest) {
            int newKey = newChild->values[0];
            newChild->parent = this;

            if (newKey < children[0]->values[0]) {
                // newNode is inserted as first child of root
                children[1] = children[0];
                children[0] = newChild;
                values[0] = children[1]->smallest();
            }
            else {
                // newNode is iserted as second child of root
                children[1] = newChild;
                values[0] = newSmallest;
            }
        }

        void insert2Siblings(Node *newChild, int newSmallest) {
            int newKey = newChild->values[0];
            newChild->parent = this;

            if (newKey < children[0]->values[0]) {
                children[2] = children[1];
                children[1] = children[0];
                children[0] = newChild;

                values[1] = values[0];
                values[0] = children[1]->smallest();
                updateParentSmallest(newSmallest);
            }
            else if (newKey < children[1]->values[0]) {
                children[2] = children[1];
                children[1] = newChild;

                values[1] = values[0];
                values[0] = newSmallest;
            }
            else {
                children[2] = newChild;

                values[1] = newSmallest;
            }
        }

        // Insert into a node with 3 children /home/apk/src/git/2-3tree/tree.h:65
        void insert3Siblings(Node *newChild, int newSmallest) {
            int newKey = newChild->values[0];

            int splitSmallest = -1;
            Node *splitNode = new Node();
            splitNode->parent = parent;

            if (newKey < children[0]->values[0] || newKey < children[1]->values[0]) {
                // newChild is inserted in current node
                splitSmallest = values[0];
                splitNode->children[0] = children[1];
                splitNode->children[1] = children[2];
                splitNode->values[0] = values[1];

                children[1]->parent = splitNode;
                children[2]->parent = splitNode;
                newChild->parent = this;

                if (newKey < children[0]->values[0]) {
                    // newChild is inserted as first child
                    children[1] = children[0];
                    children[0] = newChild;

                    values[0] = children[1]->smallest();
                    updateParentSmallest(newSmallest);
                }
                else {
                    // newChild is inserted as second child
                    children[1] = newChild;

                    values[0] = newSmallest;
                }
            }
            else {
                // newChild is inserted in split node child
                children[2]->parent = splitNode;
                newChild->parent = splitNode;
 
                if (newKey < children[2]->values[0]) {
                    // newChild is inserted as first child
                    splitSmallest = newSmallest;
                    splitNode->children[0] = newChild;
                    splitNode->children[1] = children[2];
                    splitNode->values[0] = values[1];
                }
                else {
                    // newChild is inserted as second child
                    splitSmallest = values[1];
                    splitNode->children[0] = children[2];
                    splitNode->children[1] = newChild;
                    splitNode->values[0] = newSmallest;
                }
            }

            children[2] = NULL;
            values[1] = -1;

            if (parent->parent == NULL) {
                // At root, so new root needs to be created
                Node *newNode = new Node();

                parent->children[0] = newNode;
                newNode->parent = parent;
                newNode->children[0] = this;
                parent = newNode;
            }

            parent->insert(splitNode, splitSmallest);
        }

        // Update the parent nods efor the smallest child value
        void updateParentSmallest(int data) {
            switch (sibNumber()) {
                case 0: if (parent->parent != NULL) parent->updateParentSmallest(data); break;
                case 1: parent->values[0] = data; break;
                case 2: parent->values[1] = data; break;
            }
        }

    public:
        int values[2];
        Node *parent, *children[3];

        // Constructor
        Node(int data = -1) {
            values[0] = data;
            values[1] = -1;
            parent = children[0] = children[1] = children[2] = NULL;
        }

        // Check if node is a leaf
        bool isLeaf() {
            return (children[0] == NULL);
        }

        // Get which sibling the node is getSmallest
        int sibNumber() {
            for (int i = 0; i < 3; ++i) {
                if (this == parent->children[i]) return i;
            }
            return -1;
        }

        // Insertion
        void insert(Node *newChild, int newSmallest) {
            if (children[1] == NULL) insert1Siblings(newChild, newSmallest);
            else if (children[2] == NULL) insert2Siblings(newChild, newSmallest);
            else insert3Siblings(newChild, newSmallest); 
        }
};
