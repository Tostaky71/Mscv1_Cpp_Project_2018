#ifndef FACE_H
#define FACE_H


#include <vector>

using namespace std;

          class Face{
                private:
                        vector<int> vertices;
                public:
                       Face(){}
                       void addVertex(int vertex){ vertices.push_back(vertex);}     // add a value in vertex
                       vector<int>& getVertices(){ return vertices;}                // get vertices in output
                };


#endif // FACE_H
