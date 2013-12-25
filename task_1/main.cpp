#include <iostream>
#include <fstream>
#include "Kruskal.h"
#include "Prim.h"
using namespace std;

int main()
{
    ifstream istr("/home/darya/OOP/task_1/input.txt");
    Graph<int, int> g;
    istr>>g;
    Kruskal kr(&g);
    Prim prim(&g);
    cout << "Hello World!" << endl;
    return 0;
}

