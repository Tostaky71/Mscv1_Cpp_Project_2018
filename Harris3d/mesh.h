#ifndef MESH_H
#define MESH_H
/*
 * Mesh.h is heavily based off of the source code of of Ivan Sipiran's implementation
 * for more info see https://users.dcc.uchile.cl/~isipiran/harris3D.html
 * */

#include <vector>
#include "vertex.h"

class Mesh
{
    private:
    vector<Vertex> V;

    vector<vector <unsigned int>> F;

    unsigned int nVertices, nFaces, nEdges;
    double xmin, xmax, ymin, ymax, zmin, zmax;

    double diag;

    public:

    Mesh();
    Mesh(const char* filename);
    ~Mesh();
    void loadfile(const char* filename);
    void displayVerts();
    void displayFaces();

    vector<Vertex> getVertices();
    vector<vector <unsigned int>> getFaces();

    double getDiag(){return diag;}
};

#endif // MESH_H
