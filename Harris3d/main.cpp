#include <iostream>
#include <fstream>
#include "utility.h"
#include "mesh.h"
#include "harrisdetector.h"
#include <fstream>
using namespace std;
using namespace Eigen;

int main(int argc, char* argv[])
{
    //cout << argc << endl;
    Mesh M("C:/sampling.off");
    HarrisDetector H(M);
    cout << "Calculating interest points..." << endl;
    vector<Vertex> V = H.getInterestPoints();
    cout << "displaying" <<  V.size() << "points coordinates" <<endl;
    vector<Vertex>::iterator it;
    for (it = V.begin(); it != V.end(); it++)
       (*it).display();
    ofstream output;\
    output.open("sampling.txt");
    if(output)
    {
        vector<Vertex>::iterator it;
            for (it = V.begin(); it != V.end(); it++)
            {
                //int x = (*it).operator [](0);
                //int y = *it.operator [](1);
                //int z = *it.operator [](2);
                output << (*it).display() << endl;          // trying to create a txt file with coordinates of interest points (x,y,z)
            }
            else
            {
                cout<<" ERROR " << endl;
            }
            output.close();
    }
    return 0;


}
