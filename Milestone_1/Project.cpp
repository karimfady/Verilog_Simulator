#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>  
#include <cctype>
#include <utility> 
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <algorithm>
#include <cctype>   
#include <sstream>
using namespace std;

bool Nand(bool a, bool b) {
    if (a == b == 0) {
        return 0;
    }
    else {
        return 1;
    }
}
bool Not(bool a) {
    return !a;
}
bool Or(bool a, bool b) {
    return a || b;
}
bool Xor(bool x1, bool x2) {
    if (x1 != x2)
        return 1;
    else { return 0; }
}
bool And(bool x1, bool x2) {
    if ((x1 && x2) == 1)
        return 1;
    else
        return 0;
}
bool Nor(bool x1, bool x2) {
    if ((x1 && x2) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

bool getBoolValue(char name, const vector<pair<char, bool>>& wires, const vector<pair<char, bool>>& inputs, pair<char, bool>& output) {
    for (const auto& wire : wires) {
        if (wire.first == name) return wire.second;
    }
    for (const auto& input : inputs) {
        if (input.first == name) return input.second;
    }
    if (output.first == name) return output.second;
    throw invalid_argument("Invalid wire or input name.");
}

void setBoolValue(char name, bool value, vector<pair<char, bool>>& wires, pair<char, bool>& output) {
    for (auto& wire : wires) {
        if (wire.first == name) {
            wire.second = value;
            return;
        }
    }
    if (output.first == name) output.second = value;
    throw invalid_argument("Wire not found.");
}

queue<string> readFileToQueue(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file: " << filePath << endl;
        return {};
    }

    queue<string> fileContents;
    string line;

    while (getline(file, line)) {
        if (!line.empty() && !all_of(line.begin(), line.end(), [](unsigned char c) { return isspace(c); })) {
            fileContents.push(line); 
        }
    }

    file.close();
    return fileContents;
}

void processModuleQueue(queue<string>& lines, vector<pair<char, bool>>& inputs, vector<pair<char, bool>>& wires, pair<char, bool>& output) {
    while (!lines.empty()) {


       
        if (lines.front().empty()) {

            continue; 
        }
        string line = lines.front();
        lines.pop();
        cout << "Processing line: " << line << endl;

        if (line.find("and") != string::npos ||
            line.find("nand") != string::npos ||
            line.find("or") != string::npos ||
            line.find("nor") != string::npos ||
            line.find("xor") != string::npos ||
            line.find("not") != string::npos) {
            cout << "Line contains a gate keyword, skipping." << endl;
            lines.push(line);
            return;
        }

        if (line.rfind("input", 0) == 0) {
            string keyword;
            char signal;
            stringstream ss(line);
            ss >> keyword >> signal;

            if (!ss.fail()) {
                inputs.push_back({ signal, false });
            }
            else {
                cerr << "Error parsing 'input' line: " << line << endl;
            }
        }

        else if (line.rfind("wire", 0) == 0) {
            string keyword;
            char signal;
            stringstream ss(line);
            ss >> keyword >> signal;

            if (!ss.fail()) {
                wires.push_back({ signal, false });
            }
            else {
                cerr << "Error parsing 'wire' line: " << line << endl;
            }
        }
 
        else if (line.rfind("output", 0) == 0) {
            string keyword;
            char signal;
            stringstream ss(line);
            ss >> keyword >> signal;

            if (!ss.fail()) {
                output = { signal, false };
            }
            else {
                cerr << "Error parsing 'output' line: " << line << endl;
            }
        }
        else {
            cerr << "Unrecognized line format: " << line << endl;
        }
    }

    cout << "Inputs: ";
    for (const auto& input : inputs) {
        cout << input.first << " ";
    }
    cout << "\nWires: ";
    for (const auto& wire : wires) {
        cout << wire.first << " ";
    }
    cout << "\nOutput: " << output.first << endl;
}

void processStimuliQueue(queue<string>& lines, vector<pair<char, bool>>& inputs, int& t) {
    int currentTime = t;

    while (!lines.empty()) {
        string line = lines.front();

        if (line[0] == '#') {
            stringstream ss(line);
            char hash;
            int time;
            char signal;
            char equalSign;
            int value;

            ss >> hash >> time >> signal >> equalSign >> value;

            if (time > currentTime) {
                currentTime = time;
            }
             else if (time != currentTime) {
                lines.push(line);
                return;
            }

            for (auto& input : inputs) {
                if (input.first == signal) {
                    input.second = (value == 1);
                }
            }
        }

        lines.pop();
    }

    t = currentTime;
}

void processGates(queue<string>& commands, vector<pair<char, bool>>& inputs,
    vector<pair<char, bool>>& wires, pair<char, bool>& output, int& t) {

    int commandCount = commands.size();

    for (int i = 0; i < commandCount; ++i) {
        string command = commands.front();
        commands.pop();

        if (command == "endmodule;") {
            commands.push(command);
            return;
        }

        size_t delayStart = command.find("#(");
        int delay = 0;
        if (delayStart != string::npos) {
            size_t delayEnd = command.find(")", delayStart);
            delay = stoi(command.substr(delayStart + 2, delayEnd - delayStart - 2));
            command.erase(delayStart, delayEnd - delayStart + 1);
        }


        istringstream ss(command);
        string gateType;
        char gateName;
        ss >> gateType >> gateName;


        string wireInfo;
        ss >> wireInfo;


        if (wireInfo.front() == '(' && wireInfo.back() == ')') {
            wireInfo = wireInfo.substr(1, wireInfo.length() - 2);

            char out = wireInfo.at(1);
            vector <bool> in;
            for (int i = 2; i < wireInfo.length(); i++) {
                if ((wireInfo.at(i) != ',') && (wireInfo.at(i) != ')')) {
                    in.push_back(wireInfo.at(i));
                }
            }

            if (gateType == "not") {
                bool result = Not(getBoolValue(in[0], wires, inputs, output));
                setBoolValue(out, result, wires, output);
                t += delay;
                cout << "Time: " << t << ", " << out << " = " << result << endl;
            }
            else {
                if (gateType == "and") {
                    bool result = And(getBoolValue(in[0], wires, inputs, output), getBoolValue(in[1], wires, inputs, output));
                    setBoolValue(out, result, wires, output);
                    t += delay;
                    cout << "Time: " << t << ", " << out << " = " << result << endl;
                }
                else if (gateType == "or") {
                    bool result = Or(getBoolValue(in[0], wires, inputs, output), getBoolValue(in[1], wires, inputs, output));
                    setBoolValue(out, result, wires, output);
                    t += delay;
                    cout << "Time: " << t << ", " << out << " = " << result << endl;
                }
                else if (gateType == "nand") {
                    bool result = Nand(getBoolValue(in[0], wires, inputs, output), getBoolValue(in[1], wires, inputs, output));
                    setBoolValue(out, result, wires, output);
                    t += delay;
                    cout << "Time: " << t << ", " << out << " = " << result << endl;
                }
                else if (gateType == "xor") {
                    bool result = Xor(getBoolValue(in[0], wires, inputs, output), getBoolValue(in[1], wires, inputs, output));
                    setBoolValue(out, result, wires, output);
                    t += delay;
                    cout << "Time: " << t << ", " << out << " = " << result << endl;
                }
                else if (gateType == "nor") {
                    bool result = Nor(getBoolValue(in[0], wires, inputs, output), getBoolValue(in[1], wires, inputs, output));
                    setBoolValue(out, result, wires, output);
                    t += delay;
                    cout << "Time: " << t << ", " << out << " = " << result << endl;
                }
            }
        }
        commands.push(command);
    }
}

void Result(string module_path, string stimuli_path, int t) {
    vector<pair<char, bool>> inputs, wires;
    pair<char, bool> output;
    queue<string> module = readFileToQueue(module_path);
    queue<string> stimuli = readFileToQueue(stimuli_path);
    processModuleQueue(module, inputs, wires, output);

    

    

   while (!stimuli.empty()) {
        processStimuliQueue(stimuli, inputs, t);
        processGates(module, inputs, wires, output, t);
    }
}

int main() {
    string x = "module.v";
    string y = "stimuli.stim";
    int t = -1;
    Result(x, y, t);
    return 0;
}