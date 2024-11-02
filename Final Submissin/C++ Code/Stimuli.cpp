#include "Stimuli.h"

Stimuli::Stimuli() : inputs{} {}
Stimuli::~Stimuli() {}

//A Function that sets the vector of pairs as the input vector
void Stimuli::SetInputs(vector<pair<char, bool>> i) {
    inputs = i;
}

//Returns the last time input in the Stimuli Queue 
int Stimuli::CalMaxTime(queue<string> lines) {

    int commandcount = lines.size();

    //Iterating over the queuepopping and pushing all the strings except the last one
    for (int i = 0; i < commandcount-1; ++i) {
        string command = lines.front();
        lines.pop();
         lines.push(command);
 
    }

    string command = lines.front();
    //Using ss to transform the string
    stringstream ss(command);
    char hash;
    //The int value we need
    int time;
    char signal;
    char equalSign;
    int value;

    ss >> hash >> time >> signal >> equalSign >> value;

    return time;

}

//A function that processes the Stimuli Queue and reads out of it the change in the inputs at the time after the current time 
void Stimuli::processStimuliQueue(queue<string>& lines, int& t, vector<string>& output) {

    //Store t in a variable
    int currentTime = t;
    string outputString;

    string line = lines.front();
    //ss to identify the time, input and its value
    stringstream ss(line);
    char hash;
    int time;
    char signal;
    char equalSign;
    int value;

    ss >> hash >> time >> signal >> equalSign >> value;

    //If the time read is greater thatn the currrent time, update the current time
    if (time > currentTime) {
        currentTime = time;

        lines.pop();
    }
    //Update the input vector with the new bool values
    for (auto& input : inputs) {
        if (input.first == signal) {
            ostringstream oss;
            oss << currentTime << " " << input.first << "= " << input.second;
            outputString = oss.str();
            output.push_back(outputString);
        }
    }
    //Update the t
    if (lines.empty()) {
        t = currentTime;
        return;
    }

    //check for the rest of the queue and repeat the same process but this time don't accept, strings with time greater thatn the current time
    while (!lines.empty()) {
        string line = lines.front();
        if (line[0] != '#') break;



        stringstream ss(line);
        char hash;
        int time;
        char signal;
        char equalSign;
        int value;

        ss >> hash >> time >> signal >> equalSign >> value;

        if (time == currentTime) {



            for (auto& input : inputs) {
                if (input.first == signal)
                {
                    input.second = value;
                    ostringstream oss;
                    oss << currentTime << " " << input.first << "= " << input.second;
                    outputString = oss.str();
                    output.push_back(outputString);
                }
            }
            lines.pop();
        }

        else {
            t = currentTime;
            return;
        }
    }
}