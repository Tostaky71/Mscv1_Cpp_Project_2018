#include "mesh.h"
#include "utility.h"
#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;
Mesh::Mesh()
{

}

Mesh::Mesh(const char* filename)
{
    loadfile(filename);
}

Mesh::~Mesh()
{
}

void Mesh::loadfile(const char* filename)
{
    ifstream FILE(filename);
    if (FILE.is_open())
    {
        string format;
        getline(FILE, format);
        assert(format.find("OFF") != string::npos);

        FILE >> nVertices >> nFaces >> nEdges;

        for(unsigned int i = 0; i < nVertices; i++)
        {
            double x,y,z;
            FILE >> x >> y >> z;
            Vertex ver(x,y,z);
            V.push_back(ver);
        }

        for(unsigned int i = 0; i < nFaces; i++)
        {
            vector <unsigned int> v;
            uint p0, p1, p2;
            FILE >> p0 >> p1 >> p2;
            v.push_back(p0);
            v.push_back(p1);
            v.push_back(p2);
            F.push_back(v);
        }
        FILE.close();
    }
    else
        cout << "can't open " << filename << endl;
}

void Mesh::displayVerts()
{
    vector<Vertex>::iterator it;
    for (it = V.begin(); it != V.end(); it++)
    {
        (*it).display();
    }
}
void Mesh::displayFaces()
{
    vector <vector <unsigned int>>::iterator it;
    for (it = F.begin(); it != F.end(); it++)
    {
        cout << "F" << endl;
        for (unsigned int i = 0; i < 3; i++)
        cout << (*it).at(i) << ", ";
        cout << endl;
    }
}

