#include <OneWire.h>
#include <DallasTemperature.h>
#include <NewPing.h>

#define TRIGGER_PIN_1  	12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define TRIGGER_PIN_2  	13  // Arduino pin tied to trigger pin on the ultrasonic sensor.

#define ECHO_PIN_1     	10  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define ECHO_PIN_2     	11  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define MAX_DISTANCE 	200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define SENSOR_PIN	2

/*
https://www.pjrc.com/teensy/td_libs_OneWire.html
http://www.hobbytronics.co.uk/ds18b20-arduino
https://code.google.com/p/arduino-new-ping/
*/

OneWire oneWire(SENSOR_PIN);

DallasTemperature sensor(&oneWire);
#include <OneWire.h>
#include <DallasTemperature.h>
#include <NewPing.h>

#define TRIGGER_PIN_1  	12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define TRIGGER_PIN_2  	13  // Arduino pin tied to trigger pin on the ultrasonic sensor.

#define ECHO_PIN_1     	10  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define ECHO_PIN_2     	11  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define MAX_DISTANCE 	200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define SENSOR_PIN	2

/*
https://www.pjrc.com/teensy/td_libs_OneWire.html
http://www.hobbytronics.co.uk/ds18b20-arduino
https://code.google.com/p/arduino-new-ping/
*/

OneWire oneWire(SENSOR_PIN);

DallasTemperature sensor(&oneWire);

NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);

void setup()
{
	sensor.begin();	
	Serial.begin(9600);
}

void loop()
{
	unsigned int uS_1 = sonar1.ping();
	unsigned int uS_2 = sonar2.ping();
	float left_water_level = uS_1 / US_ROUNDTRIP_CM;
	float right_water_level = uS_2 / US_ROUNDTRIP_CM;
	float avgWaterLevel = (left_water_level + right_water_level) / 2;

	float currentTemp1, currentTemp2;
	sensor.requestTemperatures();
	currentTemp1 = sensor.getTempCByIndex(0);
	currentTemp2 = sensor.getTempCByIndex(1);

	float avgTemp = (currentTemp1 + currentTemp1) / 2;

	if(abs(left_water_level - avgWaterLevel) > 10 
		|| abs(right_water_level - avgWaterLevel) > 10)
	{
		//smn wrong
	}

	if(abs(currentTemp1 - avgTemp) > 3 
		|| abs(currentTemp2 - avgTemp) > 3)
	{
		//smn wrong
	}

	//test code, change print to write
	Serial.print("current average temperature: \t");
	Serial.print(avgTemp);
	Serial.println("degC");

	Serial.print("average water level: \t\t");
	Serial.print(avgWaterLevel);
	Serial.println("cm\n");

	delay(1000);
}
NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);

void void setup()
{
	sensor.begin();	
	Serial.begin(9600);
}

void loop()
{
	unsigned int uS_1 = sonar1.ping();
	unsigned int uS_2 = sonar2.ping();
	float left_water_level = uS_1 / US_ROUNDTRIP_CM;
	float right_water_level = uS_2 / US_ROUNDTRIP_CM;
	float avgWaterLevel = (left_water_level + right_water_level) / 2;

	float currentTemp1, currentTemp2;
	tempSensor.requestTemperature();
	currentTemp1 = sensor.getTempCBYIndex(0);
	currentTemp2 = sensor.getTempCBYIndex(1);

	float avgTemp = (currentTemp1 + currentTemp1) / 2;

	if(abs(left_water_level - avgWaterLevel) > 10 
		|| abs(right_water_level - avgWaterLevel) > 10)
	{
		//smn wrong
	}

	if(abs(currentTemp1 - avgTemp) > 3 
		|| abs(currentTemp2 - avgTemp) > 3)
	{
		//smn wrong
	}

	//test code, change print to write
	Serial.print("current average temperature: \t")
	Serial.print(avgTemp);
	Serial.println("degC\n");

	Serial.print("average water level: \t");
	Serial.print(avgWaterLevel);
	Serial.println("cm\n");

	delay(1000);
}