#include <OneWire.h>
#include <DallasTemperature.h>

#define Probe1 3
#define Probe2 2

OneWire oneWire(Probe1);
OneWire oWire(Probe2);

DallasTemperature sensors1(&oneWire);
DallasTemperature sensors2(&oWire);

float Celsius1 = 0;
float Fahrenheit1 = 0;

float Celsius2 = 0;
float Fahrenheit2 = 0;

void setup() {
  sensors1.begin();
  sensors2.begin();
  Serial.begin(9600);
  //Serial.println("CLEARDATA");
  //Serial.println("LABEL,Current time,Sensor value");
}

void loop() {
  sensors1.requestTemperatures();

  Celsius1 = sensors1.getTempCByIndex(0);
  Fahrenheit1 = sensors1.toFahrenheit(Celsius1);

  Serial.print("Probe 1: ");
  Serial.print(Celsius1);
  Serial.print(" C  ");
  Serial.print(Fahrenheit1);
  Serial.println(" F");

sensors2.requestTemperatures();

  Celsius2 = sensors2.getTempCByIndex(0);
  Fahrenheit2 = sensors2.toFahrenheit(Celsius2);

  Serial.print("Probe 2: ");
  Serial.print(Celsius2);
  Serial.print(" C  ");
  Serial.print(Fahrenheit2);
  Serial.println(" F");

Serial.println("___________________");
  delay(1000);

  
}
