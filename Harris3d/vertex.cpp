#include "vertex.h"
#include <iostream>
#include <cmath>
#include <map>
#include "utility.h"

set<unsigned int> Vertex::getNeighborhood(int rad, double crit, vector<Vertex>&Ver)
{
    set<unsigned int> N;
    set<unsigned int>::iterator it;
    for (it = neighbours.begin(); it != neighbours.end(); it++)
    {
        N.insert(*it);
        if (rad > 1){
            set<unsigned int> N2;
            N2 = Ver[*it].getNeighborhood(rad-1, crit, Ver);
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
