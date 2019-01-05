#include "vertex.h"
#include <iostream>
#include <cmath>
#include <map>
#include "utility.h"
#include <Eigen/Dense>
using namespace Eigen;

set<unsigned int> Vertex::getNeighborhood(int rad, vector<Vertex>&Ver)
{
    set<unsigned int> N;
    set<unsigned int>::iterator it;
    for (it = neighbours.begin(); it != neighbours.end(); it++)
    {
        N.insert(*it);
        if (rad > 1){
            set<unsigned int> N2;
            N2 = Ver[*it].getNeighborhood(rad-1, Ver);
            N.insert(N2.begin(), N2.end());
        }
    }
    return N;
}

set<uint> Vertex::getRadius(vector<Vertex>& vertices, double radius)
{
    set<uint> Voutput;
    set <uint> N = this->getneighbours();
    map<uint, double> distanceToThis;
    set <uint>::iterator it;
    Vector3d V(this->x(), this->y(), this->z());
    for (it = N.begin(); it != N.end(); it++)
    {
        Vector3d V1(vertices[*it].x(),vertices[*it].y(), vertices[*it].z());
        Vector3d diff = V - V1;
        double distance = diff.norm();
        distanceToThis[*it] = distance;
        if (distance <= radius)
        {
            set<uint> temp;
            Voutput.insert(*it);
            temp = vertices[*it].getRadius(vertices, radius-distance);
            Voutput.insert(temp.begin(), temp.end());
        }
    }
    return Voutput;
}

void Vertex::display()
{
    std::cout << this->x() << ", " << this->y() << ", " << this->z() << endl;
}


void operator <<(std::ostream &out, Vertex V)
{
    V.display();
}



void Vertex::processMax(vector<Vertex>& Ver)
{
    set<unsigned int>::iterator it;
    for (it = neighbours.begin(); it != neighbours.end(); it++)
    {
        Vertex* v1 = &Ver[*it];
        if (this != v1)
        {
            if (response < v1->getResponse())
                return;
        }
    }
    isInterest = true;

}
