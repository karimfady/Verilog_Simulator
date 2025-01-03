#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cctype>
#include <utility>
#include <sstream>
using namespace std;

class Stimuli
{
private:
    //A vector storing the inputs identified from the Module File
    vector<pair<char, bool>> inputs;
public:
    Stimuli();
    ~Stimuli();
    int maxTime;
    int CalMaxTime(queue<string> lines);
    void SetInputs(vector<pair<char, bool>> i);
    vector<pair<char, bool>> GetInputs();
    void processStimuliQueue(queue<string>& lines, int& t, vector<string>& output);
};
