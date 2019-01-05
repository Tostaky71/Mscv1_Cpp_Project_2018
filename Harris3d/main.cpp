#include <iostream>
#include <fstream>
#include "utility.h"
#include "mesh.h"
#include "harrisdetector.h"

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[])
{
    //cout << argc << endl;
    Mesh M("/home/blue/0001.noise.4.off");
    HarrisDetector H(M);
    cout << "Calculating interest points..." << endl;
    vector<Vertex> V = H.getInterestPoints();
    cout << "displaying" <<  V.size() << "points coordinates" <<endl;
    vector<Vertex>::iterator it;
    for (it = V.begin(); it != V.end(); it++)
        (*it).display();
    return 0;
}
