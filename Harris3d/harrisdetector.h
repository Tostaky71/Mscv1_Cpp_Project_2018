#ifndef HARRISDETECTOR_H
#define HARRISDETECTOR_H

#include "mesh.h"
#include <map>
#include <Eigen/Dense>

class HarrisDetector
{
    private:
    Mesh obj;

    int typeNei;
    int ringNeighbourhood;

    double k;

    int typeSelection;
    double paramSelection;


    public:

    enum TYPENEI{RING, SPACIAL, ADAPTIVE};
    enum TYPESELEC{FRACTION, CLUSTERING};

    HarrisDetector();
    HarrisDetector(Mesh& mesh);
    ~HarrisDetector();

    vector<Vertex> getInterestPoints();

};

#endif // HARRISDETECTOR_H
