#ifndef INIPARSER_H
#define INIPARSER_H

#include <string>
#include <map>
#include <stdexcept>
#include <sstream>

using namespace std;

class IniParser
{
public:
    IniParser(const string& filename);
    bool load();

    template <typename T>
    T get_value(const string& key) const;

private:
    string filename_;
    map<string, map<string, string>> data_;

    string trim(const string& str);

    template <typename T>
    T convert(const string& str) const;
};

#endif // INIPARSER_H
