/*
The OOP concepts can now be applied a real C++ application on the BBB, by
restructuring the functionally oriented C++ code into a class called LED, which
contains states and methods. One difference with the code that is presented in
Listing 5-16 is that it allows you to control the four user LEDs using the same
OO code.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#define LED_PATH "/sys/class/leds/beaglebone:green:usr"

class LED{
	private:
		string path;
		int number;
		virtual void writeLED(string filename, string value);
		virtual void removeTrigger();
	public:
		LED(int number);
		virtual void turnOn();
		virtual void turnOff();
		virtual void flash(string delayms);
		virtual void outputStatus();
		virtual ~LED();
};

// The keyword virtual is also new.
// You can think of this keyword as "allowing overriding to take place when an object is dynamically bound."
LED::LED(int number){
	this->number = number;			// set number state to be the number passed
	// next part is easier with C++11 (see Chp.7) using to_string(number)
	ostringstream s;				// using a stream to construct the path
	s << LED_PATH << number;		// append LED number to LED_PATH
	path = string(s.str());			// convert back from stream to string
}

void LED::writeLED(string filename, string value){
	ofstream fs;
	fs.open((path + filename).c_str());
	fs << value;
	fs.close();
}

void LED::removeTrigger(){
	writeLED("/trigger", "none");
}

void LED::turnOn(){
	cout << "Turning LED" << number << " On" << endl;
	removeTrigger();
	writeLED("/brightness", "1");
}

void LED::turnOff(){
	cout << "Turning LED" << number << " Off" << endl;
	removeTrigger();
	writeLED("/brightness", "0");
}

void LED::flash(string delayms = "50"){
	cout << "Making LED" << number << " flash." << endl;
	writeLED("/trigger", "timer");
	writeLED("/delay_on", delayms);
	writeLED("/delay_off", delayms);
}

void LED::outputStatus(){
	ifstream fs;
	fs.open((path + "/trigger").c_str());
	string line;
	while(getline(fs, line)) cout << line << endl;
	fs.close();
}

LED::~LED(){
	// A destructor - called when the object is destroyed
	cout << "destroying the LED with path: " << path << endl;
}

int main(int argc, char *argv[]){
	if(argc != 2){
		cout << "Usage: makeLED flash" << endl;
		return -1;
	}
	string cmd(argv[1]);

	// Create four LED objects and put them in an array
	// Therefore, using the LED class, four different LED instance objects are created,
	// each controlling one of the BBB's four physical user LEDs.
	LED leds[4] = { LED(0), LED(1), LED(2), LED(3) };

	// Do the same operation on all four LEDS - easily changed!
	for(int i = 0; i < 4; i++){
		if(cmd == "on") leds[i].turnOn();
		else if (cmd == "off") leds[i].turnOff();
		else if (cmd == "flash") leds[i].flash("100");
		else if (cmd == "status") leds[i].outputStatus();
		else cout << "Invalid Command!" << endl;
	}
	return 0;
}
