#ifndef PROPERTIES_H
#define PROPERTIES_H
#endif // PROPERTIES_H


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
