#include <properties.h>
#include <fstream>
#include <iostream>

using namespace std;
Property::Property(){

}

Property::~Property(){

}
Property::Property(const char * args)
{
    fstream FILE(args);
    if(FILE.is_open())
    {
        string param;
        while(!FILE.eof())
        {
            string key, val;
            FILE >> key >> val;
            prop[key] = val;
        }

        FILE.close();
    }
    else
    {
        cout << "no file could be opened" << endl;
    }
}

map<string, string> Property::getProps()
{
    return this->prop;
}

string Property::getProperty(string key)
{
    string val = prop[key];
    if (prop[key].empty())
        prop.erase(key);
    return val;
}
