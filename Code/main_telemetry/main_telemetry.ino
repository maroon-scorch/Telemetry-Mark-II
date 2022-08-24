//#include <UTFT.h>
#include <URTouch.h>
#include <URTouchCD.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include  <SPI.h>

#define Probe1 3
#define Probe2 2

#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8
#define TFT_MISO 12
#define TFT_MOSI 11
#define TFT_CLK 13

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

//#define t_SCK 3
//#define t_CS 4
//#define t_MOSI 5
//#define t_MISO 6
//#define t_IRQ 7

#define t_SCK 29
#define t_CS 27
#define t_MOSI 25
#define t_MISO 23
#define t_IRQ 22

URTouch myTouch(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ);

OneWire oneWire(Probe1);
OneWire oWire(Probe2);

DallasTemperature sensors1(&oneWire);
DallasTemperature sensors2(&oWire);

float Celsius1 = 0;
float Fahrenheit1 = 0;

float Celsius2 = 0;
float Fahrenheit2 = 0;

float maxTemperature = 0;
float minTemperature = 200;
char charMinTemperature[10];
char charMaxTemperature[10];
//char timeChar[100];
//char dateChar[50];
char temperatureChar[10];

float temperature = 0;
float previousTemperature = 0;

int analogValue;
float R1 = 11000;
float R2 = 1000;
float voltage;

char currentPage, selectedAuxTemp, selectedMainTemp;

/*
-------------------------------------------------------------------------------------------------------------------------
The following colors are also from Kris Kasprzak's graphing functions from https://www.youtube.com/watch?v=U5hOU-xxQgk
-------------------------------------------------------------------------------------------------------------------------
*/

#define LTBLUE    0xB6DF
#define LTTEAL    0xBF5F
#define LTGREEN         0xBFF7
#define LTCYAN    0xC7FF
#define LTRED           0xFD34
#define LTMAGENTA       0xFD5F
#define LTYELLOW        0xFFF8
#define LTORANGE        0xFE73
#define LTPINK          0xFDDF
#define LTPURPLE  0xCCFF
#define LTGREY          0xE71C

#define BLUE            0x001F
#define TEAL    0x0438
#define GREEN           0x07E0
#define CYAN          0x07FF
#define RED           0xF800
#define MAGENTA       0xF81F
#define YELLOW        0xFFE0
#define ORANGE        0xFD20
#define PINK          0xF81F
#define PURPLE    0x801F
#define GREY        0xC618
#define WHITE         0xFFFF
#define BLACK         0x0000

#define DKBLUE        0x000D
#define DKTEAL    0x020C
#define DKGREEN       0x03E0
#define DKCYAN        0x03EF
#define DKRED         0x6000
#define DKMAGENTA       0x8008
#define DKYELLOW        0x8400
#define DKORANGE        0x8200
#define DKPINK          0x9009
#define DKPURPLE      0x4010
#define DKGREY        0x4A49
/*
-------------------------------------------------------------------------------------------------------------------------
End of Colors
-------------------------------------------------------------------------------------------------------------------------
*/
boolean graph_1 = true;
boolean graph_2 = true;
boolean graph_3 = true;
boolean graph_4 = true;
boolean graph_5 = true;
boolean graph_6 = true;
boolean graph_7 = true;
boolean graph_8 = true;
boolean graph_9 = true;
boolean graph_10 = true;
boolean graph_11 = true;
boolean graph_12 = true;
boolean graph_13 = true;

boolean display_1 = true;
boolean display_2 = true;
boolean display_3 = true;

boolean zoom_1 = false;
boolean zoom_2 = false;
boolean zoom_3 = false;

double carry_1, carry_2, carry_3;

double t;

void setup() {
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);

  Wire.begin();
  sensors1.begin();
  sensors2.begin();

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

  drawHomeScreen();
  currentPage = '0';

  selectedAuxTemp = '0';
  selectedMainTemp = '0';


}

void loop() {

  //
  if (currentPage == '0') {
    if (myTouch.dataAvailable()) {
      myTouch.read();
      int x = 319 - myTouch.getX(); // X coordinate where the screen has been pressed
      int y = 239 - myTouch.getY(); // Y coordinates where the screen has been pressed

      //      if((x!=-1) && (y!=-1))
      //    {
      //      x += 13;
      //      y += 4;
      //      int radius = 4;
      //      tft.fillCircle(x, y, radius, ILI9341_YELLOW);
      //    }
      //if touching auxiliary temperature
      if ((x >= 80) && (x <= 240) && (y >= 60) && (y <= 110)) {
        drawFrame(80, 60, 240, 110); // Custom Function -Highlighs the buttons when it's pressed
        currentPage = '1'; // Indicates that we are the first example
        tft.fillScreen(BLACK);
        drawAuxTemp();
        graph_1 = true;
        graph_2 = false;
        graph_3 = true;
        graph_4 = false;
      }
      //tft.fillRoundRect(80, 125, 160, 50, 10, ILI9341_BLUE);
      if ((x >= 80) && (x <= 240) && (y >= 125) && (y <= 175)) {
        drawFrame(80, 125, 240, 175); // Custom Function -Highlighs the buttons when it's pressed
        currentPage = '2'; // Indicates that we are the first example
        tft.fillScreen(BLACK);
        drawMainTemp();
        graph_5 = true;
        graph_6 = false;
        graph_7 = true;
        graph_8 = false;
      }

      //tft.fillRoundRect(80, 190, 160, 50, 10, ILI9341_GREEN);
      if ((x >= 80) && (x <= 240) && (y >= 190) && (y <= 240)) {
        drawFrame(80, 190, 240, 240); // Custom Function -Highlighs the buttons when it's pressed
        currentPage = '3'; // Indicates that we are the first example
        tft.fillScreen(BLACK);
        drawMainVolt();
        graph_9 = true;
        graph_10 = true;
      }

      //tft.fillRoundRect(255,190,50,50,10,BLUE);
      if ((x >= 255) && (x <= 305) && (y >= 190) && (y <= 240)) {
        drawFrame(255, 190, 305, 240); // Custom Function -Highlighs the buttons when it's pressed
        currentPage = '4'; // Indicates that we are the first example
        tft.fillScreen(BLACK);
        drawAllData();
        graph_11 = true;
        graph_12 = true;
        graph_13 = true;
      }
    }
  }

  if (currentPage == '1')
  {
    //graph_1 = true;
    getAuxTemp();
    //tft.fillRoundRect (10, 10, 60, 36,10,WHITE);
    if (myTouch.dataAvailable()) {
      myTouch.read();
      int x = 319 - myTouch.getX();
      int y = 239 - myTouch.getY();

      if ((x >= 10) && (x <= 70) && (y >= 10) && (y <= 46)) {
        drawFrame(10, 10, 70, 46);
        currentPage = '0'; // Indicates we are at home screen
        tft.fillScreen(BLACK);
        graph_1 = false;
        graph_2 = false;
        graph_3 = false;
        graph_4 = false;
        selectedAuxTemp = '0';
        drawHomeScreen(); // Draws the home screen
      }

      if ((x >= 10) && (x <= 90) && (y >= 75) && (y <= 103)) {
        drawFrame(10, 75, 90, 103);
        tft.fillRect(102, 25, 320, 240, BLACK);
        // tft.fillRect(10,165,262,82,BLACK);
        graph_1 = true;
        graph_2 = false;
        graph_3 = true;
        graph_4 = false;
        selectedAuxTemp = '0';
      }

      if ((x >= 10) && (x <= 90) && (y >= 113) && (y <= 141)) {
        drawFrame(10, 113, 90, 141);
        tft.fillRect(102, 25, 320, 240, BLACK);
        //tft.fillRect(165,25,152,152,BLACK);
        //tft.fillRect(10,165,262,82,BLACK);
        graph_1 = false;
        graph_2 = true;
        graph_3 = false;
        graph_4 = true;
        selectedAuxTemp = '1';
      }

      // tft.drawRoundRect (10, 170, 80, 28,10,RED);
      if ((x >= 10) && (x <= 90) && (y >= 150) && (y <= 220)) {
        drawFrame(10, 150, 90, 218);
        currentPage = '5';
        display_1 = true;
        tft.fillScreen(BLACK);
        drawAuxTempGraph();

        graph_1 = false;
        graph_2 = false;
        graph_3 = false;
        graph_4 = false;
        selectedAuxTemp = '0';
      }

    }


  }

  if (currentPage == '2')
  {
    //graph_1 = true;
    getMainTemp();
    //tft.fillRoundRect (10, 10, 60, 36,10,WHITE);
    if (myTouch.dataAvailable()) {
      myTouch.read();
      int x = 319 - myTouch.getX();
      int y = 239 - myTouch.getY();

      if ((x >= 10) && (x <= 70) && (y >= 10) && (y <= 46)) {
        drawFrame(10, 10, 70, 46);
        currentPage = '0'; // Indicates we are at home screen
        tft.fillScreen(BLACK);
        graph_5 = false;
        graph_6 = false;
        graph_7 = false;
        graph_8 = false;
        selectedMainTemp = '0';
        drawHomeScreen(); // Draws the home screen
      }

      if ((x >= 10) && (x <= 90) && (y >= 75) && (y <= 103)) {
        drawFrame(10, 75, 90, 103);
        tft.fillRect(102, 25, 320, 240, BLACK);
        // tft.fillRect(165,25,152,152,BLACK);
        //tft.fillRect(10,165,262,82,BLACK);
        graph_5 = true;
        graph_6 = false;
        graph_7 = true;
        graph_8 = false;
        selectedMainTemp = '0';
      }

      if ((x >= 10) && (x <= 90) && (y >= 113) && (y <= 141)) {
        drawFrame(10, 113, 90, 141);
        tft.fillRect(102, 25, 320, 240, BLACK);
        //tft.fillRect(165,25,152,152,BLACK);
        //tft.fillRect(10,165,262,82,BLACK);
        graph_5 = false;
        graph_6 = true;
        graph_7 = false;
        graph_8 = true;
        selectedMainTemp = '1';
      }

      if ((x >= 10) && (x <= 90) && (y >= 150) && (y <= 220)) {
        drawFrame(10, 150, 90, 218);
        currentPage = '6';
        display_2 = true;
        tft.fillScreen(BLACK);
        drawMainTempGraph();

        graph_5 = false;
        graph_6 = false;
        graph_7 = false;
        graph_8 = false;
        selectedMainTemp = '0';
      }


    }


  }

  if (currentPage == '3')
  {

    getMainVolt();
    if (myTouch.dataAvailable()) {
      myTouch.read();
      int x = 319 - myTouch.getX();
      int y = 239 - myTouch.getY();

      if ((x >= 10) && (x <= 70) && (y >= 10) && (y <= 46)) {
        drawFrame(10, 10, 70, 46);
        currentPage = '0'; // Indicates we are at home screen
        tft.fillScreen(BLACK);
        graph_9 = false;
        graph_10 = false;
        drawHomeScreen(); // Draws the home screen
      }
      //tft.fillRoundRect (0, 180, 60, 48,10,WHITE);
      if ((x >= 0) && (x <= 60) && (y >= 180) && (y <= 230)) {
        drawFrame(0, 180, 60, 228);
        currentPage = '7';
        display_3 = true;
        tft.fillScreen(BLACK);
        drawMainVoltGraph();

        graph_9 = false;
        graph_10 = false;
      }
    }

  }

  if (currentPage == '4')
  {

    getAllData();
    if (myTouch.dataAvailable()) {
      myTouch.read();
      int x = 319 - myTouch.getX();
      int y = 239 - myTouch.getY();

      if ((x >= 10) && (x <= 70) && (y >= 10) && (y <= 46)) {
        drawFrame(10, 10, 70, 46);
        currentPage = '0'; // Indicates we are at home screen
        tft.fillScreen(BLACK);
        graph_11 = false;
        graph_12 = false;
        graph_13 = false;
        drawHomeScreen(); // Draws the home screen
      }
    }

  }

  if (currentPage == '5')
  {
    getAuxTempGraph();
  }

  if (currentPage == '6') {
    getMainTempGraph();
  }

  if (currentPage == '7') {
    getMainVoltGraph();
  }

}

void drawHomeScreen()
{
  tft.fillRect(0, 0, 319, 30, ILI9341_WHITE);
  printText("SOLAR TELEMETRY", 0x03E0, 80, 10, 2);
  drawFrame(0, 0, 319, 30, ILI9341_GREEN);
  printText("by a Programmer who Functions Purely on Dr. Pepper", ILI9341_WHITE, 15, 35, 1);

  //Auxiliary Temperature
  tft.fillRoundRect(80, 60, 160, 50, 10, ILI9341_RED);
  tft.drawRoundRect(80, 60, 160, 50, 10, ILI9341_WHITE);
  printText("AUXILIARY", ILI9341_WHITE, 100, 68, 2);
  printText("TEMPERATURE", ILI9341_WHITE, 92, 90, 2);

  //Main Temperature
  tft.fillRoundRect(80, 125, 160, 50, 10, ILI9341_BLUE);
  tft.drawRoundRect(80, 125, 160, 50, 10, ILI9341_WHITE);
  printText("MAIN", ILI9341_WHITE, 135, 133, 2);
  printText("TEMPERATURE", ILI9341_WHITE, 92, 155, 2);

  //Main Voltage
  tft.fillRoundRect(80, 190, 160, 50, 10, ILI9341_GREEN);
  tft.drawRoundRect(80, 190, 160, 50, 10, ILI9341_WHITE);
  printText("MAIN", ILI9341_WHITE, 135, 198, 2);
  printText("VOLTAGE", ILI9341_WHITE, 112, 220, 2);

  //All Data
  tft.fillRoundRect(255, 190, 50, 50, 10, LTBLUE);
  tft.drawRoundRect(255, 190, 50, 50, 10, WHITE);
  tft.fillCircle(280, 215, 15, BLUE);
  tft.fillCircle(280, 215, 10, LTBLUE);
  //tft.drawCircle(280,215,15,BLUE);
  // printText("O",ILI9341_BLACK,270,205,3);
}

void drawFrame(int x1, int y1, int x2, int y2) {

  tft.drawRoundRect (x1, y1, x2 - x1, y2 - y1, 10, PINK);
  while (myTouch.dataAvailable())
    myTouch.read();
  tft.drawRoundRect (x1, y1, x2 - x1, y2 - y1, 10, WHITE);
}

void drawAuxTemp()
{
  //tft.fillRect(60, 0, 260, 30, ILI9341_WHITE);
  printText("Auxiliary", 0x03E0, 100, 10, 2);

  tft.fillRoundRect (10, 10, 60, 36, 10, WHITE);
  tft.drawRoundRect (10, 10, 60, 36, 10, DKRED);
  printText("<-", RED, 23, 17, 3);

  printText("Select Units", WHITE, 10, 54, 1);

  //tft.fillRoundRect (10, 135, 80, 28, 10, 0xFD20);
  tft.fillRoundRect (10, 75, 80, 28, 10, RED);
  tft.drawRoundRect (10, 75, 80, 28, 10, WHITE);
  printTxt("o", WHITE, 38, 78, 1);
  printText("C", WHITE, 45, 80, 2);

  tft.fillRoundRect (10, 113, 80, 28, 10, RED);
  tft.drawRoundRect (10, 113, 80, 28, 10, WHITE);
  printTxt("o", WHITE, 38, 118, 1);
  printText("F", WHITE, 45, 120, 2);

  tft.fillRoundRect (10, 150, 80, 68, 10, WHITE);
  tft.drawRoundRect (10, 150, 80, 68, 10, RED);
  printText("GRAPH", RED, 20, 177, 2);

  //  printText("o", ILI9341_WHITE,70,140,2);
  //  printText("C", ILI9341_WHITE,85,145,2);

}

void getAuxTemp()
{
  sensors1.requestTemperatures();
  Celsius1 = sensors1.getTempCByIndex(0);
  temperature = Celsius1;
  float temperatureF = sensors1.toFahrenheit(Celsius1);

  if (selectedAuxTemp == '0')
  {
    DrawDial(tft, 245, 140, 75, 20 , 50 , 5, 270, temperature,  3 , 1, WHITE, RED, WHITE, "", graph_1);
    //DrawBarChartH(tft, 10 , 195, 200, 20 , 20 , 50 , 5 , temperature ,  3 , 1, RED, DKRED, RED, WHITE, BLACK, "*C", graph_3);
    DrawBarChartV(tft, 105 , 210, 20, 150 , 20 , 50 , 5 , temperature ,  3 , 1, RED, DKRED, RED, WHITE, BLACK, "*C", graph_3);
    // DrawBarChartH(tft, 100, 250, 300, 30, -2.5, 2.5, .5, temperature, 2, 1, GREEN, DKGREEN,  GREEN, WHITE, BLACK, "Offset", graph_6);
    //DrawBarChartV(tft, 10, 190, 30, 160, 0, 1200 , 100, 500 , 4 , 0, BLUE, DKBLUE, BLUE, WHITE, BLACK, "Bits", graph_3 );
  }

  if (selectedAuxTemp == '1')
  {
    DrawDial(tft, 245, 140, 75, 70 , 120 , 5, 270, temperatureF,  3 , 1, WHITE, RED, WHITE, "", graph_2);
    DrawBarChartV(tft, 105 , 210, 20, 150 , 70 , 120 , 10 , temperatureF, 3 , 1, RED, DKRED, RED, WHITE, BLACK, "*F", graph_4);
  }

}

void drawAuxTempGraph()
{
  tft.fillRoundRect (10, 10, 60, 36, 10, WHITE);
  tft.drawRoundRect (10, 10, 60, 36, 10, DKRED);
  printText("<-", RED, 23, 17, 3);

  tft.fillRoundRect (80, 10, 60, 36, 10, WHITE);
  tft.drawRoundRect (80, 10, 60, 36, 10, DKRED);
  printText("<<", RED, 93, 17, 3);

  tft.fillRoundRect(150, 10, 60, 36, 10, DKRED);
  tft.drawRoundRect(150, 10, 60, 36, 10, WHITE);
  printText("Zoom", WHITE, 158, 22, 2);

}

void getAuxTempGraph()
{
  //sensors1.requestTemperatures();
  // Celsius1 = sensors1.getTempCByIndex(0);

  // float temperatureFa = sensors1.toFahrenheit(Celsius1);
  if (zoom_1 == false) {
    for (double ti = 0; ti <= 60; ti++)
    {
      sensors1.requestTemperatures();
      Celsius1 = sensors1.getTempCByIndex(0);
      //double temperature1a = Celsius1;
      double temperatureFa = sensors1.toFahrenheit(Celsius1);
      Graph(tft, ti, temperatureFa, 40, 210, 250, 152, 0, 60, 10, 70, 120, 10, "", "Time(Sec)", "Temperature(*F)", DKBLUE, RED, YELLOW, WHITE, BLACK, display_1);

      delay(250);

      if (myTouch.dataAvailable()) {
        myTouch.read();
        int x = 319 - myTouch.getX();
        int y = 239 - myTouch.getY();

        if ((x >= 10) && (x <= 70) && (y >= 10) && (y <= 46)) {
          drawFrame(10, 10, 70, 46);
          currentPage = '1'; // Indicates we are at home screen
          tft.fillScreen(BLACK);
          graph_1 = true;
          graph_2 = false;
          graph_3 = true;
          graph_4 = false;

          display_1 = false;
          t = 0;
          drawAuxTemp(); // Draws the home screen
          break;
        }

        if ((x >= 80) && (x <= 140) && (y >= 10) && (y <= 46)) {
          drawFrame(80, 10, 140, 46);
          currentPage = '0'; // Indicates we are at home screen
          tft.fillScreen(BLACK);
          display_1 = false;
          drawHomeScreen();
          break;
        }

        //tft.fillRoundRect(150,10,60,36,10,DKRED);
        if ((x >= 150) && (x <= 210) && (y >= 10) && (y <= 46)) {
          drawFrame(150, 10, 210, 46);
          tft.fillRect(0, 47, 320, 240, BLACK);
          carry_1 = temperatureFa;
          zoom_1 = true;
          break;
        }

      }
    }


    if (currentPage == '5')
    {
      display_1 = true;

      tft.fillRect(0, 47, 320, 240, BLACK);
    }
  }





  if (zoom_1 == true) {

    for (double ti = 0; ti <= 60; ti++)
    {
      sensors1.requestTemperatures();
      Celsius1 = sensors1.getTempCByIndex(0);
      //double temperature1a = Celsius1;
      double temperatureFa = sensors1.toFahrenheit(Celsius1);
      Graph(tft, ti, temperatureFa, 40, 210, 250, 152, 0, 60, 10, carry_1 - 10, carry_1 + 10, 2.5, "", "Time(Sec)", "Temperature(*F)", DKBLUE, RED, YELLOW, WHITE, BLACK, display_1);

      delay(250);

      if (myTouch.dataAvailable()) {
        myTouch.read();
        int x = 319 - myTouch.getX();
        int y = 239 - myTouch.getY();

        if ((x >= 10) && (x <= 70) && (y >= 10) && (y <= 46)) {
          drawFrame(10, 10, 70, 46);
          currentPage = '1'; // Indicates we are at home screen
          tft.fillScreen(BLACK);
          graph_1 = true;
          graph_2 = false;
          graph_3 = true;
          graph_4 = false;
          display_1 = false;
          t = 0;
          drawAuxTemp(); // Draws the home screen
          break;
        }

        if ((x >= 80) && (x <= 140) && (y >= 10) && (y <= 46)) {
          drawFrame(80, 10, 140, 46);
          currentPage = '0'; // Indicates we are at home screen
          tft.fillScreen(BLACK);
          display_1 = false;
          drawHomeScreen();
          break;
        }

        //tft.fillRoundRect(150,10,60,36,10,DKRED);
        if ((x >= 150) && (x <= 210) && (y >= 10) && (y <= 46)) {
          drawFrame(150, 10, 210, 46);
          //carry_1 = temperatureFa;
          zoom_1 = false;
          break;
        }

      }
    }

    if (currentPage == '5')
    {
      display_1 = true;
      sensors1.requestTemperatures();
      Celsius1 = sensors1.getTempCByIndex(0);
      //double temperature1a = Celsius1;
      double temperatureFb = sensors1.toFahrenheit(Celsius1);
      carry_1 = temperatureFb;
      tft.fillRect(0, 47, 320, 240, BLACK);
    }
  }

}



void drawMainTemp()
{
  printText("Main", 0x03E0, 130, 10, 2);

  tft.fillRoundRect (10, 10, 60, 36, 10, WHITE);
  tft.drawRoundRect (10, 10, 60, 36, 10, BLUE);
  printText("<-", BLUE, 23, 17, 3);

  printText("Select Units", WHITE, 10, 54, 1);

  //tft.fillRoundRect (10, 135, 80, 28, 10, 0xFD20);
  tft.fillRoundRect (10, 75, 80, 28, 10, DKBLUE);
  tft.drawRoundRect (10, 75, 80, 28, 10, WHITE);
  printTxt("o", WHITE, 38, 78, 1);
  printText("C", WHITE, 45, 80, 2);

  tft.fillRoundRect (10, 113, 80, 28, 10, BLUE);
  tft.drawRoundRect (10, 113, 80, 28, 10, WHITE);
  printTxt("o", WHITE, 38, 118, 1);
  printText("F", WHITE, 45, 120, 2);

  tft.fillRoundRect (10, 150, 80, 68, 10, WHITE);
  tft.drawRoundRect (10, 150, 80, 68, 10, BLUE);
  printText("GRAPH", BLUE, 20, 177, 2);
}

void getMainTemp()
{
  sensors2.requestTemperatures();
  Celsius2 = sensors2.getTempCByIndex(0);
  float temperature2 = Celsius2;
  float temperatureF = sensors2.toFahrenheit(Celsius2);;

  if (selectedMainTemp == '0')
  {

    DrawDial(tft, 245, 140, 75, 20 , 50 , 5, 270, temperature2,  3 , 1, WHITE, BLUE, WHITE, "", graph_5);
    DrawBarChartV(tft, 105 , 210, 20, 150 , 20 , 50 , 5 , temperature2 ,  3 , 1, BLUE, DKBLUE, BLUE, WHITE, BLACK, "*C", graph_7);
    // DrawBarChartH(tft, 100, 250, 300, 30, -2.5, 2.5, .5, temperature, 2, 1, GREEN, DKGREEN,  GREEN, WHITE, BLACK, "Offset", graph_6);
    //DrawBarChartV(tft, 10, 190, 30, 160, 0, 1200 , 100, 500 , 4 , 0, BLUE, DKBLUE, BLUE, WHITE, BLACK, "Bits", graph_3 );
  }

  if (selectedMainTemp == '1')
  {
    //    DrawDial(tft, 245, 140, 75, 70 , 120 , 5, 270, temperatureF,  3 , 1, WHITE, RED, WHITE, "", graph_2);
    //    DrawBarChartV(tft, 105 , 210, 20, 150 , 70 , 120 , 10 , temperatureF, 3 , 1, RED, DKRED, RED, WHITE, BLACK, "*F", graph_4);
    DrawDial(tft, 245, 140, 75, 70 , 120 , 5, 270, temperatureF,  3 , 1, WHITE, BLUE, WHITE, "", graph_6);
    DrawBarChartV(tft, 105 , 210, 20, 150 , 70 , 120 , 10 , temperatureF, 3 , 1, BLUE, DKBLUE, BLUE, WHITE, BLACK, "*F", graph_8);
  }

}

void drawMainTempGraph()
{
  tft.fillRoundRect (10, 10, 60, 36, 10, WHITE);
  tft.drawRoundRect (10, 10, 60, 36, 10, DKBLUE);
  printText("<-", BLUE, 23, 17, 3);

  tft.fillRoundRect (80, 10, 60, 36, 10, WHITE);
  tft.drawRoundRect (80, 10, 60, 36, 10, DKBLUE);
  printText("<<", BLUE, 93, 17, 3);

  tft.fillRoundRect(150, 10, 60, 36, 10, DKBLUE);
  tft.drawRoundRect(150, 10, 60, 36, 10, WHITE);
  printText("Zoom", WHITE, 158, 22, 2);

}

void getMainTempGraph()
{
  if (zoom_2 == false) {
    for (double ti = 0; ti <= 60; ti++)
    {
      sensors2.requestTemperatures();
      Celsius2 = sensors2.getTempCByIndex(0);
      //double temperature1a = Celsius1;
      double temperatureFa = sensors2.toFahrenheit(Celsius2);
      Graph(tft, ti, temperatureFa, 40, 210, 250, 152, 0, 60, 10, 70, 120, 10, "", "Time(Sec)", "Temperature(*F)", DKBLUE, RED, YELLOW, WHITE, BLACK, display_2);

      delay(250);

      if (myTouch.dataAvailable()) {
        myTouch.read();
        int x = 319 - myTouch.getX();
        int y = 239 - myTouch.getY();

        if ((x >= 10) && (x <= 70) && (y >= 10) && (y <= 46)) {
          drawFrame(10, 10, 70, 46);
          currentPage = '2'; // Indicates we are at home screen
          tft.fillScreen(BLACK);
          graph_5 = true;
          graph_6 = false;
          graph_7 = true;
          graph_8 = false;

          display_2 = false;
          t = 0;
          drawMainTemp(); // Draws the home screen
          break;
        }

        if ((x >= 80) && (x <= 140) && (y >= 10) && (y <= 46)) {
          drawFrame(80, 10, 140, 46);
          currentPage = '0'; // Indicates we are at home screen
          tft.fillScreen(BLACK);
          display_2 = false;
          drawHomeScreen();
          break;
        }

        //tft.fillRoundRect(150,10,60,36,10,DKRED);
        if ((x >= 150) && (x <= 210) && (y >= 10) && (y <= 46)) {
          drawFrame(150, 10, 210, 46);
          tft.fillRect(0, 47, 320, 240, BLACK);
          carry_2 = temperatureFa;
          zoom_2 = true;
          break;
        }

      }
    }


    if (currentPage == '6')
    {
      display_2 = true;

      tft.fillRect(0, 47, 320, 240, BLACK);
    }
  }





  if (zoom_2 == true) {

    for (double ti = 0; ti <= 60; ti++)
    {
      sensors2.requestTemperatures();
      Celsius2 = sensors2.getTempCByIndex(0);
      //double temperature1a = Celsius1;
      double temperatureFa = sensors2.toFahrenheit(Celsius2);
      Graph(tft, ti, temperatureFa, 40, 210, 250, 152, 0, 60, 10, carry_2 - 10, carry_2 + 10, 2.5, "", "Time(Sec)", "Temperature(*F)", DKBLUE, RED, YELLOW, WHITE, BLACK, display_2);

      delay(250);

      if (myTouch.dataAvailable()) {
        myTouch.read();
        int x = 319 - myTouch.getX();
        int y = 239 - myTouch.getY();

        if ((x >= 10) && (x <= 70) && (y >= 10) && (y <= 46)) {
          drawFrame(10, 10, 70, 46);
          currentPage = '2'; // Indicates we are at home screen
          tft.fillScreen(BLACK);
          graph_5 = true;
          graph_6 = false;
          graph_7 = true;
          graph_8 = false;
          display_2 = false;
          t = 0;
          drawMainTemp(); // Draws the home screen
          break;
        }

        if ((x >= 80) && (x <= 140) && (y >= 10) && (y <= 46)) {
          drawFrame(80, 10, 140, 46);
          currentPage = '0'; // Indicates we are at home screen
          tft.fillScreen(BLACK);
          display_2 = false;
          drawHomeScreen();
          break;
        }

        //tft.fillRoundRect(150,10,60,36,10,DKRED);
        if ((x >= 150) && (x <= 210) && (y >= 10) && (y <= 46)) {
          drawFrame(150, 10, 210, 46);
          //carry_1 = temperatureFa;
          zoom_2 = false;
          break;
        }

      }
    }

    if (currentPage == '6')
    {
      display_2 = true;
      sensors2.requestTemperatures();
      Celsius2 = sensors2.getTempCByIndex(0);
      //double temperature1a = Celsius1;
      double temperatureFb = sensors1.toFahrenheit(Celsius1);
      carry_2 = temperatureFb;
      tft.fillRect(0, 47, 320, 240, BLACK);
    }
  }

}

void drawMainVolt()
{
  printText("Main Voltage", 0x03E0, 100, 10, 2);

  tft.fillRoundRect (10, 10, 60, 36, 10, WHITE);
  tft.drawRoundRect (10, 10, 60, 36, 10, GREEN);
  printText("<-", DKGREEN, 23, 17, 3);

  tft.fillRoundRect (0, 180, 60, 48, 10, WHITE);
  tft.drawRoundRect (0, 180, 60, 48, 10, GREEN);
  printText("GRAPH", GREEN, 1, 198, 2);


}

void getMainVolt()
{
  analogValue = analogRead(A0);
  voltage = analogValue * (5.0) / (1023.0);

  float voltout = voltage * (R2 + R1) / R2;
  //    DrawDial(tft, 245, 140, 75, 70 , 120 , 5, 270, temperatureF,  3 , 1, WHITE, RED, WHITE, "", graph_2);
  //    DrawBarChartV(tft, 105 , 210, 20, 150 , 70 , 120 , 10 , temperatureF, 3 , 1, RED, DKRED, RED, WHITE, BLACK, "*F", graph_4);

  DrawDial(tft, 235, 140, 85, 0, 60, 5, 250, voltout,  4 , 2, WHITE, GREEN, WHITE, "Volts", graph_9);
  DrawBarChartV(tft, 75, 210, 20, 150, 0, 60, 5, voltout , 4 , 2, GREEN, DKGREEN, GREEN, WHITE, BLACK, "Volts", graph_10 );
}

void drawMainVoltGraph()
{
  tft.fillRoundRect (10, 10, 60, 36, 10, WHITE);
  tft.drawRoundRect (10, 10, 60, 36, 10, DKGREEN);
  printText("<-", GREEN, 23, 17, 3);

  tft.fillRoundRect (80, 10, 60, 36, 10, WHITE);
  tft.drawRoundRect (80, 10, 60, 36, 10, DKGREEN);
  printText("<<", GREEN, 93, 17, 3);

  tft.fillRoundRect(150, 10, 60, 36, 10, DKGREEN);
  tft.drawRoundRect(150, 10, 60, 36, 10, WHITE);
  printText("Zoom", WHITE, 158, 22, 2);
}

void getMainVoltGraph()
{
  if (zoom_3 == false) {
    for (double ti = 0; ti <= 60; ti++)
    {
      analogValue = analogRead(A0);
      double voltin = analogValue * (5.0) / (1023.0);

      float voltout = voltin * (R2 + R1) / R2;
      Graph(tft, ti, voltout, 40, 210, 250, 152, 0, 60, 10, 0, 60, 10, "", "Time(Sec)", "Voltage(V)", DKBLUE, RED, YELLOW, WHITE, BLACK, display_3);

      delay(250);

      if (myTouch.dataAvailable()) {
        myTouch.read();
        int x = 319 - myTouch.getX();
        int y = 239 - myTouch.getY();

        if ((x >= 10) && (x <= 70) && (y >= 10) && (y <= 46)) {
          drawFrame(10, 10, 70, 46);
          currentPage = '3'; // Indicates we are at home screen
          tft.fillScreen(BLACK);
          graph_9 = true;
          graph_10 = true;

          display_3 = false;
          t = 0;
          drawMainVolt(); // Draws the home screen
          break;
        }

        if ((x >= 80) && (x <= 140) && (y >= 10) && (y <= 46)) {
          drawFrame(80, 10, 140, 46);
          currentPage = '0'; // Indicates we are at home screen
          tft.fillScreen(BLACK);
          display_3 = false;
          drawHomeScreen();
          break;
        }

        //tft.fillRoundRect(150,10,60,36,10,DKRED);
        if ((x >= 150) && (x <= 210) && (y >= 10) && (y <= 46)) {
          drawFrame(150, 10, 210, 46);
          tft.fillRect(0, 47, 320, 240, BLACK);
          carry_3 = voltout;
          zoom_3 = true;
          break;
        }

      }
    }


    if (currentPage == '7')
    {
      display_3 = true;

      tft.fillRect(0, 47, 320, 240, BLACK);
    }
  }





  if (zoom_3 == true) {

    for (double ti = 0; ti <= 60; ti++)
    {
      analogValue = analogRead(A0);
      double voltin = analogValue * (5.0) / (1023.0);

      float voltout = voltin * (R2 + R1) / R2;
      Graph(tft, ti, voltout, 40, 210, 250, 152, 0, 60, 10, carry_3 - 10, carry_3 + 10, 2.5, "", "Time(Sec)", "Voltage(V)", DKBLUE, RED, YELLOW, WHITE, BLACK, display_3);

      delay(250);

      if (myTouch.dataAvailable()) {
        myTouch.read();
        int x = 319 - myTouch.getX();
        int y = 239 - myTouch.getY();

        if ((x >= 10) && (x <= 70) && (y >= 10) && (y <= 46)) {
          drawFrame(10, 10, 70, 46);
          currentPage = '3'; // Indicates we are at home screen
          tft.fillScreen(BLACK);
          graph_9 = true;
          graph_10 = true;

          display_3 = false;
          t = 0;
          drawMainVolt(); // Draws the home screen
          break;
        }

        if ((x >= 80) && (x <= 140) && (y >= 10) && (y <= 46)) {
          drawFrame(80, 10, 140, 46);
          currentPage = '0'; // Indicates we are at home screen
          tft.fillScreen(BLACK);
          display_3 = false;
          drawHomeScreen();
          break;
        }

        //tft.fillRoundRect(150,10,60,36,10,DKRED);
        if ((x >= 150) && (x <= 210) && (y >= 10) && (y <= 46)) {
          drawFrame(150, 10, 210, 46);
          //carry_1 = temperatureFa;
          zoom_3 = false;
          break;
        }

      }
    }

    if (currentPage == '7')
    {
      display_3 = true;
      analogValue = analogRead(A0);
      double voltin = analogValue * (5.0) / (1023.0);

      float voltout = voltin * (R2 + R1) / R2;
      carry_3 = voltout;
      tft.fillRect(0, 47, 320, 240, BLACK);
    }
  }
}

void drawAllData() {
  printText("ALL DATA", 0x03E0, 100, 10, 2);
  printText("Auxiliary", RED, 20, 50, 1);
  printText("Temperature:", RED, 20, 60, 1);

  printText("Main", BLUE, 130, 50, 1);
  printText("Temperature:", BLUE, 130, 60, 1);

  printText("Main", GREEN, 240, 50, 1);
  printText("Voltage:", GREEN, 240, 60, 1);

  tft.fillRoundRect (10, 10, 60, 36, 10, WHITE);
  tft.drawRoundRect (10, 10, 60, 36, 10, GREEN);
  printText("<-", DKGREEN, 23, 17, 3);

}

void getAllData() {
  sensors1.requestTemperatures();
  Celsius1 = sensors1.getTempCByIndex(0);
  float temperature1a = Celsius1;
  float temperatureFa = sensors1.toFahrenheit(Celsius1);

  sensors2.requestTemperatures();
  Celsius2 = sensors2.getTempCByIndex(0);
  float temperature2b = Celsius2;
  float temperatureFb = sensors2.toFahrenheit(Celsius2);

  analogValue = analogRead(A0);
  voltage = analogValue * (5.0) / (1023.0);
  float voltout = voltage * (R2 + R1) / R2;

  DrawBarChartV(tft, 20, 210, 30, 110, 70, 120, 5, temperatureFa , 4 , 2, RED, DKRED, RED, WHITE, BLACK, "*F", graph_11 );
  DrawBarChartV(tft, 130, 210, 30, 110, 70, 120, 5, temperatureFb , 4 , 2, BLUE, DKBLUE, BLUE, WHITE, BLACK, "*F", graph_12 );
  DrawBarChartV(tft, 240, 210, 30, 110, 0, 60, 5, voltout , 4 , 2, GREEN, DKGREEN, GREEN, WHITE, BLACK, "Volts", graph_13 );
}

void printText(char *text, uint16_t color, int x, int y, int textSize)
{
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.setTextWrap(true);
  tft.print(text);
}

void printTxt(String text, uint16_t color, int x, int y, int textSize)
{
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.setTextWrap(true);
  tft.print(text);
}

void drawFrame(int x1, int y1, int xlen, int ylen, uint16_t color)
{
  tft.drawLine(x1, y1, x1 + xlen, y1, color);
  tft.drawLine(x1, y1, x1, y1 + ylen, color);
  tft.drawLine(x1 + xlen, y1, x1 + xlen, y1 + ylen, color);
  tft.drawLine(x1, y1 + ylen, x1 + xlen, y1 + ylen, color);
}

String Format(double val, int dec, int dig ) {
  int addpad = 0;
  char sbuf[20];
  String condata = (dtostrf(val, dec, dig, sbuf));


  int slen = condata.length();
  for ( addpad = 1; addpad <= dec + dig - slen; addpad++) {
    condata = " " + condata;
  }
  return (condata);

}

void touchScreenTest()
{
  int x, y;

  while (myTouch.dataAvailable())
  {
    myTouch.read();
    // x = 319-ts.getX();
    // y = 239-ts.getY();

    x = myTouch.getX();
    y = myTouch.getY();
    //    Serial.print("X: ");
    //    Serial.println(x);
    //    Serial.print("Y: ");
    //    Serial.println(y);
    //    Serial.println("______");
    //
    if ((x != -1) && (y != -1))
    {
      x += 13;
      y += 4;
      int radius = 4;
      tft.fillCircle(x, y, radius, ILI9341_YELLOW);
    }
  }
}

/*
-------------------------------------------------------------------------------------------------------------------------
The following functions are also from Kris Kasprzak's graphing functions from https://www.youtube.com/watch?v=U5hOU-xxQgk
-------------------------------------------------------------------------------------------------------------------------
*/

/*
  This method will draw a vertical bar graph for single input
  it has a rather large arguement list and is as follows

  &d = display object name
  x = position of bar graph (lower left of bar)
  y = position of bar (lower left of bar
  w = width of bar graph
  h =  height of bar graph (does not need to be the same as the max scale)
  loval = lower value of the scale (can be negative)
  hival = upper value of the scale
  inc = scale division between loval and hival
  curval = date to graph (must be between loval and hival)
  dig = format control to set number of digits to display (not includeing the decimal)
  dec = format control to set number of decimals to display (not includeing the decimal)
  barcolor = color of bar graph
  voidcolor = color of bar graph background
  bordercolor = color of the border of the graph
  textcolor = color of the text
  backcolor = color of the bar graph's background
  label = bottom lable text for the graph
  redraw = flag to redraw display only on first pass (to reduce flickering)

*/

void DrawBarChartV( Adafruit_ILI9341 & d, double x , double y , double w, double h , double loval , double hival , double inc , double curval ,  int dig , int dec, unsigned int barcolor, unsigned int voidcolor, unsigned int bordercolor, unsigned int textcolor, unsigned int backcolor, String label, boolean & redraw)
{

  double stepval, range;
  double my, level;
  double i, data;
  // draw the border, scale, and label once
  // avoid doing this on every update to minimize flicker
  if (redraw == true) {
    redraw = false;

    d.drawRect(x - 1, y - h - 1, w + 2, h + 2, bordercolor);
    d.setTextColor(textcolor, backcolor);
    d.setTextSize(2);
    d.setCursor(x , y + 10);
    d.println(label);
    // step val basically scales the hival and low val to the height
    // deducting a small value to eliminate round off errors
    // this val may need to be adjusted
    stepval = ( inc) * (double (h) / (double (hival - loval))) - .001;
    for (i = 0; i <= h; i += stepval) {
      my =  y - h + i;
      d.drawFastHLine(x + w + 1, my,  5, textcolor);
      // draw lables
      d.setTextSize(1);
      d.setTextColor(textcolor, backcolor);
      d.setCursor(x + w + 12, my - 3 );
      data = hival - ( i * (inc / stepval));
      d.println(Format(data, dig, dec));
    }
  }
  // compute level of bar graph that is scaled to the  height and the hi and low vals
  // this is needed to accompdate for +/- range
  level = (h * (((curval - loval) / (hival - loval))));
  // draw the bar graph
  // write a upper and lower bar to minimize flicker cause by blanking out bar and redraw on update
  d.fillRect(x, y - h, w, h - level,  voidcolor);
  d.fillRect(x, y - level, w,  level, barcolor);
  // write the current value
  d.setTextColor(textcolor, backcolor);
  d.setTextSize(2);
  d.setCursor(x , y - h - 23);
  d.println(Format(curval, dig, dec));

}

/*
  This method will draw a dial-type graph for single input
  it has a rather large arguement list and is as follows

  &d = display object name
  cx = center position of dial
  cy = center position of dial
  r = radius of the dial
  loval = lower value of the scale (can be negative)
  hival = upper value of the scale
  inc = scale division between loval and hival
  sa = sweep angle for the dials scale
  curval = date to graph (must be between loval and hival)
  dig = format control to set number of digits to display (not includeing the decimal)
  dec = format control to set number of decimals to display (not includeing the decimal)
  needlecolor = color of the needle
  dialcolor = color of the dial
  textcolor = color of all text (background is dialcolor)
  label = bottom lable text for the graph
  redraw = flag to redraw display only on first pass (to reduce flickering)
*/

void DrawDial(Adafruit_ILI9341 & d, int cx, int cy, int r, double loval , double hival , double inc, double sa, double curval,  int dig , int dec, unsigned int needlecolor, unsigned int dialcolor, unsigned int  textcolor, String label, boolean & redraw) {

  double ix, iy, ox, oy, tx, ty, lx, rx, ly, ry, i, offset, stepval, data, angle;
  double degtorad = .0174532778;
  static double px = cx, py = cy, pix = cx, piy = cy, plx = cx, ply = cy, prx = cx, pry = cy;

  // draw the dial only one time--this will minimize flicker
  if ( redraw == true) {
    redraw = false;
    d.fillCircle(cx, cy, r - 2, dialcolor);
    d.drawCircle(cx, cy, r, needlecolor);
    d.drawCircle(cx, cy, r - 1, needlecolor);
    d.setTextColor(textcolor, dialcolor);
    d.setTextSize(2);
    d.setCursor(cx - 25, cy + 80);
    d.println(label);

  }
  // draw the current value
  d.setTextSize(2);
  d.setTextColor(textcolor, dialcolor);
  d.setCursor(cx - 30, cy + 50 );
  d.println(Format(curval, dig, dec));
  // center the scale about the vertical axis--and use this to offset the needle, and scale text
  offset = (270 +  sa / 2) * degtorad;
  // find hte scale step value based on the hival low val and the scale sweep angle
  // deducting a small value to eliminate round off errors
  // this val may need to be adjusted
  stepval = ( inc) * (double (sa) / (double (hival - loval))) + .00;
  // draw the scale and numbers
  // note draw this each time to repaint where the needle was
  for (i = 0; i <= sa; i += stepval) {
    angle = ( i  * degtorad);
    angle = offset - angle ;
    ox =  (r - 2) * cos(angle) + cx;
    oy =  (r - 2) * sin(angle) + cy;
    ix =  (r - 10) * cos(angle) + cx;
    iy =  (r - 10) * sin(angle) + cy;
    tx =  (r - 30) * cos(angle) + cx;
    ty =  (r - 30) * sin(angle) + cy;
    d.drawLine(ox, oy, ix, iy, textcolor);
    d.setTextSize(1.5);
    d.setTextColor(textcolor, dialcolor);
    d.setCursor(tx - 10, ty );
    data = hival - ( i * (inc / stepval)) ;
    d.println(Format(data, dig, dec));
  }
  // compute and draw the needle
  angle = (sa * (1 - (((curval - loval) / (hival - loval)))));
  angle = angle * degtorad;
  angle = offset - angle  ;
  ix =  (r - 10) * cos(angle) + cx;
  iy =  (r - 10) * sin(angle) + cy;
  // draw a triangle for the needle (compute and store 3 vertiticies)
  lx =  5 * cos(angle - 90 * degtorad) + cx;
  ly =  5 * sin(angle - 90 * degtorad) + cy;
  rx =  5 * cos(angle + 90 * degtorad) + cx;
  ry =  5 * sin(angle + 90 * degtorad) + cy;
  // first draw the previous needle in dial color to hide it
  // note draw performance for triangle is pretty bad...

  //d.fillTriangle (pix, piy, plx, ply, prx, pry, dialcolor);
  //d.fillTriangle (pix, piy, plx, ply, prx, pry, dialcolor);

  //d.fillTriangle (pix, piy, plx, ply, prx - 20, pry - 20, dialcolor);
  //d.fillTriangle (pix, piy, prx, pry, prx + 20, pry + 20, dialcolor);

  d.fillTriangle (pix, piy, plx, ply, prx, pry, dialcolor);
  d.drawTriangle (pix, piy, plx, ply, prx, pry, dialcolor);

  // then draw the old needle in need color to display it
  d.fillTriangle (ix, iy, lx, ly, rx, ry, needlecolor);
  d.drawTriangle (ix, iy, lx, ly, rx, ry, textcolor);

  // draw a cute little dial center
  d.fillCircle(cx, cy, 8, textcolor);
  //save all current to old so the previous dial can be hidden
  pix = ix;
  piy = iy;
  plx = lx;
  ply = ly;
  prx = rx;
  pry = ry;

}

/*
  This method will draw a horizontal bar graph for single input
  it has a rather large arguement list and is as follows

  &d = display object name
  x = position of bar graph (upper left of bar)
  y = position of bar (upper left of bar (add some vale to leave room for label)
  w = width of bar graph (does not need to be the same as the max scale)
  h =  height of bar graph
  loval = lower value of the scale (can be negative)
  hival = upper value of the scale
  inc = scale division between loval and hival
  curval = date to graph (must be between loval and hival)
  dig = format control to set number of digits to display (not includeing the decimal)
  dec = format control to set number of decimals to display (not includeing the decimal)
  barcolor = color of bar graph
  voidcolor = color of bar graph background
  bordercolor = color of the border of the graph
  textcolor = color of the text
  back color = color of the bar graph's background
  label = bottom lable text for the graph
  redraw = flag to redraw display only on first pass (to reduce flickering)
*/

void DrawBarChartH(Adafruit_ILI9341 & d, double x , double y , double w, double h , double loval , double hival , double inc , double curval ,  int dig , int dec, unsigned int barcolor, unsigned int voidcolor, unsigned int bordercolor, unsigned int textcolor, unsigned int backcolor, String label, boolean & redraw)
{
  double stepval, range;
  double mx, level;
  double i, data;

  // draw the border, scale, and label once
  // avoid doing this on every update to minimize flicker
  // draw the border and scale
  if (redraw == true) {
    redraw = false;
    d.drawRect(x , y , w, h, bordercolor);
    d.setTextColor(textcolor, backcolor);
    d.setTextSize(2);
    d.setCursor(x , y - 20);
    d.println(label);
    // step val basically scales the hival and low val to the width
    stepval =  inc * (double (w) / (double (hival - loval))) - .00001;
    // draw the text
    for (i = 0; i <= w; i += stepval) {
      d.drawFastVLine(i + x , y + h + 1,  5, textcolor);
      // draw lables
      d.setTextSize(1);
      d.setTextColor(textcolor, backcolor);
      d.setCursor(i + x , y + h + 10);
      // addling a small value to eliminate round off errors
      // this val may need to be adjusted
      data =  ( i * (inc / stepval)) + loval + 0.00001;
      d.println(Format(data, dig, dec));
    }
  }
  // compute level of bar graph that is scaled to the width and the hi and low vals
  // this is needed to accompdate for +/- range capability
  // draw the bar graph
  // write a upper and lower bar to minimize flicker cause by blanking out bar and redraw on update
  level = (w * (((curval - loval) / (hival - loval))));
  d.fillRect(x + level + 1, y + 1, w - level - 2, h - 2,  voidcolor);
  d.fillRect(x + 1, y + 1 , level - 1,  h - 2, barcolor);
  // write the current value
  d.setTextColor(textcolor, backcolor);
  d.setTextSize(2);
  d.setCursor(x + w + 10 , y + 5);
  d.println(Format(curval, dig, dec));
}

/*

  function to draw a cartesian coordinate system and plot whatever data you want
  just pass x and y and the graph will be drawn

  huge arguement list
  &d name of your display object
  x = x data point
  y = y datapont
  gx = x graph location (lower left)
  gy = y graph location (lower left)
  w = width of graph
  h = height of graph
  xlo = lower bound of x axis
  xhi = upper bound of x asis
  xinc = division of x axis (distance not count)
  ylo = lower bound of y axis
  yhi = upper bound of y asis
  yinc = division of y axis (distance not count)
  title = title of graph
  xlabel = x asis label
  ylabel = y asis label
  gcolor = graph line colors
  acolor = axi ine colors
  pcolor = color of your plotted data
  tcolor = text color
  bcolor = background color
  &redraw = flag to redraw graph on fist call only
*/


void Graph(Adafruit_ILI9341 & d, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, String title, String xlabel, String ylabel, unsigned int gcolor, unsigned int acolor, unsigned int pcolor, unsigned int tcolor, unsigned int bcolor, boolean &redraw) {

  double ydiv, xdiv;
  // initialize old x and old y in order to draw the first point of the graph
  // but save the transformed value
  // note my transform funcition is the same as the map function, except the map uses long and we need doubles
  static double ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
  static double oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  double i;
  double temp;
  int rot, newrot;

  if (redraw == true) {

    redraw = false;
    ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
    oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == 0) {
        d.drawLine(gx, temp, gx + w, temp, acolor);
      }
      else {
        d.drawLine(gx, temp, gx + w, temp, gcolor);
      }

      d.setTextSize(1);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(gx - 40, temp);
      // precision is default Arduino--this could really use some format control
      d.println(i);
    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {

      // compute the transform

      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        d.drawLine(temp, gy, temp, gy - h, acolor);
      }
      else {
        d.drawLine(temp, gy, temp, gy - h, gcolor);
      }

      d.setTextSize(1);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(temp, gy + 10);
      // precision is default Arduino--this could really use some format control
      d.println(i);
    }

    //now draw the labels
    d.setTextSize(2);
    d.setTextColor(tcolor, bcolor);
    d.setCursor(gx , gy - h - 30);
    d.println(title);

    d.setTextSize(1);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx , gy + 20);
    d.println(xlabel);

    d.setTextSize(1);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx - 30, gy - h - 10);
    d.println(ylabel);


  }
  //graph drawn now plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized as static above
  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  d.drawLine(ox, oy, x, y, pcolor);
  d.drawLine(ox, oy + 1, x, y + 1, pcolor);
  d.drawLine(ox, oy - 1, x, y - 1, pcolor);
  ox = x;
  oy = y;

}
