/*
 Name:		NixieClock.ino
 Created:	4/27/2021 8:53:46 AM
 Author:	zippo
*/

#include "NixieDisplay.h"
#include "Time_Clock.h"
#include "Encoder.h"

/*
latchPin 8  // Latch pin of 74HC595 is connected to Digital pin 5
clockPin 5 // Clock pin of 74HC595 is connected to Digital pin 6
dataPin 10  // Data pin of 74HC595 is connected to Digital pin 4
OE 9 //Enable Bit

inputCLK 6 // Encoder counter
inputDT 12 // Encouder counter
HourButton 13 // Encoder button press
*/

NixieDisplay nixiedisplay(8, 5, 10, 9); 
Time_Clock time_clock(true);
Encoder encoder(6, 12, 13);

unsigned long LoopTime; //used to only check time every so often

void setup()
{

    Serial.begin(9600);
   
    delay(500);
    LoopTime = millis();//set the looptime first time

}


void loop()
{
    
    if (encoder.ButtonPressCheck()) {
        time_clock.TwelveOrTwentyFour(); //Call clock class to swap 24/12hour configuration
        nixiedisplay.NumberToPrint(time_clock.TimeinInt());
    }

    //Check to see is encoder has moved, call time_clock set function
    //If changed, update the NixieClock display
    if (encoder.EncoderCheck(&time_clock)){
      nixiedisplay.NumberToPrint(time_clock.TimeinInt(), time_clock.Need_PM());
    }

    //Uses the sloppy CPU clock time to limit the amount of checks to RTC chip
    if ((millis() - LoopTime) > 10000) {
        time_clock.ClockSerialPrintTime();
        nixiedisplay.NumberToPrint(time_clock.TimeinInt(), time_clock.Need_PM());
        LoopTime = millis(); //set looptime to now
    }



}
