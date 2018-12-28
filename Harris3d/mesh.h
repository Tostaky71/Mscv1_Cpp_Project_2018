#ifndef MESH_H
#define MESH_H

#include "face.h"
#include "vertex.h"

class Mesh
{
    private:
    vector<Vertex> V;

    vector<vector <unsigned int>> F;

    unsigned int nVertices, nFaces, nEdges;

    public:

    Mesh();
    Mesh(const char* filename);
    ~Mesh();
    void loadfile(const char* filename);
    void displayVerts();
    void displayFaces();
};

#endif // MESH_H
