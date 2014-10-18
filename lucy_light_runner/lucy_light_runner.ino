// 
// 
// 
#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"
#include <JsonParser.h>

// using namespace ArduinoJson::Parser;

#define PIN 4
#define LED_COUNT 2

// 
// 
// 
char inData[100]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

using namespace ArduinoJson::Parser;

// 
// SETUP
// 
void setup() {
    Serial.begin(9600);
    Serial.write("Power On");

    JsonParser<32> parser;
    char json[] = "{\"sensor\":\"MYSENSOR\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

    JsonObject root = parser.parse(json);
    char* sensor = root["sensor"];
    Serial.write(sensor);


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

    // Serial.write(inData);
    
    // clearLEDs();
    // leds.setBrightness(0);
    // leds.setPixelColor(0, RUNNING);
    // leds.setPixelColor(1, WALKING);
    // leds.show();

    // stateMoving(WALKING, 10, 255);
    stateStanding(WALKING, 10);
    led_error();
    
    delay(1);
    
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

    int speed = 15;

    for (int i = 0; i < 5; ++i)
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
        leds.setBrightness(255);
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
