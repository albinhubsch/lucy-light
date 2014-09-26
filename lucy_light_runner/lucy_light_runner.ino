// 
// 
// 
#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"

#define PIN 4
#define LED_COUNT 2

// 
// 
// 
char inData[100]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

// 
// SETUP
// 
void setup() {
    Serial.begin(9600);
    Serial.write("Power On");

    leds.begin();  // Call this to start up the LED strip.
    clearLEDs();   // This function, defined below, turns all LEDs off...
    leds.show();   // ...but the LEDs don't actually update until you call this.
}

// 
// LOOP
// Program loop listening for comands and controlls the light
// 
void loop()
{
  
    serialToString();

    Serial.write(inData);
    
    clearLEDs();
    leds.setPixelColor(0, NAVY);
    leds.setPixelColor(1, WALKING);
    leds.show();

    led_error();
    
    delay(2000);
    
}

// 
// COMP
// Translates bytes to actual string
// 
char serialToString()
{
  
    memset(&inData[0], 0, sizeof(inData));

    // Don't read unless you know there is data
    while (Serial.available() > 0)
    {
        
        // One less than the size of the array
        if(index < 99)
        {
            inChar = Serial.read(); // Read a character
            inData[index] = inChar; // Store it
            index++; // Increment where to write next
            inData[index] = '\0'; // Null terminate the string
        }
    }
    
    index = 0;
}

//
// Flash a error message
// Something went wrong, no bootup call from py
//
void led_error()
{

    // Set color of leds
    for (int i = 0; i < LED_COUNT; i++)
    {
        leds.setPixelColor(i, WARNING);
    }

    leds.show();

    // Flash 5 times
    for (int i = 0; i < 5; i++)
    {
        leds.setBrightness(0);
        leds.show();
        delay(200);
        leds.setBrightness(255);
        leds.show();
        delay(200);
    }

    leds.show();
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
