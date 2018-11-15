#ifndef FACE_H
#define FACE_H


#include <vector>

using namespace std;

          class Face{
                private:
                        vector<int> vertices;
                public:
                       Face(){}
                       void addVertex(int vertex){ vertices.push_back(vertex);}
                       vector<int>& getVertices(){ return vertices;}
                };


#endif // FACE_H
