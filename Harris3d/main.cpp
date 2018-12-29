#include <iostream>
#include <fstream>
#include "utility.h"
#include "mesh.h"
#include <Eigen/Eigen>
#include "harrisdetector.h"

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[])
{
    //cout << argc << endl;
    Mesh M("/home/blue/null.off");
    HarrisDetector H(M);

    map<uint, uint> points = H.getInterestPoints();
    map<uint, uint>::iterator it;
    for (it = points.begin(); it!= points.end(); it++)
    {
        if((*it).second > 8)
            cout << (*it).first << ", " << (*it).second << endl;
    }

    return 0;
}
