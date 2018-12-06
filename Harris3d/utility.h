#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include "vertex.h"
using namespace std;

void Pause();
void Pause(const char* message);
int sgn(double num);
void skipline(istream &in);
double distanceL2(Vertex* v1, Vertex* v2);

#endif // UTILITY_H
