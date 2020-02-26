/*
    Central Heating radiator efficiency monitor
*/

#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Ucglib.h"

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2 // on WeMos D1 mini the D4 port is identified as GPIO2
#define TEMPERATURE_PRECISION 9

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
DeviceAddress inPipeThermIDX, outPipeThermIDX;

/////////////////////////////////////////////
// UCG initialisation
//Ucglib8BitPortD ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, /* wr= */ 18 , /* cd= */ 19 , /* cs= */ 17, /* reset= */ 16 );
//Ucglib8Bit ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, 0, 1, 2, 3, 4, 5, 6, 7, /* wr= */ 18 , /* cd= */ 19 , /* cs= */ 17, /* reset= */ 16 );

//Ucglib4WireSWSPI ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, /*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);  // not working
//Ucglib4WireSWSPI ucg(ucg_dev_ili9325_spi_18x240x320, ucg_ext_ili9325_spi_18, /*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8); // not working
//Ucglib3WireILI9325SWSPI ucg(ucg_dev_ili9325_spi_18x240x320, ucg_ext_ili9325_spi_18, /*sclk=*/ 13, /*data=*/ 11, /*cs=*/ 10, /*reset=*/ 8);  // not working
//Ucglib3WireILI9325SWSPI ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, /*sclk=*/ 13, /*data=*/ 11, /*cs=*/ 10, /*reset=*/ 8); // not working

//Ucglib_ST7735_18x128x160_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_ST7735_18x128x160_HWSPI ucg(/*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);

//Ucglib_ILI9163_18x128x128_SWSPI ucg(/*sclk=*/ 7, /*data=*/ 6, /*cd=*/ 5, /*cs=*/ 3, /*reset=*/ 4);
//Ucglib_ILI9163_18x128x128_HWSPI ucg(/*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8); /* HW SPI Adapter */

//Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 7, /*data=*/ 6, /*cd=*/ 5, /*cs=*/ 3, /*reset=*/ 4);
//Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);
Ucglib_ILI9341_18x240x320_HWSPI ucg(/*cd=*/ 4, /*cs=*/ 15 /*reset= 8 */);
//Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 4, /*data=*/ 3, /*cd=*/ 6, /*cs=*/ 7, /*reset=*/ 5);  /* Elec Freaks Shield */

//Ucglib_HX8352C_18x240x400_SWSPI ucg(/*sclk=*/ 7, /*data=*/ 6, /*cd=*/ 5, /*cs=*/ 3, /*reset=*/ 4);
//Ucglib_HX8352C_18x240x400_HWSPI ucg(/*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);

//Ucglib_ILI9486_18x320x480_SWSPI ucg(/*sclk=*/ 7, /*data=*/ 6, /*cd=*/ 5, /*cs=*/ 3, /*reset=*/ 4);
//Ucglib_ILI9486_18x320x480_HWSPI ucg(/*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);

//Ucglib_SSD1351_18x128x128_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_SSD1351_18x128x128_HWSPI ucg(/*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_SSD1351_18x128x128_FT_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_SSD1351_18x128x128_FT_HWSPI ucg(/*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_SSD1351_18x128x128_FT_SWSPI ucg(/*sclk=*/ 4, /*data=*/ 17, /*cd=*/ 16, /*cs=*/ 0, /*reset=*/ 2);   /* FT SSD1351 direct connect to ESP32 */

//Ucglib_PCF8833_16x132x132_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cs=*/ 9, /*reset=*/ 8); /* linksprite board */
//Ucglib_PCF8833_16x132x132_HWSPI ucg(/*cs=*/ 9, /*reset=*/ 8); /* linksprite board */

//Ucglib_LD50T6160_18x160x128_6Bit ucg( /*d0 =*/ d0, /*d1 =*/ d1, /*d2 =*/ d2, /*d3 =*/ d3, /*d4 =*/ d4, /*d5 =*/ d5, /*wr=*/ wr, /*cd=*/ cd, /*cs=*/ cs, /*reset=*/ reset);
//Ucglib_LD50T6160_18x160x128_6Bit ucg( /*d0 =*/ 16, /*d1 =*/ 17, /*d2 =*/ 18, /*d3 =*/ 19, /*d4 =*/ 20, /*d5 =*/ 21, /*wr=*/ 14, /*cd=*/ 15); /* Samsung 160x128 OLED with 6Bit minimal interface with Due */
//Ucglib_LD50T6160_18x160x128_6Bit ucg( /*d0 =*/ 5, /*d1 =*/ 4, /*d2 =*/ 3, /*d3 =*/ 2, /*d4 =*/ 1, /*d5 =*/ 0, /*wr=*/ 7, /*cd=*/ 6); /* Samsung 160x128 OLED with 6Bit minimal interface with Uno */

//Ucglib_SSD1331_18x96x64_UNIVISION_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_SSD1331_18x96x64_UNIVISION_HWSPI ucg(/*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);

//Ucglib_SEPS225_16x128x128_UNIVISION_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_SEPS225_16x128x128_UNIVISION_HWSPI ucg(/*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);


// relative X and Y coordinates of the tetragons of 12 segments, based on a inner radius of 30 and outer radius of 50
// the coordinates are for TopLeft, TopRight, BottomRight and BottomLeft and drawn clockwise, starting at 3 oçlock
#define VISIBLESECTORS 13 //this gauge shows just 13 sectors, sector 14 = warning, 15 is increase/decrease indicator, 16 is unused
#define MAXSECTORS 16 //total number of sectors, 4 per quarter circle
#define INDICATORSECTIDX 14 // this is the array index, starting 0
#define WARNINGSECTIDX 13 // this is a array index, starting at 0
#define INDICATORCOLORIDX 7 // use the same intensity of the matching indicator color for every gauge, so: the 8th color in the array
#define AVGDOTCENTERCOLORIDX 11 // use the same intensity of the matching indicator color for every gauge, so: the 12th color in the array
#define AVGDOTRINGCOLORIDX 7 // use the same intensity of the matching indicator color for every gauge, so: the 8th color in the array

const PROGMEM short xTL[] = { 30, 28, 21, 11, 0, -11, -21, -28, -30, -28, -21, -11, 0, 11, 21, 28}; //x1 TopLeft
const PROGMEM short yTL[] = { 0, 11, 21, 28, 30, 28, 21, 11, 0, -11, -21, -28, -30, -28, -21, -11}; //y1 TopLeft
const PROGMEM short xTR[] = { 50, 46, 35, 19, 0, -19, -35, -46, -50, -46, -35, -19, 0, 19, 35, 46}; //x2 TopRight
const PROGMEM short yTR[] = { 0, 19, 35, 46, 50, 46, 35, 19, 0, -19, -35, -46, -50, -46, -35, -19}; //y2 TopRight
const PROGMEM short xBR[] = { 47, 37, 21, 2, -17, -34, -45, -50, -47, -37, -21, -2, 17, 34, 45, 50};//x3 Bottom Right
const PROGMEM short yBR[] = { 17, 34, 45, 50, 47, 37, 21, 2, -17, -34, -45, -50, -47, -37, -21, -2};//y3 Bottom Right
const PROGMEM short xBL[] = { 28, 22, 13, 1, -10, -20, -27, -30, -28, -22, -13, -1, 10, 20, 27, 30};//x4 BottomLeft
const PROGMEM short yBL[] = { 10, 20, 27, 30, 28, 22, 13, 1, -10, -20, -27, -30, -28, -22, -13, -1};//y4 Bottom Left

const PROGMEM short c_innerRad = 28; //inner radius of the gauge plus margin
const PROGMEM short c_outerRad = 52; //outer radius of the gauge plus margin

//colorrange = 75%, 70%, 65%, 60%, 55%, 50%, 45%, 40%, 35%, 30%, 25%, 20%, 15%
const PROGMEM unsigned long c_sectorColorReds[] = {0xff8080, 0xff6666, 0xff4d4d, 0xff3333, 0xff1a1a, 0xff0000, 0xe60000, 0xcc0000, 0xb30000, 0x990000, 0x800000, 0x660000, 0x4d0000};
const PROGMEM unsigned long c_sectorColorBlues[] = {0x8080ff, 0x6666ff, 0x4d4dff, 0x3333ff, 0x1a1aff, 0x0000ff, 0xe000090, 0x0000cc, 0x0000b3, 0x000099, 0x000080, 0x000066, 0x00004d};
const PROGMEM unsigned long c_sectorColorGreens[] = {0x80ff80, 0x66ff66, 0x4dff4d, 0x33ff33, 0x1aff1a, 0x00ff00, 0xe009000, 0x00cc00, 0x00b300, 0x009900, 0x008000, 0x006600, 0x004d00};

const long c_sectorBaseColor = 0x2d112d;  //dark but visible color to use for inactive segments
const long c_warningSignColor = 0xff9900; //orange
const long c_errorSignColor = 0xff0000; // red

/*
 * block of user messages and error messages
 */

const char* g_MSGTBL[] PROGMEM = {
                                /* 0 */ " ",
                                /* 1 */ "ERR: setup error or sensor error",
                                /* 2 */ "ERR: Sensor (IN) not found",
                                /* 3 */ "ERR: Sensor (OUT) not found",
                                /* 4 */ "...waiting until T-in is hotter than T-out",
                                /* 5 */ "ERR: sensor 1 (in) < 0 gr",
                                /* 6 */ "ERR: sensor 2 (out) < 0 gr",
                                /* 7 */ "WARN: T-in much cooler than T-out",
                                /* 8 */ "INFO: CV paused, radiator is cooling (OK)",
                                /* 9 */ "INFO: heating increases rapidly (OK)",
                                /*10 */ "INFO: efficiency is GOOD (70%-85%)",
                                /*11 */ "INFO: efficiency is LOW (>85%)",
                                /*12 */ "WARN: no heat flow!  T-in = T-out",
                                /*13 */ "Radiator cockpit v2.0 wybelution@gmail.com 2020",
                                /*14 */ "overflow message array error..."
}; //end of declaration of user messages

#define BLACK 0
#define WHITE 255
#define TRUE 1
#define FALSE 0
#define WARNINGSTATE 1
#define ERRORSTATE 2

#define GAUGE1 0
#define GAUGE2 1
#define GAUGE3 2

#define SHOW_ALL  1 //refers to the details in the gauges and graphs
#define SHOW_TEMP 2

#define MESSAGEBOXYPOS 126 //starting y-coordinate of notification area

#define SAMPLESPEED 15 //delay in seconds between 2 measurements and display updates

//global variables
struct s_gauge {  //structure that holds all the data for a graph gauge
  word cntrX, cntrY;  //center coordinates for the gauge
  byte currValue, prevValue; //stores current value, previous value and the value 10 measurements ago
  unsigned long measurements; //number of measurements
  long sum; //the total sum of all measurements
  byte absLow, absHigh; //lowest and highest value so far
  short avgW; //weighted average counts every measurement: sum/measurements;
  char unitchar; //the character for the unit (e.g. %, degrees, etc);
  char title[12];  //the name of the gauge
//  boolean sectorActive[VISIBLESECTORS];  //indicator for every segment if it is within measured range, UNUSED?
  byte valueSect, avgSect; //remember the sector containing value mark and average mark
  byte gaugeMin, gaugeMax;  //set the absolute value range for the gauge
  byte belowOpt, aboveOpt;  //lower and upper threshold of the Optimum (temperature/efficiency) range of the gauge
  unsigned long *colorArray; //pointer to the chosen color array for this gauge;
  byte errStat; //0=ok, 1=warning, 2=error
};
struct s_gauge g_gauge[3]; //define 3 structure instances

struct s_graph { //structure that holds the data for a graph
  word posX, posY; //display position of the origin of the graph
  word sizeX, sizeY; //display size of the graph
  word value; // actual IRL value of the measurement
  word rangeX, rangeY; //value range of X and Y axis
};
struct s_graph g_graph;

byte g_R, g_G, g_B; // used to handover RGB values based on hex colors
boolean g_errorState = FALSE; //global errorstate


//////////////////////////////////////////////////////////////////////////////////////////////////////

void setRGBcolors( long hexColor) {
  /*
        transpose a hex color value into indivudual R, G, B values.
        the global R,G,B values are set.
  */
  g_R = hexColor >> 16;
  g_G = (hexColor & 0x00ff00) >> 8;
  g_B = (hexColor & 0x0000ff);
} //end of setRGBcolors()


void initialiseGauges() {
  /* initialise alle gauges and prepare for showing actual data

  */
  word cX = 0, cY = 0;

  Serial.println (F("initialiseGauges()..."));

  // init GAUGE 1: incoming pipe for radiator, temp 0-99
  g_gauge[GAUGE1].unitchar = char(176); // char(176) is a degree sign
  g_gauge[GAUGE1].gaugeMin = 0; // min is 0 degrees
  g_gauge[GAUGE1].gaugeMax = 99; //max is 99 degrees
  g_gauge[GAUGE1].belowOpt = 40;
  g_gauge[GAUGE1].aboveOpt = 60;
  strcpy(g_gauge[GAUGE1].title, "aanvoer");
  g_gauge[GAUGE1].colorArray = (unsigned long *)c_sectorColorReds; //use green sector colors for this gauge
  g_gauge[GAUGE1].cntrX = 55;
  g_gauge[GAUGE1].cntrY = 70;

  // init GAUGE 2: outgoing pipe from radiator, temp 0-99
  g_gauge[GAUGE2].unitchar = char(176); // char(176) is a degree sign
  g_gauge[GAUGE2].gaugeMin = 0; // min is 0 degrees
  g_gauge[GAUGE2].gaugeMax = 99; //max is 99 degrees
  g_gauge[GAUGE2].belowOpt = 32; //optimum incoming watertemp = 30-48 (but never > 55)
  g_gauge[GAUGE2].aboveOpt = 48; 
  strcpy(g_gauge[GAUGE2].title, "afvoer");
  g_gauge[GAUGE2].colorArray = (unsigned long *)c_sectorColorBlues; //use green sector colors for this gauge
  g_gauge[GAUGE2].cntrX = 55 + 107;
  g_gauge[GAUGE2].cntrY = 70 + 0;

  // init GAUGE 3: efficience of the radiator, 0-100%
  g_gauge[GAUGE3].unitchar = '%'; // use single quotes, because the character is needed, not the string
  g_gauge[GAUGE3].gaugeMin = 0; // min is 0 procent
  g_gauge[GAUGE3].gaugeMax = 100; //max is 100 procent
  g_gauge[GAUGE3].belowOpt = 70; //optimum efficiency watertemp = 30-40
  g_gauge[GAUGE3].aboveOpt = 85; 
  strcpy(g_gauge[GAUGE3].title, "rendement");
  g_gauge[GAUGE3].colorArray = (unsigned long *)c_sectorColorGreens; //use green sector colors for this gauge
  g_gauge[GAUGE3].cntrX = 55 + 107 + 107;
  g_gauge[GAUGE3].cntrY = 70 + 0;

  // anim: draw all visible sectors in base color, clockwise
  setRGBcolors (c_sectorBaseColor);
  ucg.setColor (g_R, g_G, g_B);
  for (int i = 0; i < VISIBLESECTORS; i++) {
    cX = g_gauge[GAUGE1].cntrX;
    cY = g_gauge[GAUGE1].cntrY;
    ucg.drawTetragon (xTL[i] + cX, yTL[i] + cY, xTR[i] + cX, yTR[i] + cY, xBR[i] + cX, yBR[i] + cY, xBL[i] + cX, yBL[i] + cY);
    cX = g_gauge[GAUGE2].cntrX;
    cY = g_gauge[GAUGE2].cntrY;
    ucg.drawTetragon (xTL[i] + cX, yTL[i] + cY, xTR[i] + cX, yTR[i] + cY, xBR[i] + cX, yBR[i] + cY, xBL[i] + cX, yBL[i] + cY);
    cX = g_gauge[GAUGE3].cntrX;
    cY = g_gauge[GAUGE3].cntrY;
    ucg.drawTetragon (xTL[i] + cX, yTL[i] + cY, xTR[i] + cX, yTR[i] + cY, xBR[i] + cX, yBR[i] + cY, xBL[i] + cX, yBL[i] + cY);
    delay(30);
  }
  delay(250);

  // anim: draw all visible (real gauge value) sectors in the target colors
  for (int i = 0; i < VISIBLESECTORS; i++) {
    setRGBcolors ( *(g_gauge[GAUGE1].colorArray + i) );  //tricky... use the pointer to the right color array and add the right number of addresses to reach the correct item
    ucg.setColor (g_R, g_G, g_B);
    cX = g_gauge[GAUGE1].cntrX;
    cY = g_gauge[GAUGE1].cntrY;
    ucg.drawTetragon (xTL[i] + cX, yTL[i] + cY, xTR[i] + cX, yTR[i] + cY, xBR[i] + cX, yBR[i] + cY, xBL[i] + cX, yBL[i] + cY);
    setRGBcolors ( *(g_gauge[GAUGE2].colorArray + i) );  //tricky... use the pointer to the right color array and add the right number of addresses to reach the correct item
    ucg.setColor (g_R, g_G, g_B);
    cX = g_gauge[GAUGE2].cntrX;
    cY = g_gauge[GAUGE2].cntrY;
    ucg.drawTetragon (xTL[i] + cX, yTL[i] + cY, xTR[i] + cX, yTR[i] + cY, xBR[i] + cX, yBR[i] + cY, xBL[i] + cX, yBL[i] + cY);
    setRGBcolors ( *(g_gauge[GAUGE3].colorArray + i) );  //tricky... use the pointer to the right color array and add the right number of addresses to reach the correct item
    ucg.setColor (g_R, g_G, g_B);
    cX = g_gauge[GAUGE3].cntrX;
    cY = g_gauge[GAUGE3].cntrY;
    ucg.drawTetragon (xTL[i] + cX, yTL[i] + cY, xTR[i] + cX, yTR[i] + cY, xBR[i] + cX, yBR[i] + cY, xBL[i] + cX, yBL[i] + cY);
    delay (30);
  }
  delay(500);

  Serial.println (F("end of initialiseGauges()..."));
} //end of initialiseGauges()

void initialiseGraphs() {
  /* initialise alle gauges and prepare for showing actual data

  */
  Serial.println (F("initialiseGraphs()..."));
  g_graph.posX = 5; //display coordinate
  g_graph.posY = 235; //display coordinate
  g_graph.sizeX = 315;
  g_graph.sizeY = 85;
  g_graph.rangeY = 100; //0-100 degrees

  // background of graph
  ucg.setColor(0, 100, 0, 0);
  ucg.setColor(1, 100, 0, 0);
  ucg.setColor(2, 0, 0, 100);
  ucg.setColor(3, 0, 0, 100);
  ucg.drawGradientBox( 0, g_graph.posY - g_graph.sizeY, g_graph.sizeX + g_graph.posX, g_graph.sizeY);

  //background of Y-axis
  ucg.setColor(0, 255, 0, 0);
  ucg.setColor(1, 255, 0, 0);
  ucg.setColor(2, 0, 0, 255);
  ucg.setColor(3, 0, 0, 255);
  ucg.drawGradientBox( 0, g_graph.posY - g_graph.sizeY, g_graph.posX, g_graph.sizeY);

  //X-axis and Y-axis
  ucg.setColor(WHITE, WHITE, WHITE);
  ucg.drawHLine( g_graph.posX, g_graph.posY, g_graph.sizeX);
  ucg.drawVLine( g_graph.posX, g_graph.posY - g_graph.sizeY, g_graph.sizeY);

  Serial.println (F("end of initialiseGauges()..."));
} // end of initialiseGraphs()

void updateMsgBox (byte msgIdx) { //show messages and notifications
/*
 * show messages and notifications in a box
 */
  static byte prevMsgIdx = 0;

  if ( msgIdx != prevMsgIdx ){
    ucg.setColor(255, 0, 0); //red!
    ucg.drawRFrame (0, MESSAGEBOXYPOS, 319, 20, 3);
    ucg.setColor(BLACK, BLACK, BLACK);
    ucg.drawBox (0+1, MESSAGEBOXYPOS+1, 319-2, 20-2); 
    ucg.setFontPosTop();
    ucg.setFont (ucg_font_helvR10_tf); // set small font
    ucg.setColor(255, 77, 77); //light red
    ucg.setPrintPos ( 5, MESSAGEBOXYPOS+3);
    Serial.print ("MSG = "); Serial.println (msgIdx);
    Serial.println ( g_MSGTBL[msgIdx] );
    ucg.print ( g_MSGTBL[msgIdx] );
    prevMsgIdx = msgIdx;
  }
} // end of updateMsgBox()

void updateGraphs () {
/*  
 *   draw the currValues of all three gauges in a continuous motion
 */

 word Xpos, Xoffset, Ypos1=0, Ypos2=0, Ypos3=0;
 const word cleanWindow = 8;
 
 ucg.setFont (ucg_font_6x12_67_75);
 ucg.setFontPosCenter();
 ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);

 Xoffset = ( g_gauge[GAUGE1].measurements % (g_graph.sizeX - cleanWindow) );
 Xpos = g_graph.posX + 2 + Xoffset;
 Ypos1 = g_graph.posY - map(g_gauge[GAUGE1].currValue, g_gauge[GAUGE1].gaugeMin, g_gauge[GAUGE1].gaugeMax -1, 1, g_graph.sizeY);
 Ypos2 = g_graph.posY - map(g_gauge[GAUGE2].currValue, g_gauge[GAUGE2].gaugeMin, g_gauge[GAUGE2].gaugeMax -1, 1, g_graph.sizeY);
 Ypos3 = g_graph.posY - map(g_gauge[GAUGE3].currValue, g_gauge[GAUGE3].gaugeMin, g_gauge[GAUGE3].gaugeMax -1, 1, g_graph.sizeY);

  //clean the graph
  ucg.setColor(0, 100, 0, 0);
  ucg.setColor(1, 100, 0, 0);
  ucg.setColor(2, 0, 0, 100);
  ucg.setColor(3, 0, 0, 100);
  if ( Xoffset == 0 ) {
    ucg.drawGradientBox( Xpos, g_graph.posY - g_graph.sizeY, cleanWindow, g_graph.sizeY - 1); // also clean the leftover pixels leftside of the old glyphs
  }
  else {
    ucg.drawGradientBox( Xpos + 3, g_graph.posY - g_graph.sizeY, cleanWindow, g_graph.sizeY - 1);  
  }
   
 ucg.setColor (255,0,0);
 ucg.drawGlyph( Xpos, Ypos1, 0, 198);
 ucg.setColor (0,0,255);
 ucg.drawGlyph( Xpos, Ypos2, 0, 198);
 ucg.setColor (0,255,0);
 ucg.drawGlyph( Xpos, Ypos3, 0, 198);
 
} //end of updateGraphs()

void updateGauge ( byte gaugeIdx, byte mode) {
  /*
     update the visual gauge parameters
  */
  word cX = g_gauge[gaugeIdx].cntrX;
  word cY = g_gauge[gaugeIdx].cntrY;
  char valueStr[6];
  word sX, sY;
  byte newValueSect, prevValuesect, newAvgSect, prevAvgSect;
  float sectorRange = (float(g_gauge[gaugeIdx].gaugeMax) / float(VISIBLESECTORS));  //sectorRange is the number of unity values within 1 sector (e.g. 5 degrees)

  // TODO avoid flicker: don't update currValue and range if the value didn't change

  Serial.print (F("updateGauges()...gauge = ")); Serial.println (gaugeIdx);
  Serial.print (F("currValue = ")); Serial.println(g_gauge[gaugeIdx].currValue);
  
  if (mode == SHOW_ALL) {
    //remove old value mark and average mark in reverse order of previous loop
    ucg.setColor(0, BLACK, BLACK, BLACK); //foreground color
    ucg.setColor(1, BLACK, BLACK, BLACK); //background color
    ucg.setFont (ucg_font_cursor_tf);
    ucg.setFontPosCenter();
    ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
    newValueSect = byte( ceil(( float(g_gauge[gaugeIdx].currValue) / sectorRange)) ) - 1; //calculate the index of the sector where the weighted average is part of.
    prevValuesect = g_gauge[gaugeIdx].valueSect;
    Serial.print (F("newValueSect = ")); Serial.println(newValueSect);
    if ( newValueSect != prevValuesect ) {
      //new position for value mark, so erase the old position
      sX = cX + xTR[prevValuesect] + ( round( ( xBR[prevValuesect] - xTR[prevValuesect] ) / 2 )) ; //xBR is X3, xTR is X2
      sY = cY + yTR[prevValuesect] + ( round( ( yBR[prevValuesect] - yTR[prevValuesect] ) / 2 )) ; //yBR is Y3, xTR is Y2
      ucg.drawGlyph (sX, sY, 0, 68); // glyph 62 is a crosshair
    }
    // and remove old avg mark
    newAvgSect = byte( ceil (( float(g_gauge[gaugeIdx].avgW) / sectorRange)) ) - 1; //calculate the index of the sector where the weighted average is part of.
    prevAvgSect = g_gauge[gaugeIdx].avgSect;
    if ( newAvgSect != prevAvgSect ) {
      sX = cX + xTR[prevAvgSect] + ( round( ( xBR[prevAvgSect] - xTR[prevAvgSect] ) / 2 )) ; //xBR is X3, xTR is X2
      sY = cY + yTR[prevAvgSect] + ( round( ( yBR[prevAvgSect] - yTR[prevAvgSect] ) / 2 )) ; //yBR is Y3, xTR is Y2
      ucg.drawGlyph (sX, sY, 0, 70); // glyph is a small dot
      ucg.drawGlyph (sX, sY, 0, 71); // glyph is a big dot
    }

    Serial.println (F("updateGauges()...old marks removed"));
    
    // draw the sectors of the gauge, set the visibility of each sector for future reference
    for (int i = 0; i < VISIBLESECTORS; i++) {
      // sector is INactive if it is not in the absLow - absHigh range
      if ( ((float(i + 1) * sectorRange) < float(g_gauge[gaugeIdx].absLow) ) || ((float(i) * sectorRange) > float(g_gauge[gaugeIdx].absHigh)) ) {
//        g_gauge[gaugeIdx].sectorActive[i] = FALSE ; // mark the sector inactive ?not used anymore?
        setRGBcolors (c_sectorBaseColor);
        ucg.setColor (g_R, g_G, g_B);
        ucg.drawTetragon (xTL[i] + cX, yTL[i] + cY, xTR[i] + cX, yTR[i] + cY, xBR[i] + cX, yBR[i] + cY, xBL[i] + cX, yBL[i] + cY);
      }
      else {
//        g_gauge[gaugeIdx].sectorActive[i] = TRUE; //mark the sector active  ?not used anymore?
        setRGBcolors ( *(g_gauge[gaugeIdx].colorArray + i) );  //tricky... use the pointer to the right color array and add the right number of addresses to reach the correct item
        ucg.setColor (g_R, g_G, g_B);
        ucg.drawTetragon (xTL[i] + cX, yTL[i] + cY, xTR[i] + cX, yTR[i] + cY, xBR[i] + cX, yBR[i] + cY, xBL[i] + cX, yBL[i] + cY);
      }
//      delay(25);
    } //end for

    Serial.println (F("updateGauges()...sectors redrawn"));
    
    //set the new current sectors of the marks in the data structure
    g_gauge[gaugeIdx].valueSect = newValueSect;
    g_gauge[gaugeIdx].avgSect = newAvgSect;

  } //end if SHOW_ALL

  // display main value, including unit sign and including a warning backgroundcolor is necessary
  if (mode == SHOW_TEMP || mode == SHOW_ALL ) {
    // main value: clear the text area in the gauge center, top half
    ucg.setColor(0, BLACK, BLACK, BLACK);
    if ( g_gauge[gaugeIdx].currValue > g_gauge[gaugeIdx].aboveOpt ) ucg.setColor(0, 160, BLACK, BLACK); // red
    if ( g_gauge[gaugeIdx].currValue < g_gauge[gaugeIdx].belowOpt ) ucg.setColor(0, BLACK, BLACK, 127); // blue
    ucg.drawDisc(cX, cY, c_innerRad, UCG_DRAW_UPPER_RIGHT);
    ucg.drawDisc(cX, cY, c_innerRad, UCG_DRAW_UPPER_LEFT);

    // print the main value in the center of the gauge
    if (g_gauge[gaugeIdx].errStat == ERRORSTATE) {
      ucg.setColor(0, 127, 127, 127); //make current value grey
    }
    else {
      ucg.setColor(0, WHITE, WHITE, WHITE);
    }
    ucg.setFont (ucg_font_inb16_tf);  // set large font
    ucg.setFontPosBaseline();
    sprintf(valueStr, "%d", g_gauge[gaugeIdx].currValue); //only meant to measure the width of the value without degree sign
    ucg.setPrintPos ( cX - (ucg.getStrWidth(valueStr) / 2), cY ); // set the text position to the center of the value, without degree sign
    sprintf(valueStr, "%d%c", g_gauge[gaugeIdx].currValue, g_gauge[gaugeIdx].unitchar); //add the unit sign to the value string
    ucg.print(valueStr);
  } //end if SHOW_TEMP || SHOW_ALL

    Serial.println (F("updateGauges()...current value shown"));

  // display the from-to range values
  if ( mode == SHOW_ALL ) {
    // prepare range value display area: clear the text area in the gauge center, bottom half
    ucg.setColor(0, BLACK, BLACK, BLACK);
    ucg.drawDisc(cX, cY, c_innerRad, UCG_DRAW_LOWER_RIGHT);
    ucg.drawDisc(cX, cY, c_innerRad, UCG_DRAW_LOWER_LEFT);

    // show range values, create a XX-YY string and print below main value
    ucg.setColor(0, WHITE, WHITE, WHITE);
    ucg.setFont (ucg_font_helvR10_tf); // set small font
    ucg.setFontPosTop(); //draw the text below the top-left coordinates of the position
    sprintf(valueStr, "%d %c %d", g_gauge[gaugeIdx].absLow, char(183), g_gauge[gaugeIdx].absHigh); //construct range string, char 183 is a middot
    ucg.setPrintPos ( cX - (ucg.getStrWidth(valueStr) / 2), cY + 5 ); // set the text position to the center of the value
    ucg.print(valueStr);

    // show the weighted average as a marking on a sector
    // show a donut glyph on the outer radius of the range of the weighted average sector
    // calculate the X and Y coordinate of the weighted average as follows: X2 + (X3-X2)/2
    ucg.setFont (ucg_font_cursor_tf);
    ucg.setFontPosCenter();
    //  newAvgSect = byte( g_gauge[gaugeIdx].avgW / sectorRange); //calculate the index of the sector where the weighted average is part of.
    sX = cX + xTR[newAvgSect] + ( round( ( xBR[newAvgSect] - xTR[newAvgSect] ) / 2 )) ; //xBR is X3, xTR is X2
    sY = cY + yTR[newAvgSect] + ( round( ( yBR[newAvgSect] - yTR[newAvgSect] ) / 2 )) ; //yBR is Y3, xTR is Y2
    //  setRGBcolors ( *(g_gauge[gaugeIdx].colorArray + AVGDOTRINGCOLORIDX ) );  //tricky... use the pointer to the right color array and add the right number of addresses to reach the correct item
    //  ucg.setColor (g_R, g_G, g_B);
    ucg.setColor(0, WHITE, WHITE, WHITE);
    ucg.drawGlyph (sX, sY, 0, 71); // glyph is a big dot
    setRGBcolors ( *(g_gauge[gaugeIdx].colorArray + AVGDOTCENTERCOLORIDX ) );  //tricky... use the pointer to the right color array and add the right number of addresses to reach the correct item
    ucg.setColor (g_R, g_G, g_B);
    ucg.drawGlyph (sX, sY, 0, 70); // glyph is a small dot

    Serial.println (F("updateGauges()...range values shown"));

    // show the current value as a marking on a sector
    // show a crosshair glyph in the center of the range of the weighted average sector
    // calculate the X and Y coordinate of the weighted average as follows: X1 + (X3-X1)/2
    ucg.setColor(0, WHITE, WHITE, WHITE);
    ucg.setFont (ucg_font_cursor_tf); //ucg_font_10x20_67_75
    ucg.setFontPosCenter();
    //  newValueSect = byte( g_gauge[gaugeIdx].currValue / sectorRange); //calcultae the index of the sector where the weighted average is part of.
    sX = cX + xTR[newValueSect] + ( round( ( xBR[newValueSect] - xTR[newValueSect] ) / 2 )) ; //xBR is X3, xTR is X2
    sY = cY + yTR[newValueSect] + ( round( ( yBR[newValueSect] - yTR[newValueSect] ) / 2 )) ; //yBR is Y3, xTR is Y2
    ucg.drawGlyph (sX, sY, 0, 68); // glyph 62 is a crosshair

    Serial.println (F("updateGauges()...value marker shown"));

    // show an increase / decrease indicator
    // position indicator in the indicator sector
    ucg.setColor(0, BLACK, BLACK, BLACK); // set background color
    ucg.setColor(1, BLACK, BLACK, BLACK); // set background color
    ucg.setFont (ucg_font_10x20_67_75);
    ucg.setFontMode(UCG_FONT_MODE_SOLID); //erase the old mark by clearing the background with black
    ucg.setFontPosTop();
    sX = cX + xTR[INDICATORSECTIDX];
    sY = cY + yTR[INDICATORSECTIDX];
    short diff = ( g_gauge[gaugeIdx].currValue - g_gauge[gaugeIdx].prevValue );
    ucg.drawGlyph (sX, sY, 0, 136); //clear glyph area with a solid character
    setRGBcolors ( *(g_gauge[gaugeIdx].colorArray + INDICATORCOLORIDX ) );  //tricky... use the pointer to the right color array and add the right number of addresses to reach the correct item
    ucg.setColor (g_R, g_G, g_B);
    if ( diff > 4 ) { // arbitrary condition, 4 seems to count as a big change
      ucg.drawGlyph (sX, sY, 0, 17); // arrow up
    }
    else if ( diff > 1 ) {
      ucg.drawGlyph (sX, sY, 0, 23); //arrow 45deg up
    }
    else if ( diff > -1 ) {
      ucg.drawGlyph (sX, sY, 0, 18); //arrow horizontal
    }
    else if ( diff > -4 ) {
      ucg.drawGlyph (sX, sY, 0, 24); //arrow 45deg down
    }
    else {
      ucg.drawGlyph (sX, sY, 0, 19); //arrow down
    }
    Serial.println (F("updateGauges()...increase/decrease shown"));

    // show a warning or error sign if necessary
    ucg.setColor(1, BLACK, BLACK, BLACK); // set background color
    ucg.setFontMode(UCG_FONT_MODE_SOLID); //erase the old mark by clearing the background with black
    ucg.setFont (ucg_font_10x20_67_75);
    ucg.setFontPosTop();
    sX = cX + xTR[WARNINGSECTIDX];
    sY = cY + yTR[WARNINGSECTIDX];
    if ( g_gauge[gaugeIdx].errStat == WARNINGSTATE ) {
      setRGBcolors (c_warningSignColor); // orange
      ucg.setColor(g_R, g_G, g_B);
      ucg.drawGlyph (sX, sY, 0, 178);
    }
    else if ( g_gauge[gaugeIdx].errStat == ERRORSTATE ) {
      setRGBcolors (c_errorSignColor); // red
      ucg.setColor(g_R, g_G, g_B);
      ucg.drawGlyph (sX, sY, 0, 188);
    }
    else {
      ucg.setColor(BLACK, BLACK, BLACK); // remove any previous marking
      ucg.drawGlyph (sX, sY, 0, 188);
      ucg.drawGlyph (sX, sY, 0, 178);
    }

    Serial.println (F("updateGauges()...error mark shown"));

  } // end of SHOW_ALL
  
  // show the title of the gauge 
  ucg.setColor(0, WHITE, WHITE, WHITE);
  ucg.setFont (ucg_font_helvB10_hf);
  ucg.setColor(1, BLACK, BLACK, BLACK); // set background color
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFontPosTop();
  ucg.setPrintPos ( cX - (ucg.getStrWidth(g_gauge[gaugeIdx].title) / 2), 1 ); 
  ucg.print ( g_gauge[gaugeIdx].title );

  Serial.println (F("updateGauges()...gauge tile shown"));
  Serial.println (F("end of updateGauges()"));

} // end of UpdateGauge()

void setup() {
  // initialise this sketch, prepare sensors and display

  delay(1000);
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println(F("Efficiency monitor"));
  Serial.println (F("Setup()..."));

  // Start up the library
  sensors.begin();

  // locate devices on the bus
  Serial.print(F("Locating devices...found "));
  Serial.print(sensors.getDeviceCount(), DEC); Serial.println(F(" sensors."));


  if (!sensors.getAddress(inPipeThermIDX, 0)) {
    Serial.println(F("Unable to find address for Device 0"));
    g_errorState = TRUE;
    updateMsgBox(2); /* "ERR: Sensor (IN) not found" */
  }
  if (!sensors.getAddress(outPipeThermIDX, 1)) {
    Serial.println(F("Unable to find address for Device 1"));
    g_errorState = TRUE;
    updateMsgBox(3); /* "ERR: Sensor (OUT) not found" */
  }

  // generic initilisation for all gauges
  for ( word i = GAUGE1; i <= GAUGE3; i++) {
    g_gauge[i].measurements = 0;
    g_gauge[i].sum = 0;
    g_gauge[i].avgW = 0;
    g_gauge[i].errStat = 0;
  }

  // set the resolution to 9 bit per device
  if ( !g_errorState ) {
    sensors.setResolution(inPipeThermIDX, TEMPERATURE_PRECISION);
    sensors.setResolution(outPipeThermIDX, TEMPERATURE_PRECISION);
    delay (500);

    // call sensors.requestTemperatures() to issue a global temperature
    // request to all devices on the bus
    sensors.requestTemperatures();
    delay (500);

    // preset a previous value for the sensors
    g_gauge[GAUGE1].currValue = byte ( round (sensors.getTempC(inPipeThermIDX) ));
    g_gauge[GAUGE1].prevValue = g_gauge[GAUGE1].absLow = g_gauge[GAUGE1].absHigh = g_gauge[GAUGE1].currValue;  // gna gna, lazy programmer
    g_gauge[GAUGE2].currValue = byte ( round (sensors.getTempC(outPipeThermIDX) ));
    g_gauge[GAUGE2].prevValue = g_gauge[GAUGE2].absLow = g_gauge[GAUGE2].absHigh = g_gauge[GAUGE2].currValue;
    Serial.println(F("Presetting currValues"));
    Serial.print (F("currValue1 = ")); Serial.println (g_gauge[GAUGE1].currValue);
    Serial.print (F("currValue2 = ")); Serial.println (g_gauge[GAUGE2].currValue);

    ucg.begin(UCG_FONT_MODE_TRANSPARENT);
    ucg.setRotate270();
    ucg.clearScreen();
    ucg.setFont(ucg_font_ncenR10_tr);
    ucg.setColor(255, 255, 255);
    updateMsgBox(13); /* version information */

    initialiseGauges();
    initialiseGraphs();
    delay (2500);
    
    while ( g_gauge[GAUGE2].currValue >= g_gauge[GAUGE1].currValue) { // wait until inTemp is hotter than outTemp before showing the gauges
      updateMsgBox(4); /* "...waiting until temp-in is hotter than out"); */
      updateGauge(GAUGE1, SHOW_TEMP); // only show the measured temperature, no other data
      updateGauge(GAUGE2, SHOW_TEMP); // only show the measured temperature, no other data
      delay (2500);
      sensors.requestTemperatures();
      delay (500);
      g_gauge[GAUGE1].currValue = byte ( round (sensors.getTempC(inPipeThermIDX) ));
      g_gauge[GAUGE2].currValue = byte ( round (sensors.getTempC(outPipeThermIDX) ));
      Serial.print (F("waiting for out < in, in = ")); Serial.print( g_gauge[GAUGE1].currValue ); 
      Serial.print(F(", ou = ")); Serial.println( g_gauge[GAUGE2].currValue );
    }
    // after this while() the inTemp must be higher than the outTemp
    // now calculate the first efficiency and start the loop()
//    g_gauge[GAUGE3].currValue = byte ( 100 - round ( 100 * ((float(g_gauge[GAUGE2].currValue) / float(g_gauge[GAUGE1].currValue))) ));
      g_gauge[GAUGE3].currValue = byte ( round ( 100 * ((float(g_gauge[GAUGE2].currValue) / float(g_gauge[GAUGE1].currValue))) ));
      g_gauge[GAUGE3].prevValue = g_gauge[GAUGE3].absLow = g_gauge[GAUGE3].absHigh = g_gauge[GAUGE3].currValue;
  }

  updateMsgBox(0); /* ~clear~ */
  Serial.println (F("end Setup()..."));

} //end of setup()


void loop() {
  // main program loop

  // TODO: add animated progress indicator
  // TODO: keep track of time, show the duration of the measurements
  // TODO: use a timer to do the measurements every X seconds. Show the progress indicator working between the measurements

  static float inTemp, outTemp, efficiency;

  Serial.println (F("Loop() start"));

  if ( !g_errorState ) { //during Setup() or previous cycle something may has gone wrong. In that case do not take measurements

    Serial.println (F(">no errors, process sensor request"));

    // call sensors.requestTemperatures() to issue a global temperature
    // request to all devices on the bus
    sensors.requestTemperatures();
    delay (250);

    inTemp = sensors.getTempC(inPipeThermIDX);
    outTemp = sensors.getTempC(outPipeThermIDX);

    //evaluate the measurements and act accordingly
    if ( inTemp <= 0.0F ) {// freezing water... discard measurement
      updateMsgBox(5); /* "ERR: sensor 1 (in) < 0 gr" */
      g_gauge[GAUGE1].errStat = ERRORSTATE ;
      g_errorState = TRUE;
    } //end if

    if (outTemp <= 0.0F) {// freezing water... discard measurement
      updateMsgBox(6); /* "ERR: sensor 2 (out) < 0 gr" */
      g_gauge[GAUGE2].errStat = ERRORSTATE ;
      g_errorState = TRUE;
    } //end if

    if ( !g_errorState ) {//all is ok, process measurements
      Serial.println (F(">sensors OK, process measurements"));
      // GAUGE1:: incoming temperature
      g_gauge[GAUGE1].prevValue = g_gauge[GAUGE1].currValue;  // save the old currValue to prevValue
      g_gauge[GAUGE1].currValue = byte ( round ( inTemp ));  // store new currValue
      if ( g_gauge[GAUGE1].currValue < g_gauge[GAUGE1].absLow ) g_gauge[GAUGE1].absLow = g_gauge[GAUGE1].currValue ; // reset abslow is needed
      if ( g_gauge[GAUGE1].currValue > g_gauge[GAUGE1].absHigh ) g_gauge[GAUGE1].absHigh = g_gauge[GAUGE1].currValue ; //reset absHigh if needed

      // GAUGE2:: outgoing temperature
      g_gauge[GAUGE2].prevValue = g_gauge[GAUGE2].currValue; // save the old currValue to prevValue
      g_gauge[GAUGE2].currValue = byte ( round ( outTemp )); // store new currValue
      if ( g_gauge[GAUGE2].currValue < g_gauge[GAUGE2].absLow ) g_gauge[GAUGE2].absLow = g_gauge[GAUGE2].currValue ; // reset abslow is needed
      if ( g_gauge[GAUGE2].currValue > g_gauge[GAUGE2].absHigh ) g_gauge[GAUGE2].absHigh = g_gauge[GAUGE2].currValue ; //reset absHigh if needed

      Serial.print (F("currValue(in) = ")); Serial.println ( g_gauge[GAUGE1].currValue );
      Serial.print (F("currValue(out) = ")); Serial.println ( g_gauge[GAUGE2].currValue );
      
      // calc efficiency but don't store until the difference between in and out is processed
      efficiency = outTemp / inTemp;  //should be OK, inTemp <> 0 

      if (outTemp > inTemp) { //incoming temp lower than outgoing, so don't store the measurements but only show them, discard efficiency completely
        efficiency = 0.0F; //prevent strange eff values if out is hotter than in
        g_gauge[GAUGE1].errStat = WARNINGSTATE ; 
        g_gauge[GAUGE2].errStat = WARNINGSTATE ;
        g_gauge[GAUGE3].errStat = ERRORSTATE ; // in this case, no efficiency may be calculated
        Serial.println (F(">>T(out) > T(in), reverse flow?"));
        if ( (inTemp / outTemp) < 0.85F ) { // large difference between in and out when out is hotter than in
          Serial.println (F(">>>eff < 0.85"));
          updateMsgBox(7); /* "WARN: T-in much cooler than T-out" */
        } //end if (in/out) < 0.85
        else { // negative heatflow but difference between 100% - 80%
          Serial.println (F(">>>eff >=0.85 "));
          updateMsgBox(8); /* "INFO: CV paused, radiator is cooling (OK)" */
        } //end else
      } //end if IN lower than OUT
      else { // normal heat flow, in is hotter then out, store measurements
        Serial.println (F(">>in >= out (normal flow)"));

        //process GAUGE1
        g_gauge[GAUGE1].errStat = 0 ; 
        g_gauge[GAUGE1].sum += g_gauge[GAUGE1].currValue;
        g_gauge[GAUGE1].measurements += 1;
        g_gauge[GAUGE1].avgW =  byte ( round ( float(g_gauge[GAUGE1].sum) / float(g_gauge[GAUGE1].measurements) )) ; // should be save, #measurements is never 0
        Serial.print (F("#measurements = ")); Serial.println ( g_gauge[GAUGE1].measurements );

        //process GAUGE2
        g_gauge[GAUGE2].errStat = 0 ;
        g_gauge[GAUGE2].sum += g_gauge[GAUGE2].currValue;
        g_gauge[GAUGE2].measurements += 1;
        g_gauge[GAUGE2].avgW =  byte ( round ( float(g_gauge[GAUGE2].sum) / float(g_gauge[GAUGE2].measurements) )) ;

        //process GAUGE3
        g_gauge[GAUGE3].errStat = 0 ;
        g_gauge[GAUGE3].prevValue = g_gauge[GAUGE3].currValue; // save the previous value;
//        g_gauge[GAUGE3].currValue = byte ( 100 - round (100 * efficiency ));  // old calculation, show efficiency of radiation (10% - 30%);
        g_gauge[GAUGE3].currValue = byte ( round (100 * efficiency )); // new calculation, shows energy efficiency (70% - 90%)
        if ( g_gauge[GAUGE3].currValue > 99 ) g_gauge[GAUGE3].currValue = 99; //limit the efficiency to 99%
        g_gauge[GAUGE3].sum += g_gauge[GAUGE3].currValue;
        g_gauge[GAUGE3].measurements += 1;
        g_gauge[GAUGE3].avgW = byte ( round ( float(g_gauge[GAUGE3].sum) / float(g_gauge[GAUGE3].measurements) ));
        // check the current stored absolute min and max
        if ( g_gauge[GAUGE3].currValue < g_gauge[GAUGE3].absLow ) g_gauge[GAUGE3].absLow = g_gauge[GAUGE3].currValue ;
        if ( g_gauge[GAUGE3].currValue > g_gauge[GAUGE3].absHigh ) g_gauge[GAUGE3].absHigh = g_gauge[GAUGE3].currValue ;


        if (efficiency < 0.75F) { // big difference between in and out
          Serial.println (F(">>>eff < 0.75"));
          updateMsgBox(9); /* "INFO: heating increases rapidly (OK)" */
        } //end if eff < 0.75

        if ( (efficiency >= 0.75F) && (efficiency < 0.85F) ) { // between 25% and 15%
          Serial.println (F(">>>eff >= 0.75 - 0.85"));
          updateMsgBox(10); /* "INFO: efficiency is GOOD (70%-85%)" */
        } //end if eff >= 0.75 - 0.85

        if ( (efficiency >= 0.85F) && (efficiency < 0.98F) ) { // between 15% and 2%
          Serial.println (F(">>>eff >= 0.85 - 0.98"));
          updateMsgBox(11); /* "INFO: efficiency LOW (>85%)" */
        } //end if eff >= 0.85 - 0.98

        if ( efficiency >= 0.98F ) { // smaller than 2%
          Serial.println (F(">>>eff >= 0.98"));
          updateMsgBox(12); /* "WARN: no heat flow!  T-in = T-out" */
        } //end if eff >= 0.98
      } //end else normal heat flow
    } //end process measurements
  }
  else {
    // do something when g_errorState == TRUE
    Serial.println (F("ERROR program flow in Loop()"));
    g_gauge[GAUGE1].errStat = ERRORSTATE ;
    g_gauge[GAUGE2].errStat = ERRORSTATE ;
    g_gauge[GAUGE3].errStat = ERRORSTATE ;
    updateMsgBox(1); /* "ERR: setup error or sensor error" */
    // clear actual values from the gauge in case of error, but show warning or error indicator
  }

  updateGauge(GAUGE1, SHOW_ALL);
  updateGauge(GAUGE2, SHOW_ALL);
  updateGauge(GAUGE3, SHOW_ALL);
  updateGraphs();
  
  //  updateGraph(GAUGE2);

//  delay (SAMPLESPEED * 1000);
  delay (10);
  //  while(true) { };

}
