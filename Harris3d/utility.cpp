#include <iostream>
#include <cmath>
#include "utility.h"

using namespace std;

void Pause(){
    cout<<"Press any key to continue...";
    getchar();
}

void Pause(const char* message){
    cout<<message<<endl;
    Pause();
}

int sgn(double num){
    if(num >= 0.0)
        return 1;
    else
        return -1;
}

void skipline(istream &in){
    char c;
    while(in>>noskipws>>c && c!='\n');
    in>>skipws;
}
double distanceL2(Vertex* v1, Vertex* v2){
    double diffx = v1->getx() - v2->getx();
    double diffy = v1->gety() - v2->gety();
    double diffz = v1->getz() - v2->getz();
    return sqrt(diffx*diffx + diffy*diffy + diffz*diffz);
}
