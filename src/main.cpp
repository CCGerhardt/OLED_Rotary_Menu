#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "DHT.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define DEGREE 247

#define OLED_RESET -1 // Reset pin
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire, OLED_RESET);

#define CLK 32
#define DT 35
#define SW 34

#define DHTPIN 27
DHT dht(DHTPIN,DHT11);
long lastReadTime = 0;
float temp = dht.readTemperature();

void testScrollText(void);
void mainMenu(void);

int arrowPos = 0;

void setup() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(500); // Pause for 0.5 seconds

  dht.begin();
  }

void loop() {
  // Clear bufffer and re-write on loop call
  display.clearDisplay();
  mainMenu(); // Display the main menu with temperature sensor
  arrowPos++; // Increment arrow position
}

void mainMenu(void){

  if (millis()-lastReadTime > 1000){
    temp = dht.readTemperature();
    lastReadTime = millis();
  }

  /*
    Below are pixel art parameters
  */
  uint8_t width = 128;
  uint8_t height = 11;
  uint8_t x_cord = 0;
  uint8_t upper_y = 0;
  uint8_t lower_y = SCREEN_HEIGHT-height;
  uint8_t numLines = 4;

  display.drawRect(x_cord,upper_y,width,height, SSD1306_WHITE);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(x_cord+2, upper_y+2);
  display.printf("Test: %.2f%cC\n",temp,(char)DEGREE);

  uint8_t y_cord = upper_y+height;
  for (uint8_t i = 0; i < numLines;i++){
    display.setCursor(x_cord+2, y_cord);
    display.printf(" Test: %d\n",(uint8_t)i);
    y_cord += 11;

  }

  uint8_t arrP = upper_y+height+11*(arrowPos%numLines);
  display.setCursor(x_cord+2,arrP);
  display.printf(">");



  // display.drawFastHLine(x_cord,)
  display.drawRect(x_cord,lower_y,width,height, SSD1306_WHITE);
  display.display();
}
