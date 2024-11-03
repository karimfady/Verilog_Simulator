#include "File.h"

File::File() {}


//Takes the File Path String and set it in the class
void File::SetFilePath(string x) {
    filePath = x;

}

//Reads the Lines of the file and save them as  a queue
queue<string> File::readFileToQueue() {
    ifstream file(filePath);
    if (!file.is_open()) {
        //Error Message if the file did not open
        cerr << "Error: Could not open the file: " << filePath << endl;
        return {};
    }

    //The queue string that will be returned
    queue<string> fileContents;
    string line;

    //A loop around the whole file
    while (getline(file, line)) {

        //Only push the lines with content
        if (!line.empty() && !all_of(line.begin(), line.end(), [](unsigned char c) { return isspace(c); })) {
            fileContents.push(line);
        }
    }

    file.close();
    return fileContents;
}

//A function to write the Result in the Simulation File
void File::writeVectorToFile(const vector<string>& output) {

    //Opening the File
    ofstream file(filePath);
    if (!file) {
        throw std::ios_base::failure("Failed to open file: " + filePath);
    }

    //Iterating around the vector to write in the file
    for (const auto& line : output) {
        file << line << '\n';
    }

    file.close();
}
File::~File() {}
