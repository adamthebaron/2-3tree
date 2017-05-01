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

        void updateSmallest(int data) {
            switch (childNumber()) {
                case 0: 
					if (parent->parent != NULL) 
						parent->updateSmallest(data); 
					break;
                case 1: 
					parent->values[0] = data; 
					break;
                case 2: 
					parent->values[1] = data; 
					break;
            }
        }

    public:
        int values[2];
        Node *parent, *children[3];

        Node(int data = -1) {
            values[0] = data;
            values[1] = -1;
			parent = NULL;
			for (int i = 0; i < 3; i++)
				children[i] = NULL;
        }

        bool isLeaf() {
            return (children[0] == NULL);
        }

        int childNumber() {
            for (int i = 0; i < 3; ++i)
                if (this == parent->children[i]) 
					return i;
            return -1;
        }

		void insert(Node* newChild, int newSmallest) {
			if (children[1] == NULL) {
				int newval = newChild->values[0];
           		newChild->parent = this;
            	if (newval < children[0]->values[0]) {
                	children[1] = children[0];
                	children[0] = newChild;
                	values[0] = children[1]->smallest();
            	} else {
                	children[1] = newChild;
                	values[0] = newSmallest;
            	}
			} else if (children[2] == NULL) {
				int newval = newChild->values[0];
            	newChild->parent = this;
            	if (newval < children[0]->values[0]) {
                	children[2] = children[1];
                	children[1] = children[0];
                	children[0] = newChild;
                	values[1] = values[0];
                	values[0] = children[1]->smallest();
                	updateSmallest(newSmallest);
            	} else if (newval < children[1]->values[0]) {
                	children[2] = children[1];
                	children[1] = newChild;
                	values[1] = values[0];
                	values[0] = newSmallest;
            	} else {
                	children[2] = newChild;
                	values[1] = newSmallest;
            	}
			} else {
				int newval = newChild->values[0];
            	int splitSmallest = -1;
            	Node *splitNode = new Node();
            	splitNode->parent = parent;
            	if (newval < children[0]->values[0] || newval < children[1]->values[0]) {
                	splitSmallest = values[0];
               		splitNode->children[0] = children[1];
                	splitNode->children[1] = children[2];
                	splitNode->values[0] = values[1];
                	children[1]->parent = splitNode;
                	children[2]->parent = splitNode;
                	newChild->parent = this;
                	if (newval < children[0]->values[0]) {
                    	children[1] = children[0];
                    	children[0] = newChild;
                    	values[0] = children[1]->smallest();
                    	updateSmallest(newSmallest);
                	} else {
                    	children[1] = newChild;
                    	values[0] = newSmallest;
                	}
            	} else {
                	children[2]->parent = splitNode;
                	newChild->parent = splitNode;
                	if (newval < children[2]->values[0]) {
                    	splitSmallest = newSmallest;
                    	splitNode->children[0] = newChild;
                    	splitNode->children[1] = children[2];
                    	splitNode->values[0] = values[1];
                	} else {
                    	splitSmallest = values[1];
                    	splitNode->children[0] = children[2];
                    	splitNode->children[1] = newChild;
                    	splitNode->values[0] = newSmallest;
                	}
            	}
            	children[2] = NULL;
            	values[1] = -1;
            	if (parent->parent == NULL) {
                	Node *newNode = new Node();
                	parent->children[0] = newNode;
                	newNode->parent = parent;
                	newNode->children[0] = this;
                	parent = newNode;
            	}
            	parent->insert(splitNode, splitSmallest);
			}
		}
};
