// Ignore the first two arguments (nodejs and the program name)
var myArgs = process.argv.slice(2);
var LED3_PATH = "/sys/class/leds/beaglebone:green:usr3"
var fs = require('fs');

function writeLED(filename, value, path){
	try{
		// the next call must be synchronous, otherwise the timer will not work
		fs.writeFileSync(path + filename, value);
	}
	catch(err){
		console.log("The write failed to the file: " + path+filename);
	}
}
function removeTrigger(){
	writeLED("/trigger", "none", LED3_PATH);
}

console.log("Starting the LED Node.js Program.");

if(myArgs[0] == null){
	console.log("There is an incorrect number of argument.");
	process.exit(2);
}
switch(myArgs[0]){
	case "on":
		console.log("Turning the LED On");
		removeTrigger();
		writeLED("/brightness", "1", LED3_PATH);
		break;
	case "off":
		console.log("Turning the LED Off");
		removeTrigger();
		writeLED("/brightness", "0", LED3_PATH);
		break;
	case "flash":
		console.log("Flashing the LED");
		writeLED("/trigger", "timer", LED3_PATH);
		writeLED("/delay_on", "50", LED3_PATH);
		writeLED("/delay_off", "50", LED3_PATH);
		break;
	case "status":
		console.log("Getting the LED Status");
		fs.readFile(LED3_PATH+"/trigger", 'utf8', function(err, data){
			if(err) { return console.log(err); }
			console.log(data);
		});
		break;
	default:
		console.log("Invalid Command.");
		break;
}
console.log("End of Node.js script");
