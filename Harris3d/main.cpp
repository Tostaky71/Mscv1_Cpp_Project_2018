#include <cstdlib>
#include <iostream>
#include <fstream>	// ifstream,
#include <string>
#include <map>
#include <cmath>

#include "Mesh.h"
//#include "Clock.h"
//#include "util.h"
#include "Properties.h"
#include "HarrisDetector.h"

using namespace std;

string getOutputPath(string filename){
  string outputPath = filename;
  size_t pos;
  string directory = "";

  if((pos = filename.find_last_of('/')) != string::npos){
    directory = filename.substr(0, pos + 1);
    outputPath = filename.substr(pos + 1);
  }

  pos = outputPath.find_last_of('.');
  outputPath = outputPath.substr(0, pos);

  outputPath = directory + outputPath + ".int";

  return outputPath;
}

void help(){
    cout << "Harris3D: Extracts the interest points from a 3D mesh." << endl;
    cout <<"  Command:" << endl;
    cout <<"            harris input_mesh [properties_file]" << endl;	// arguments to enter in the shell
    cout <<" where " << endl;
    cout <<" - input_mesh must be a valid OFF file" << endl;	// off file = geometric file
    cout <<" - properties_file is an optional text file with the parameters for Harris 3D." << endl;
    cout <<"   If this file is not provided, default parameters are used." << endl;
}

int main(int argc, char *argv[])
{
    if(argc < 2){		// if argument = 1, stop the program
        help();
        exit(EXIT_SUCCESS);
    }

    string offFilename = argv[1];		// rename argument nb 2 : input_mesh = offFilename (easier to use)
    string optFilename;
    if(argc == 3)
        optFilename = argv[2];			// rename argument nb 3 : properties_file = optFilename

    cout<<"File:"<<offFilename;			// display name of the input 3D file

    string outfilename = getOutputPath(offFilename);	// take the path of offFilename into outfilename
    ifstream inp;									// create a stream object "inp"
    inp.open(outfilename.c_str(), ifstream::in);	// open inp to put the string path as a char, and define inp as an input
    inp.close();

    if(inp.fail()){						// is there no existing result in inp file ? = is inp.value = 1 ?
        inp.clear(ios::failbit);		// let inp.value = 0

        int i = 0;	// ???
        Clock r;
        r.tick();	// how many time to reach this point
        Mesh mesh(argv[1]);
        r.tick();
        cout<<"->Loaded";
        cout<<"->Loading time:"<<r.getTime()<<"s."<<endl;

        Properties prop;
        if(argc == 3)
            prop.load(optFilename);

        HarrisDetector hd(&mesh, &prop);

        vector<Vertex> interestPoints;
        interestPoints.clear();
        Vertex* vertices = mesh.getVertices();

        Clock r1;
        r1.tick();
        cout<<"->Interest points"<<endl;
        hd.detectInterestPoints(interestPoints);
        r1.tick();
        cout<<"->Calculation time:"<<r1.getTime()<<"s."<<endl;

        cout<<"->Saving"<<endl;
        ofstream out(outfilename.c_str());

        out<<interestPoints.size()<<endl;
        for(register int i = 0; i < interestPoints.size(); i++) {
            out<<interestPoints[i].getIndex()<<endl;
        }
        out.close();
        interestPoints.clear();

        cout<<"File saved."<<endl;
    }else{
        cout << "Interest points already exist - Skipped" << endl;
    }

    return EXIT_SUCCESS;
}
