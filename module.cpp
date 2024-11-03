#include "Module.h"

Module::Module() : wires{}, inputs{}, output{ ' ', false }, timedelay{} {}
Module::~Module() {}

//Setting the queue of strings read from the Module File as the lines queue
void Module::SetLines(queue<string> x) {
    lines = x;
}

void Module::SetInputs(vector<pair<char, bool>> i) {
    inputs = i;
}

//A Get Function in order to use the inputs identified from processing the Module in the Stimuli class
vector<pair<char, bool>> Module::GetInputs() {
    return inputs;
}

bool Module::Nand(bool x1, bool x2) {
    return !(x1 && x2);
}

bool Module::Not(bool x1) {
    return !x1;
}

bool Module::Or(bool x1, bool x2) {
    return x1 || x2;
}

bool Module::Xor(bool x1, bool x2) {
    return x1 != x2;
}

bool Module::And(bool x1, bool x2) {
    return x1 && x2;
}

bool Module::Nor(bool x1, bool x2) {
    return !(x1 || x2);
}

//A Function that searches for the bool of a variable using its name
bool Module::getBoolValue(char name) {

    //First it checks the Wires
    for (const auto& wire : wires) {
        if (wire.first == name) return wire.second;
    }
    //Then it checks the Inputs
    for (const auto& input : inputs) {
        if (input.first == name) return input.second;
    }
    //If not found in the wires or inputs, check the output
    if (output.first == name) return output.second;
    //If not found, generate an error message
    throw invalid_argument("Invalid wire or input name.");
}

//A Function that Sets the bool of a variable using its name
void Module::setBoolValue(char name, bool value) {

    //First it checks the Wires
    for (auto& wire : wires) {
        if (wire.first == name) {
            wire.second = value;
            return;
        }
    }

    //If not found in the wires, check the output
    if (output.first == name) { output.second = value; }

    //If not found, generate an error message
    else {
        cout << "Wire not found.";
    }
}

//A Function that Identifies the inputs,wires and output and stores them
void Module::processModuleQueue() {

    //Iterate over the whole queue of strings
    while (!lines.empty()) {

        if (lines.front().empty()) {

            continue;
        }
        //Transfer the front to a variable and pop it
        string line = lines.front();
        lines.pop();

        //If you have reached "endmodule;" then return as that is the end of the data that is useful for us
        if (line.find("endmodule;") != string::npos) {
            return;

        }

        //If you have found  a gate declaration then the inputs,wies and outputs declarations were all in the previous lines and we don't need the rest in this function
        if (line.find("and") != string::npos ||
            line.find("nand") != string::npos ||
            line.find("or") != string::npos ||
            line.find("nor") != string::npos ||
            line.find("xor") != string::npos ||
            line.find("not") != string::npos) {
            lines.push(line);

        }

        //If an Input is identified use ss to divide the string to other variable types and store it
        if (line.rfind("input", 0) == 0) {
            string keyword;
            char signal;
            stringstream ss(line);
            // The ss used
            ss >> keyword >> signal;

            if (!ss.fail()) {
                //Storing the input in the inputs vector
                inputs.push_back({ signal, false });
            }
            else {
                cerr << "" << line;
            }
        }
        //If a Wire is identified use ss to divide the string to other variable types and store it
        else if (line.rfind("wire", 0) == 0) {
            string keyword;
            char signal;
            stringstream ss(line);
            // The ss used
            ss >> keyword >> signal;

            if (!ss.fail()) {
                //Storing the wire in the wires vector
                wires.push_back({ signal, false });
            }
            else {
                cerr << "" << line;
            }
        }

        else if (line.rfind("output", 0) == 0) {
            string keyword;
            char signal;
            stringstream ss(line);
            // The ss used
            ss >> keyword >> signal;

            if (!ss.fail()) {
                //Storing the output in the output pair
                output = { signal, false };
            }
            else {
                cerr << "";
            }
        }
        else {
            cerr << "";
        }
    }
}

//A Function that store the time delay of the gates in a vector in order to be able to use it multiple times without the need of generating it again
void Module::delaycal() {

    int commandcount = lines.size();

    //Resizing the timedelay vector
    timedelay.resize(commandcount);

    //Iterate over all the lines left in the queue after the processModuleQueue() function
    for (int i = 0; i < commandcount; ++i) {
        string command = lines.front();
        lines.pop();

        //when "endmodule;", that is our stoping condition
        if (command == "endmodule;") {
            lines.push(command);
            return;
        }

        //the next lines search for "#(time delay)", when "#(" is found the string after it is converted to int using stoi and the whole part is erased to make it easier for processGates(int& t, vector<string>& output) function.
        size_t delayStart = command.find("#(");
        int delay = 0;
        if (delayStart != string::npos) {
            size_t delayEnd = command.find(")", delayStart);
            delay = stoi(command.substr(delayStart + 2, delayEnd - delayStart - 2));
            command.erase(delayStart, delayEnd - delayStart + 1);
        }

        //the delay found is stored in the vector using its index to match the gate
        timedelay[i] = delay;
        lines.push(command);
    }

}

//A Function that Identifies the gates and then call the function correspond to each gate and update the output of the gate
void Module::processGates(int& t, vector<string>& output) {

    int commandCount = lines.size();
    // A string of the data that will be written in the simulation file
    string outputString;


    //Iterate over all the lines left in the queue after the processModuleQueue() function
    for (int i = 0; i < commandCount; ++i) {
        string command = lines.front();
        lines.pop();

        //When "endmodule;" is found, that is our stopping condition
        if (command == "endmodule;") {
            return;
        }


        //Now After the delaycal() was previously called, the line format changed from, GateType #(delay) GateName(output,input,input);, to GateType GateName(output,input,input);
        /// ss is used to identifiy the Gatetype and name
        istringstream ss(command);
        string gateType;
        string gateName;
        ss >> gateType >> gateName;

        //The remainin block is called wireInfo,(output,input,input);
        string wireInfo;
        ss >> wireInfo;

        //Check that the wireInfo is the part that we want be checking the start and end of the string
        if (wireInfo.front() == '(' && wireInfo.back() == ';') {
            wireInfo = wireInfo.substr(1, wireInfo.length() - 2);

            //After removing the ( from the begining and the ; from the end in the previous line, output is now positioned in the begining of the WireInfo in the 0 index
            char out = wireInfo.at(0);
            vector <char> in;
            //Iterate over the remaining positions and store the inputs when identitied
            for (int i = 1; i < wireInfo.length(); i++) {
                if ((wireInfo.at(i) != ',') && (wireInfo.at(i) != ')')) {
                    in.push_back(wireInfo.at(i));
                }
            }
            //For the following if conditions, Identify the function that you need to call corresponding to the gate type , and then get the boolean value of the inputs and then set the boolean value of the output , update the time by the time delay of the gate and use ss to convert the time, output and result into a srting and store it in the output string
            if (gateType == "not") {
                bool result = Not(getBoolValue(in[0]));
                setBoolValue(out, result);
                t += timedelay[i];
                stringstream ss;
                ss << t << " " << out << " = " << result;
                outputString = ss.str();
            }
            else {
                if (gateType == "and") {
                    bool result = And(getBoolValue(in[0]), getBoolValue(in[1]));
                    setBoolValue(out, result);
                    t += timedelay[i];
                    stringstream ss;
                    ss << t << " " << out << " = " << result;
                    outputString = ss.str();
                }
                else if (gateType == "or") {
                    bool result = Or(getBoolValue(in[0]), getBoolValue(in[1]));
                    setBoolValue(out, result);
                    t += timedelay[i];
                    stringstream ss;
                    ss << t << " " << out << " = " << result;
                    outputString = ss.str();
                }
                else if (gateType == "nand") {
                    bool result = Nand(getBoolValue(in[0]), getBoolValue(in[1]));
                    setBoolValue(out, result);
                    t += timedelay[i];
                    stringstream ss;
                    ss << t << " " << out << " = " << result;
                    outputString = ss.str();
                }
                else if (gateType == "xor") {
                    bool result = Xor(getBoolValue(in[0]), getBoolValue(in[1]));
                    setBoolValue(out, result);
                    t += timedelay[i];
                    stringstream ss;
                    ss << t << " " << out << " = " << result;
                    outputString = ss.str();
                }
                else if (gateType == "nor") {
                    bool result = Nor(getBoolValue(in[0]), getBoolValue(in[1]));
                    setBoolValue(out, result);
                    t += timedelay[i];
                    stringstream ss;
                    ss << t << " " << out << " = " << result;
                    outputString = ss.str();
                }
            }
        }
        //Store the output string in the vector of strings that will be written in the Simulation File
        output.push_back(outputString);
        lines.push(command);
    }
}


