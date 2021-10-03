#include "Sensors.h"
#include "Motors.h"
byte inputarray[100];

void setup() {
  Serial.begin(115200);
  MotorsInitialize();
}

void SerialOperations() {
	for (int x = 0; x < sizeof(inputarray) / sizeof(inputarray[0]); x++){
		inputarray[x] = 0;
	}
  	Serial.flush();
  	if(Serial.available()){
  		Serial.readBytesUntil('\n', inputarray, sizeof(inputarray))
  	}
    //Control motors
  	for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
      	Serial.print(pixels[i-1]);
      	Serial.print(", ");
    }
  	Serial.println(CO2level);
}

void loop() {
  ReadSensors();
  SerialOperations();
}
