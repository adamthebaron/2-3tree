#include <iostream>
#include <fstream>

#include "tree.h"

using namespace std;

int main(int argc, char **argv) {
    ifstream infile;
    infile.open(argv[1]);

    Tree tree;
    int x;

    while (infile.good()) {
        infile >> x;
        if (!infile.eof())
            tree.insert(x);
    }
    infile.close();

    return 0;
}