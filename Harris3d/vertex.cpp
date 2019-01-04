#include "vertex.h"
#include <iostream>
#include <cmath>
#include <map>
#include "utility.h"

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

void Vertex::display()
{
    std::cout << this->x() << ", " << this->y() << ", " << this->z() << endl;
}


void operator <<(std::ostream &out, Vertex V)
{
    V.display();
}



void Vertex::processMax(vector<Vertex> Ver, int numRings)
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
