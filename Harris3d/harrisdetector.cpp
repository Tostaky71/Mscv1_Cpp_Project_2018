#include "harrisdetector.h"

using namespace Eigen;

HarrisDetector::HarrisDetector()
{
ringNeighbourhood  = 1;
}

HarrisDetector::HarrisDetector(Mesh& mesh)
{
    this->obj = mesh;
    ringNeighbourhood = 1;
}

HarrisDetector::~HarrisDetector()
{

}

map<uint, uint> HarrisDetector::getInterestPoints()
{
   map<uint, uint> interestPoints;

    double max =0.0; int rad = 0, cont = 0;
    double diag = obj.getDiag();

    vector<Vertex> Vertices = obj.getVertices();
    vector <vector <uint>> faces = obj.getFaces();

    vector<Vertex>::iterator it;
    for (it = Vertices.begin(); it != Vertices.end(); it++)
    {
        set<uint> neighbours;
        neighbours = (*it).getNeighborhood(ringNeighbourhood,0.0,Vertices);

        set<uint>::iterator it2;
        for (it2 = neighbours.begin(); it2 != neighbours.end();it2++)
        {
            interestPoints[(*it2)] += 1;
        }
    }


    return interestPoints;
}
