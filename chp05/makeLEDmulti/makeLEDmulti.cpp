/**
Simple On-board LED flashing program - written by C++ by Derek Molloy
simple functional structure for the Exploring BeagleBone book

This program uses USR LED 3 and can be executed in three ways:

	makeLED on
	makeLED off
	makeLED flash (flash at 100ms intervals - on 50ms/off 50ms)
	makeLED status (get the trigger status)
*/
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

void writeLED(string filename, string value){
	fstream fs;
	string path(LED3_PATH);
	fs.open((path + filename).c_str(), fstream::out);
	fs << value;
	fs.close();
}

bool endsWith(string const &in, string const &comp){
	return (0 == in.compare(in.length()-comp.length(), comp.length(), comp));
}

void removeTrigger(){
	writeLED("/trigger", "none");
}

int main(int argc, char* argv[]){
/*	if(argc != 2){
		cout << "Usage is makeLED and one of: " << endl;
		cout << "	on, off, flash or status" << endl;
		cout << "	e.g. makeLED flash" << endl;
		return 2;
	}*/
	string cmd(argv[0]);
	cout << "Starting the makeLED program" << endl;
	cout << "The current LED Path is: " << LED3_PATH << endl;

	// select whether command is on, off, flash or status
	if(endsWith(cmd, "onled")){
		cout << "Turning the LED on" << endl;
		removeTrigger();
		writeLED("/brightness", "1");
	}
	else if(endsWith(cmd, "offled")){
		cout << "Turning the LED off" << endl;
		removeTrigger();
		writeLED("/brightness", "0");
	}
	else if(endsWith(cmd, "flashled")){
		cout << "Flashing the LED" << endl;
		writeLED("/trigger", "timer");
		writeLED("/delay_on", "50");
		writeLED("/delay_off", "50");
	}
	else if (endsWith(cmd, "ledstatus")){
		// display the current trigger details
		std::fstream fs;
		fs.open(LED3_PATH "/trigger", std::fstream::in);
		string line;
		while(getline(fs, line)) cout << line << endl;
		fs.close();
	}
	else{
		cout << "Invalid command!" << endl;
	}
	cout << "Finished the makeLED Program" << endl;
	return 0;
}
