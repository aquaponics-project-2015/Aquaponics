#include <OneWire.h>
#include <DallasTemperature.h>
#include <NewPing.h>

#define TRIGGER_PIN_1  	  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define TRIGGER_PIN_2  	  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.

#define ECHO_PIN_1     	  10  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define ECHO_PIN_2     	  11  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define MAX_DISTANCE 	  200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define SENSOR_PIN	  2

#define SensorPin         A0            //pH meter Analog output to Arduino Analog Input 0
#define Offset            0.00            //deviation compensate
#define samplingInterval  20
#define ArrayLenth        40    //times of collection

/*
https://www.pjrc.com/teensy/td_libs_OneWire.html
http://www.hobbytronics.co.uk/ds18b20-arduino
https://code.google.com/p/arduino-new-ping/
*/

OneWire oneWire(SENSOR_PIN);
DallasTemperature sensor(&oneWire);
NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;

void setup()
{
	sensor.begin();	
	Serial.begin(9600);
}

void loop()
{
  float avgWaterlevel = getWaterLevel();
  float phVal = getpH();
  float avgTemp = getTemp();
  
  Serial.print(avgWaterlevel);
  Serial.print(",");
  Serial.print(phVal);
  Serial.print(",");
  Serial.print(avgTemp);
  Serial.print(",");
  if(isPump())
    Serial.print("On");  
  else
    Serial.print("Off");  

  delay(1000);
}

float getWaterLevel()
{
  unsigned int uS_1 = sonar1.ping();
  unsigned int uS_2 = sonar2.ping();
  float left_water_level = uS_1 / US_ROUNDTRIP_CM;
  float right_water_level = uS_2 / US_ROUNDTRIP_CM;
  float avgWaterLevel = (left_water_level + right_water_level) / 2;
  
  if(abs(left_water_level - avgWaterLevel) > 10
    || abs(right_water_level - avgWaterLevel) > 10)
  {
    //smn wrong
  }
  return avgWaterLevel;
}

float getTemp()
{
  float currentTemp1, currentTemp2;
  sensor.requestTemperatures();
  currentTemp1 = sensor.getTempCByIndex(0);
  currentTemp2 = sensor.getTempCByIndex(1);

  float avgTemp = (currentTemp1 + currentTemp1) / 2;
  
  if(abs(currentTemp1 - avgTemp) > 3 
    || abs(currentTemp2 - avgTemp) > 3)
  {
    //smn wrong
  }
  return avgTemp;
}

float getpH()
{
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = 3.5*voltage+Offset;
      samplingTime=millis();
  }
  //if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  //{
	//Serial.print("Voltage:");
       // Serial.print(voltage,2);
        //Serial.print("    pH value: ");
	//Serial.println(pHValue);
  return pHValue;
        //digitalWrite(LED,digitalRead(LED)^1);
        //printTime=millis();
  //}
}
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}
