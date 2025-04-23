#include "IniParser.h"
#include <fstream>
#include <iostream>

IniParser::IniParser(const string& filename) : filename_(filename) {}

bool IniParser::load()
{
    ifstream file(filename_);
    if (!file.is_open())
    {
        throw runtime_error("Error opening file: " + filename_);
    }

    string line;
    string currentSection;

    while (getline(file, line))
    {
        line = trim(line);

        if (line.empty() || line[0] == ';')
        {
            continue;
        }

        if (line[0] == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.length() - 2);
            continue;
        }

        size_t pos = line.find('=');
        if (pos != string::npos)
        {
            string key = trim(line.substr(0, pos));
            string value = trim(line.substr(pos + 1));
            data_[currentSection][key] = value;
        }
        else
        {
            throw runtime_error("Invalid format in file: " + filename_);
        }
    }

    return true;
}

template <typename T>
T IniParser::get_value(const string& key) const
{
    size_t dotPos = key.find('.');
    if (dotPos == string::npos)
    {
        throw invalid_argument("Invalid key format: " + key);
    }

    string section = key.substr(0, dotPos);
    string name = key.substr(dotPos + 1);

    auto sectionIt = data_.find(section);
    if (sectionIt == data_.end())
    {
        throw out_of_range("Section not found: " + section);
    }

    auto keyIt = sectionIt->second.find(name);
    if (keyIt == sectionIt->second.end())
    {
        throw out_of_range("Key not found: " + key);
    }

    try
    {
        return convert<T>(keyIt->second);
    }
    catch (...)
    {
        throw runtime_error("Failed to convert value for key: " + key);
    }
}

string IniParser::trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return "";
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

template <typename T>
T IniParser::convert(const string& str) const
{
    istringstream iss(str);
    T value;
    iss >> value;
    if (iss.fail() || !iss.eof())
    {
        throw runtime_error("Conversion failed");
    }
    return value;
}

template int IniParser::get_value<int>(const string&) const;
template double IniParser::get_value<double>(const string&) const;
template string IniParser::get_value<string>(const string&) const;
