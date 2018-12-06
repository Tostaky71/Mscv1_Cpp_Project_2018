#include <iostream>
#include <fstream>
#include "utility.h"
#include "mesh.h"

using namespace std;

int main(int argc, char* argv[])
{
    cout << argc;
    Mesh M("/home/blue/null.off");
    M.displayVerts();
    //M.displayFaces();
    return 0;
}
