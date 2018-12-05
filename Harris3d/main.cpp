#include <iostream>
#include <fstream>
#include "utility.h"
#include "mesh.h"

using namespace std;

int main()
{
    cout <<"build" << endl;
    Mesh M("/home/blue/testmesh.off");
    M.displayVerts();
    M.displayFaces();
    return 0;
}
