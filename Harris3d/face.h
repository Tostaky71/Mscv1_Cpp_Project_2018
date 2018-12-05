#ifndef FACE_H
#define FACE_H

#include <vector>

typedef std::vector<unsigned int> vint;

class Face
{
    private :
    vint vertices;
    public:
    Face(){}
    ~Face(){}
    void addVertex(unsigned int vertex){vertices.push_back(vertex);}
    vint &getVertices(){return vertices;}

    void displayF();
};

#endif // FACE_H
