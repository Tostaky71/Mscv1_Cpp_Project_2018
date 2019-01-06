#ifndef PROPERTIES_H
#define PROPERTIES_H
/*
 * Properties.h is heavily based off of the source code of of Ivan Sipiran's implementation
 * for more info see https://users.dcc.uchile.cl/~isipiran/harris3D.html
 * */

#include <map>
#include <string>

class Property{

    private:
    std::map<std::string, std::string> prop;

    public:
    Property();
    Property(const char* args);
    ~Property();

    std::map<std::string, std::string> getProps();
    void setProps(std::string id, std::string val);
    std::string getProperty(std::string key);

};

#endif // PROPERTIES_H
