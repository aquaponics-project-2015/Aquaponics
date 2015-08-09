#include <OneWire.h>
#include <DallasTemperature.h>
#include <NewPing.h>
#include <Timer.h>

#define TRIGGER_PIN_1     11  // Arduino pin tied to trigger pin on the ultrasonic sensor.


#define ECHO_PIN_1        10  // Arduino pin tied to echo pin on the ultrasonic sensor.


#define MAX_DISTANCE    200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define SENSOR_PIN    12

#define SensorPin         A0             //pH meter Analog output to Arduino Analog Input 0
#define Offset            0.00            //deviation compensate
#define samplingInterval  20
#define ArrayLenth        40    //times of collection

#define pumpPin           13              //Pin for the positive end of the pump relay
#define pumpLED   7                 //Optional 
#define waterAmount   16                //Optional 
#define waterInPlants   0.7                //Optional 
#define dryPeriodLed  8
#define DRY_PERIOD 900000

Timer t;
int waterSampleRate = 100;

//Try period testing code
int pumpCycleNum;
int dryThreshold = 10 ; // cycles before dry period
//int dryPeriod = 1800000; // Duration of dry period



/*
https://www.pjrc.com/teensy/td_libs_OneWire.html
http://www.hobbytronics.co.uk/ds18b20-arduino
https://code.google.com/p/arduino-new-ping/
*/

OneWire oneWire(SENSOR_PIN);
DallasTemperature sensor(&oneWire);
NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;
float initialWaterLevel;
bool pumpState;

void setup(){
  sensor.begin(); 
  Serial.begin(9600); 
  pinMode(pumpPin, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pumpState = FALSE;
  t.every(60000,getReadings); //Update rate for the server
  initialWaterLevel = waterAmount;
  pumpCycleNum = 0;
}

void loop(){
  t.update();
  checkWater();

}





float getWaterLevelAccurate(){
  float readings[waterSampleRate];
  float sum = 0;
        

  for (int i = 0; i < waterSampleRate; ++i){
    unsigned int uS_1 = 0;
    while(uS_1==0){
      uS_1 = sonar1.ping();
      delay(50);
    }
    readings[i] = (float) uS_1 / US_ROUNDTRIP_CM;
    
     //delay(100);
  }

  for (int i = 0; i < waterSampleRate; ++i){
    sum= sum + readings[i];

  }
 

  float wata = (float) sum/(waterSampleRate);
  
  float accuratewaterlevel = 30 - wata;
  return accuratewaterlevel; //Only one sensor  
}

float getTemp(){
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
  //return currentTemp1;
}

float getpH(){
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

void getReadings(){
  float avgWaterlevel = getWaterLevelAccurate();
  float phVal = getpH();
  float avgTemp = getTemp();
  
  Serial.print("1");
  Serial.print(",");
  Serial.print(avgWaterlevel);
  Serial.print(",");
  Serial.print(phVal);
  Serial.print(",");
  Serial.print(avgTemp);
  Serial.print(",");
  Serial.print(pumpState);
  Serial.print(",");
  Serial.print("\n");
}

void getPumpReading(){
  Serial.print("2");
  Serial.print(",");
  if(pumpState){
    Serial.print("On");
  }else{
    Serial.print("Off");
  }
  Serial.print(",");
  Serial.print("\n");
}

void checkWater(){
  float waterLevel = getWaterLevelAccurate();
  float upperLimit = initialWaterLevel;
  float lowerLimit = initialWaterLevel-waterInPlants;
  if(waterLevel>=upperLimit && !pumpState){
      float waterLevel2 = getWaterLevelAccurate();
      if(waterLevel>=upperLimit){
       if(pumpCycleNum>= dryThreshold){
          digitalWrite(dryPeriodLed,HIGH);
          Serial.print("3,Entering dry period");
          delay(1000);
          unsigned long startMillis = millis();
          while (millis() - startMillis < DRY_PERIOD);
          digitalWrite(dryPeriodLed,LOW);
          pumpCycleNum = 0;
      }
       turnOnPump(TRUE);
       pumpCycleNum = pumpCycleNum + 1;
       Serial.print("3,Cyles: ");
       Serial.print(pumpCycleNum);
       Serial.print("\n");
      }

  }
  if(waterLevel<lowerLimit && pumpState ){
     turnOnPump(FALSE); 
  }
  float phVal = getpH();
  float avgTemp = getTemp();
  Serial.print("3");
  Serial.print(",");
  Serial.print(waterLevel);
  Serial.print(",");
  Serial.print(phVal);
  Serial.print(",");
  Serial.print(avgTemp);
  Serial.print(",");
  Serial.print(pumpState);
  Serial.print(",");
  Serial.print("\n");
}

void turnOnPump(boolean pumpAction){
  if(pumpAction){
    digitalWrite(pumpPin, HIGH);
    digitalWrite(7, HIGH);
    pumpState = TRUE;
    getPumpReading();
  }else{
    digitalWrite(pumpPin, LOW);
    digitalWrite(7, LOW);
    pumpState = FALSE;
    getPumpReading();
  }
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


  



