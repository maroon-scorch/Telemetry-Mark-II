#include <Adafruit_GPS.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Wire.h>
#include  <SPI.h>
#include <Adafruit_GPS.h>

// what's the name of the hardware serial port?
#define GPSSerial Serial

// Connect
//to the GPS on the hardware port
Adafruit_GPS GPS(&GPSSerial);

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO false

uint32_t timer = millis();

//#define TFT_DC 23
//#define TFT_CS 24
//#define TFT_RST 22
//#define TFT_MISO 26
//#define TFT_MOSI 25
//#define TFT_CLK 28

#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8
#define TFT_MISO 12
#define TFT_MOSI 11
#define TFT_CLK 13

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

boolean graph_1 = true;
float sped;
uint8_t secon;

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

void setup()
{
  //while (!Serial);  // uncomment to have the sketch wait until Serial is ready

  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out

      pinMode(LED_BUILTIN, OUTPUT);
      

      
  Serial.begin(115200);
  Serial.println("Adafruit GPS library basic test!");

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  delay(1000);

  // Ask for firmware version
  GPSSerial.println(PMTK_Q_RELEASE);

  
  tft.begin(9600);
  //tft.setRotation(0);
        tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0,0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(2);
}

void loop() // run over and over again
{
   //tft.fillScreen(ILI9341_BLACK);
  // read data from the GPS in the 'main loop'
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  if (GPSECHO)
    if (c) Serial.print(c);
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    Serial.println(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return; // we can fail to parse a sentence in which case we should just wait for another
  }
//
// if (timer > millis()) timer = millis();
//
//  // approximately every 2 seconds or so, print out the current stats
//  if (millis() - timer > 1000) {
//  sped = GPS.speed;
//  tft.print(sped);
//  }
//  
//   DrawDial(tft, 220, 135, 100, 0, 60, 5, 250, sped,  4 , 2, WHITE, GREEN, WHITE, "Speed", graph_1);

 gpsParsing();

 //gpsTest();
}

void gpsTest(){
 if (timer > millis()) timer = millis();
  if (millis() - timer > 500) {
    tft.setCursor(0,0);
 secon = GPS.seconds;
    tft.print(secon);
    delay(1000);
    tft.fillScreen(BLACK);
  }
}
void gpsParsing()
{
  if (timer > millis()) timer = millis();

  if (millis() - timer > 2600) {

    
    timer = millis(); // reset the timer
    //Serial.print("\nTime");
    //tft.print("\nTime: ");

    uint8_t hr = GPS.hour;
    
    if (GPS.hour < 10) { 
      //tft.print('0'); 
      }
    //tft.print(hr, DEC); tft.print(':');

    uint8_t mi = GPS.minute;
        
    if (GPS.minute < 10) { 
      //tft.print('0'); 
      }
    //tft.print(GPS.minute, DEC); tft.print(':');

    uint8_t sec = GPS.seconds;
    
    if (GPS.seconds < 10) { 
      //tft.print('0'); 
      }
    //tft.print(GPS.seconds, DEC); tft.print('.');
    if (GPS.milliseconds < 10) {
      //tft.print("00");
    } else if (GPS.milliseconds > 9 && GPS.milliseconds < 100) {
      //tft.print("0");
    }
    
    if (GPS.hour < 10) { Serial.print('0'); }
    Serial.print(hr, DEC); Serial.print(':');


    float seconds = 1.15078*GPS.speed;
    DrawDial(tft, 160, 120, 120, 0, 60, 5,250, seconds,  4 , 2, RED, WHITE, BLACK, "SPEED", graph_1);
    //graph_1 = true;

  }

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

/*
-------------------------------------------------------------------------------------------------------------------------
The following functions are also from Kris Kasprzak's graphing functions from https://www.youtube.com/watch?v=U5hOU-xxQgk
-------------------------------------------------------------------------------------------------------------------------
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
