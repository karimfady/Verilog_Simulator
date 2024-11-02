#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <algorithm>  
#include <cctype>
#include <utility> 
using namespace std;

class File
{
private:
    string filePath;


public:
    File();
    ~File();
    void SetFilePath(string x);
    queue<string> readFileToQueue();
    void writeVectorToFile(const vector<string>& output);
};

