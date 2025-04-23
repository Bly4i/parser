#include "IniParser.h"
#include <iostream>

using namespace std;

int main()
{
    try
    {
        IniParser parser("example.ini");
        parser.load();

        int age = parser.get_value<int>("Section1.age");
        cout << "Age: " << age << endl;

        string name = parser.get_value<string>("Section1.name");
        cout << "Name: " << name << endl;

        double setting = parser.get_value<double>("Section2.setting");
        cout << "Setting: " << setting << endl;
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
