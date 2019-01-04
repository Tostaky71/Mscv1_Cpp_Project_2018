#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;
typedef unsigned int uint;

class Vertex;
void operator <<(std::ostream &out, Vertex V);
class Vertex
{
    private:
    uint index;
    bool mark, isInterest;
    vector <uint> faces;
    set<uint> neighbours;// 252

    int depth;
    double response;
    uint numNeighbors;
    double v[3];
    public:

    Vertex(){v[0] = v[1] = v[2] = 0;}
    Vertex(double x, double y, double z){v[0] = x; v[1] = y; v[2] = z;mark = false; depth = 0;isInterest = 0;}

    double x() const { return v[ 0 ]; }
    double y() const { return v[ 1 ]; }
    double z() const { return v[ 2 ]; }

    double& x() { return v[ 0 ]; }
    double& y() { return v[ 1 ]; }
    double& z() { return v[ 2 ]; }

    double getx(){return v[0];}
    double gety(){return v[1];}
    double getz(){return v[2];}

    void setx(double x){v[0] = x;}
    void sety (double y){v[1] = y;}
    void setz(double z){{v[2] = z;}}

    bool operator==(const Vertex& p) const
    {
        return (x() == p.x()) && (y() == p.y()) && (z() == p.z())  ;
    }

    bool  operator!=(const Vertex& p) const { return ! (*this == p); }

    friend ostream& operator<<(ostream& out, Vertex& point);

    void setVertex(double x1, double y1, double z1){v[0] = x1; v[1] = y1; v[2] = z1;}
    void setIndex(uint ind){index = ind;}
    uint getIndex(){return index;}
    bool isMarked(){return mark;}
    void setMark(bool mark1){mark = mark1;}
    int getDepth(){ return depth;}
    void setDepth(int dep){ depth = dep;}
    double getResponse(){return response;}
    void setResponse(double resp){response = resp;}
    bool getInterest(){return isInterest;}

    set<unsigned int> getNeighborhood(int rad, vector<Vertex>&Ver);
    int getRadius(vector<Vertex>& vertices, double radius, set<uint>& Voutput);

    void addVertex(uint V){neighbours.insert(V);}
    void addFace(uint face){faces.push_back(face); }
    vector<uint> getFaces(){return this->faces;}
    set<uint> getneighbours(){return this->neighbours;}

    void display();
    void processMax(vector<Vertex>& Ver);

};

#endif // VERTEX_H
