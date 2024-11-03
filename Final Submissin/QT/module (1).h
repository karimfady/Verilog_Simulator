#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cctype>
#include <utility>
#include <sstream>
using namespace std;

class Module
{
private:
    //Vectors in which the inputs and wires are stored in pairs of char followed by a bool
    vector<pair<char, bool>> wires, inputs;

    //Output isstored in single pair of char followed by a bool as it is a singke variable
    pair<char, bool> output;

    //The lines read from the Module File
    queue<string> lines;

    //A vector storing the time delay of each Gate
    vector <int> timedelay;

public:
    Module();

    ~Module();

    void SetLines(queue<string> x);

    void SetInputs(vector<pair<char, bool>> i);

    vector<pair<char, bool>> GetInputs();

    bool Nand(bool a, bool b);
    bool Not(bool a);
    bool Or(bool a, bool b);
    bool Xor(bool x1, bool x2);
    bool And(bool x1, bool x2);
    bool Nor(bool x1, bool x2);

    bool getBoolValue(char name);
    void setBoolValue(char name, bool value);
    void delaycal();
    void processModuleQueue();
    void processGates(int& t, vector<string>& output);
};
