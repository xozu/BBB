var fs = require('fs');
fs.writeFileSync('/sys/class/leds/beaglebone:green:usr3/brightness', '1');
