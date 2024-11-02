#include <iostream>
//Call the classes created
#include "Module.h"
#include "Stimuli.h"
#include "File.h"

int main()
{
	// Variable that stores the filepath
	string  Filepath;
	vector<string> output;
	File f;
	Module m;
	Stimuli s;
	//initializing the time to -1
	int t = -1;

	//User input: Module File Path
	cout << "Enter the Module File Path" << endl;
	cin >> Filepath;
	//Setting the Module File Path in the File Class
	f.SetFilePath(Filepath);
	//Reading the Module File and storing the strings in a queue
	queue<string> module = f.readFileToQueue();

	//User input: Stimuli File Path
	cout << "Enter the Stimuli File Path" << endl;
	cin >> Filepath;
	//Setting the Stimuli File Path in the File Class
	f.SetFilePath(Filepath);
	//Reading the Stimuli File and storing the strings in a queue
	queue<string> Stimuli = f.readFileToQueue();

	//Setting the Module Queue as the lines queue
	m.SetLines(module);
	//Processing the Module Queue to get the Inputs,Wires and output and store them
	m.processModuleQueue();
	//Identify and store the time delay of the gates from the Module Queue
	m.delaycal();
	//Set the Inputs vector generated in the Module Class in the Stimuli Class
	s.SetInputs(m.GetInputs());

	//Generate the Results that will be stored in the Simulation file till the Stimuli Queue ends
	while (!Stimuli.empty()) {
		//Generate the new bool values of the inputs and store them in output vector.
		s.processStimuliQueue(Stimuli, t, output);
		m.SetInputs(s.GetInputs());
		//Generate the results of the Gates and store them in output vector.
		m.processGates(t, output);
	}

	//User input: Simulation File Path
	cout << "Enter the Simulation File Path" << endl;
	cin >> Filepath;
	//Setting the Stimuli File Path in the File Class
	f.SetFilePath(Filepath);
	//Writing the output vector into the Simulation File
	f.writeVectorToFile(output);

	return 0;
}

