#include <Wire.h>
#include <Adafruit_AMG88xx.h>
#include <Adafruit_CCS811.h>
Adafruit_AMG88xx ThermalImager;
Adafruit_CCS811 GasDetector;
int CO2level = 0;
float amg88_pixels[AMG88xx_PIXEL_ARRAY_SIZE];
float MINTEMP = 10.0;
float MAXTEMP = 50.0;

void SensorsInitialize() {
	ThermalImager.begin();
	GasDetector.begin();
}

void ReadSensors() {
	CO2level = (GasDetector.geteCO2() * 0.5) + (CO2level * 0.5);
	ThermalImager.readPixels(amg88_pixels);
	for (int i=0; i < AMG88xx_PIXEL_ARRAY_SIZE; i++) {
		amg88_pixels[i] = (map(constrain(amg88_pixels[i], MINTEMP, MAXTEMP), MINTEMP, MAXTEMP, 0, 255) * 0.5) + (amg88_pixels[i] * 0.5);
	}
}