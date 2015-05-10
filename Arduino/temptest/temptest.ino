#include <OneWire.h>
#include <DallasTemperature.h>

/*
https://www.pjrc.com/teensy/td_libs_OneWire.html
http://www.hobbytronics.co.uk/ds18b20-arduino
*/

OneWire oneWire(2);
DallasTemperature sensor(&oneWire);

void void setup()
{
	sensor.begin();	
	Serial.begin(9600);
}

void loop()
{
	tempSensor.requestTemperature();

	float currentTemp0, currentTemp1;
	currentTemp0 = sensor.getTempCBYIndex(0);
	currentTemp1 = sensor.getTempCBYIndex(1);

	float avgTemp = (currentTemp0 + currentTemp0)/2;

	Serial.write(avgTemp);
	delay(1);
}