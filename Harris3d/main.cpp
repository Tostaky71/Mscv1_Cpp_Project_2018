#include <QApplication>
#include <iostream>
#include <fstream>
#include "mesh.h"
#include "harrisdetector.h"
#include "myglwidget.h"

using namespace std;
using namespace Eigen;


int main(int argc, char *argv[])
{
    string filename;
    string options;
    if(argc > 1)
        filename.assign(argv[1]);
    else
        filename.assign("./mesh.off");

    if (argc > 2)
        options.assign(argv[2]);
    else
        options.assign("./opt.txt");

    Property prop(options.c_str());
    Mesh M(filename.c_str());
    HarrisDetector H;
    if (argc>2)
    {
        H = HarrisDetector(M, prop);
    }
    else{
        H = HarrisDetector(M);
    }

    QApplication a(argc, argv);
    MyGLWidget wi(H);
    wi.show();
    return a.exec();
}
