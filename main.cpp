#include <iostream>
#include <fstream>

#include "tree.h"

using namespace std;

int main(int argc, char **argv) {
 if (argc <= 1) {
        cout << argv[0] << ": too few arguments" << endl;
        cout << "Usage: " << argv[0] << " filename" << endl;
        exit(1);
    }

    // Open file
    ifstream infile;
    infile.open(argv[1]);

    // Create tree and insert data
    Tree ttTree;
    int x;

    while (infile.good()) {
        infile >> x;
        if (!infile.eof()) {
            cout << x << endl;
            ttTree.insert(x);
            ttTree.print();
        }
    }

    infile.close();

    return 0;
}