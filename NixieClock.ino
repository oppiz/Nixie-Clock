/*
 Name:		NixieClock.ino
 Created:	4/27/2021 8:53:46 AM
 Author:	zippo
*/

#include "NixieDisplay.h"
#include "Time_Clock.h"
#include "Encoder.h"

/*
SDMA = 17; //PB0
SDMB = 19; //PF6
SDMC = 18; //PF7
SDMD = 7; //PE6
FDMA = 23; //PF0
FDMB = 21; //PF4
FDMC = 20; //PF5
FDMD = 22; //PF1
SDHA = 13; //PC7
SDHB = 10; //PB6
SDHC = 9; //PB5
SDHD = 5; //PC6
FDHA = 8; //PB4
FDHB = 12; //PD6
FDHC = 4; //PD4
FDHD = 6; //PD7
  
inputCLK 0 // Encoder counter
inputDT 1 // Encouder counter
HourButton 30 // Encoder button press
*/


int HWPINS[16] = {17, 19, 18, 7, 23, 21, 20, 22, 13, 10, 9, 5, 8, 12, 4, 6};

NixieDisplay nixiedisplay(HWPINS); 
Time_Clock time_clock(true);
Encoder encoder(0, 1, 30);

unsigned long LoopTime; //used to only check time every so often

void setup()
{

    Serial.begin(9600);
   
    delay(500);
    LoopTime = millis();//set the looptime first time
    time_clock.Set24Hour();
}


void loop()
{
    
    if (encoder.ButtonPressCheck()) {
        time_clock.TwelveOrTwentyFour(); //Call clock class to swap 24/12hour configuration
        nixiedisplay.NumberToPrint(time_clock.TimeinInt());
    }

    //Check to see is encoder has moved, call time_clock set function
    if (encoder.EncoderCheck(&time_clock)){
      nixiedisplay.NumberToPrint(time_clock.TimeinInt());
    }

    //Uses the sloppy CPU clock time to limit the amount of checks to RTC chip
    if ((millis() - LoopTime) > 10000) {
        time_clock.ClockSerialPrintTime();
        //Serial.println(time_clock.TimeinInt());
        nixiedisplay.NumberToPrint(time_clock.TimeinInt());
        LoopTime = millis(); //set looptime to now
    }



}
