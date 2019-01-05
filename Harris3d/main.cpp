#include <iostream>
#include <fstream>
#include "utility.h"
#include "mesh.h"
#include "harrisdetector.h"

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[])
{
    string filename;
    string options = "/home/blue/opt.txt";
    if(argc > 1)
        filename.assign(argv[1]);
    else
        filename.assign("/home/blue/sampling.off");

    if (argc > 2)
        options.assign(argv[2]);

    Property prop(options.c_str());
    Mesh M(filename.c_str());
    if (argc>2)
    {
        HarrisDetector H(M, prop);
        cout << "Calculating interest points..." << endl;
        vector<Vertex> V = H.getInterestPoints();
        cout << "displaying " <<  V.size() << " points' coordinates" <<endl;
        vector<Vertex>::iterator it;
        for (it = V.begin(); it != V.end(); it++)
            (*it).display();
    }
    else{
        HarrisDetector H(M);
    cout << "Calculating interest points..." << endl;
    vector<Vertex> V = H.getInterestPoints();
    cout << "displaying " <<  V.size() << " points' coordinates" <<endl;
    vector<Vertex>::iterator it;
    for (it = V.begin(); it != V.end(); it++)
        (*it).display();
    }
    return 0;
}
