#ifndef HARRISDETECTOR_H
#define HARRISDETECTOR_H

#include "mesh.h"
#include "properties.h"
#include <map>
#include <Eigen/Dense>

class HarrisDetector
{
    private:
    Mesh obj;

    int typeNei;
    int ringNeighbourhood;
    double fractionDiagonal;
    double k;

    int typeSelection;
    double paramSelection;
    public:

    enum TYPENEI{RING, ADAPTIVE};
    enum TYPESELEC{FRACTION, CLUSTERING};

    HarrisDetector();
    HarrisDetector(Mesh& mesh);
    HarrisDetector(Mesh& mesh, Property& prop);
    ~HarrisDetector();

    vector<Vertex> getInterestPoints();
    Mesh getMesh();
};

#endif // HARRISDETECTOR_H
