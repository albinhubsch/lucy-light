// 
// 
// 
#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"

#define PIN 4
#define LED_COUNT 60

// 
// 
// 
int inData[4]; // Allocate some space for the string

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

// 
// SETUP
// 
void setup() {
    // Serial.begin(9600);
    // Serial.println("Power On");

    leds.begin();  // Call this to start up the LED strip.
    startUpSequence();
}

// 
// LOOP
// Program loop listening for comands and controlls the light
// 
void loop()
{
  
    // serialToString();

    // if(inData[0] != 0)
    // {
    //     Serial.println(inData[0]);
    // }

    // if(state == 1)
    // {
    //     Serial.write("Moving");
    // }else if(state == 0){
    //     Serial.write("Standing");
    // }else{
    //     Serial.write("none");
    // }

    stateMoving(WALKING, 5, 30);
    // stateStanding(WALKING, 30);
    // led_error();
    
    delay(10);
    
}

// 
// COMP
// Translates bytes to actual string
// 
char serialToString()
{
    // Don't read unless you know there is data
    while (Serial.available() > 0)
    {
        Serial.println("Hittat");
        inData[0] = Serial.parseInt();
        inData[1] = Serial.parseInt();
        inData[2] = Serial.parseInt();

        Serial.println(inData[0]);
        Serial.println(inData[1]);
        Serial.println(inData[2]);
    }
}

// 
// 
// 
// 
void stateStanding(uint32_t color, int lum)
{
    clearLEDs();
    setStripColor(color);
    leds.setBrightness(lum);
    leds.show();
}

// 
// 
// 
// 
void stateMoving(uint32_t color, int low, int high)
{

    int speed = 20;

    for (int i = 0; i < 1; ++i)
    {
        
        clearLEDs();
        setStripColor(color);

        for (int i = low; i < high; ++i)
        {
            setStripColor(color);
            leds.setBrightness(i);
            leds.show();
            delay(speed);
        }

        for (int i = high; i > low; --i)
        {
            setStripColor(color);
            leds.setBrightness(i);
            leds.show();
            delay(speed);
        }

    }
}

// 
// 
// 
// 
void startUpSequence()
{

    clearLEDs();

    for (int i = 0; i < 6; ++i)
    {

        clearLEDs();
        setStripColor(WHITE);
        leds.setBrightness(150);
        leds.show();
        delay(150);
        leds.setBrightness(1);
        leds.show();
        delay(150);

    }
}

//
// Flash a error message
// Something went wrong, no bootup call from py
//
void led_error()
{

    for (int i = 0; i < 4; ++i)
    {
        clearLEDs();
        setStripColor(WARNING);

        for (int i = 15; i < 255; ++i)
        {
            leds.setBrightness(i);
            leds.show();
            delay(1);
        }

        for (int i = 255; i > 15; --i)
        {
            leds.setBrightness(i);
            leds.show();
            delay(1);
        }

        delay(10);

    }
}

void setStripColor(uint32_t color)
{
    for (int i=0; i<LED_COUNT; i++)
    {
        leds.setPixelColor(i, color);
    }
}

// 
// Clear all leds on strip
// 
void clearLEDs()
{
    
    for (int i=0; i<LED_COUNT; i++)
    {
        leds.setPixelColor(i, 0);
    }
}
