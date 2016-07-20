#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

void writeLED(char filename[], char value[]);
void removeTrigger();

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("makeLED flash\n");
		return 2;
	}
	printf("Starting the makeLED program\n");
	
	if(strcmp(argv[1], "on") == 0){
		removeTrigger();
		writeLED("/brightness", "1");
	}
	else if(strcmp(argv[1], "off") == 0){
		removeTrigger();
		writeLED("/brightness", "0");
	}
	else if (strcmp(argv[1], "flash") == 0){
		writeLED("/trigger", "timer");
		writeLED("/delay_on", "50");
		writeLED("/delay_off", "50");
	}
	else{
		printf("Invalid Command!");
	}

	return 0;
}

void writeLED(char filename[], char value[]){
	FILE* fp;
	char fullFileName[100];
	sprintf(fullFileName, LED3_PATH "%s", filename);
	fp = fopen(fullFileName, "w+");
	fprintf(fp, "%s", value);
	fclose(fp);
}

void removeTrigger(){
	writeLED("/trigger", "none");
}
