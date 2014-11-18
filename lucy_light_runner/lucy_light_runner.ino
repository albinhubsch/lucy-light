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
int MAXBRIGHTNESS = 160;
int controller = 8;
boolean power = false;

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

// 
// SETUP
// 
void setup() {

    // 
    pinMode(controller, INPUT);

    inData[0] = 0;
    inData[1] = 0;
    inData[2] = 0;
    inData[3] = 0;

    Serial.begin(9600);

    leds.begin();  // Call this to start up the LED strip.
    startUpSequence();
}

// 
// LOOP
// Program loop listening for comands and controlls the light
// 
// State,activity,strenght
// type, duration, freq, indetifier
// 
void loop()
{

    int looper = 0;

    int activity = 0;
    int duration = 0;
    int freq = 0;
    int identifier = 0;
    int strenght = 255;
    int controller_val = 0;
  
    serialToString();

    if(duration == 0 && identifier != inData[3])
    {
        activity = inData[0];
        duration = inData[1];
        freq = inData[2];
        identifier = inData[3];
    }

    if(power)
    {
        if(identifier == 0)
        {
            led_error();
        }else{
            switch(activity)
            {
                case 0:
                    pulse(WALKING, 60, map(strenght, 0, 255, 60, MAXBRIGHTNESS), freq);
                break;
                case 1:
                    pulse(CYCLING, 60, map(strenght, 0, 255, 60, MAXBRIGHTNESS), freq);
                break;
                case 2:
                    pulse(RUNNING, 60, map(strenght, 0, 255, 60, MAXBRIGHTNESS), freq);
                break;
                default:
                    pulse(WARNING, 60, map(strenght, 0, 255, 60, MAXBRIGHTNESS), freq);
            }
        }
    }else{
        stateStanding(BLACK, 0);
    }
    
    // If looper reach 100, 1 second has passed and should be deleted from duration
    if(looper == 100)
    {
        if(power)
        {
            duration--;
        }
        looper = 0;
    }

    looper++;

    controller_val = digitalRead(controller);

    if (controller_val == 0)
    {
        power = !power;
        
        if(!power)
        {
            stateStanding(BLACK, 0);
            delay(2000);
        }
    }

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
        inData[0] = Serial.parseInt();
        inData[1] = Serial.parseInt();
        inData[2] = Serial.parseInt();
        inData[3] = Serial.parseInt();

        if (Serial.read() == '\n') {

        }
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
void pulse(uint32_t color, int low, int high, int speed)
{

    // speed = speed

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
        leds.setBrightness(MAXBRIGHTNESS);
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

        for (int i = 15; i < MAXBRIGHTNESS; ++i)
        {
            leds.setBrightness(i);
            leds.show();
            delay(1);
        }

        for (int i = MAXBRIGHTNESS; i > 15; --i)
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
