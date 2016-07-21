#!/bin/bash
file="/sys/class/gpio/gpio49"
if [ ! -e $file ]; then
	echo 49 > /sys/class/gpio/export
fi

echo "out" > /sys/class/gpio/gpio49/direction

COUNTER=0
while [ $COUNTER -lt 100000 ]; do 
	echo 0 > /sys/class/gpio/gpio49/value
	echo "       0"
	sleep 1.0

	echo 1 > /sys/class/gpio/gpio49/value
	echo "                      1"	
	sleep 1.0

	let COUTER=COUNTER+1
done
echo 49 > /sys/class/gpio/unexport

