#include <URTouch.h>
#include <URTouchCD.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include  <SPI.h>


#define Probe1 2
#define Probe2 1

#define TFT_DC 9              
#define TFT_CS 10             
#define TFT_RST 8             
#define TFT_MISO 12           
#define TFT_MOSI 11           
#define TFT_CLK 13          

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

OneWire oneWire(Probe1);
OneWire oWire(Probe2);

DallasTemperature sensors1(&oneWire);
DallasTemperature sensors2(&oWire);

float Celsius1 = 0;
float Fahrenheit1 = 0;

float Celsius2 = 0;
float Fahrenheit2 = 0;

float maxTemperature=0;
float minTemperature=200;
char charMinTemperature[10];
char charMaxTemperature[10];
//char timeChar[100];
//char dateChar[50];
char temperatureChar[10];

float temperature = 0;
float previousTemperature = 0;

void setup() {
  
  Serial.begin(9600);
  tft.begin();                      
  tft.setRotation(0);            
  tft.fillScreen(ILI9341_BLACK);

  Wire.begin();
  sensors1.begin();
  sensors2.begin();

  printText("TEMPERATURE", ILI9341_GREEN,20,130,3);
  printText("MAX", ILI9341_RED,37,260,2);
  printText("MIN", ILI9341_BLUE,173,260,2);

}


void loop(void) {

  sensors1.requestTemperatures();
  Celsius1 = sensors1.getTempCByIndex(0);
  float temperature = Celsius1;
//  
if(temperature != previousTemperature)
  {
    previousTemperature = temperature;
    String temperatureString = String(temperature,1);
    //temperatureString.toCharArray(temperatureChar,10);
    tft.fillRect(50,175,150,40,ILI9341_BLACK);
    printTxt(temperatureString, ILI9341_WHITE,50,180,4);
    printTxt("o", ILI9341_WHITE,158,175,3);
    printTxt("C", ILI9341_WHITE,180,180,4);
//
if(temperature>maxTemperature)
    {
      maxTemperature = temperature;
      dtostrf(maxTemperature,5, 1, charMaxTemperature); 
      tft.fillRect(8,280,90,28,ILI9341_BLACK);
      printText(charMaxTemperature, ILI9341_WHITE,8,290,2);
      printText("o", ILI9341_WHITE,70,280,2);
      printText("C", ILI9341_WHITE,85,290,2);
    }
if(temperature  < minTemperature) 

 {
      minTemperature = temperature;
      dtostrf(minTemperature,5, 1, charMinTemperature); 
      tft.fillRect(145,280,90,28,ILI9341_BLACK);
      printText(charMinTemperature, ILI9341_WHITE,145,290,2);
      printText("o", ILI9341_WHITE,207,280,2);
      printText("C", ILI9341_WHITE,222,290,2);
    }
  }

    delay(1000);
}

void printText(char *text, uint16_t color, int x, int y,int textSize)
{
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.setTextWrap(true);
  tft.print(text);
}

void printTxt(String text, uint16_t color, int x, int y,int textSize)
{
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.setTextWrap(true);
  tft.print(text);
}
