#ifndef HARRISDETECTOR_H
#define HARRISDETECTOR_H

#include "mesh.h"
#include <map>
#include <Eigen/Dense>

class HarrisDetector
{
    private:
    Mesh obj;

    int ringNeighbourhood;

    public:
    HarrisDetector();
    HarrisDetector(Mesh& mesh);
    ~HarrisDetector();

    map<uint, uint> getInterestPoints();

};

#endif // HARRISDETECTOR_H
