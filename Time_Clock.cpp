#include "Time_Clock.h"
#include <Wire.h>
#include <DS3231.h>


//For some reason this required me to pass a varable to default constructure?
Time_Clock::Time_Clock(bool x) {
    
    Wire.begin();
    
}


/*This function calculates the minutes from midnight. This is used to set time,
* as adding to total minutes is easier and quicker then nested if statements needed
* for all cases.
* This also checks for 24 or 12 hour setup. Time is always set with 24 hour time.
*/
int Time_Clock::MinutesFromMidnight() {
    if (h12Flag) {
        if (pmFlag) {
            return((Clock_Chip.getHour(h12Flag, pmFlag) + 12) * 60 + Clock_Chip.getMinute());
        }
        else {
            if (Clock_Chip.getHour(h12Flag, pmFlag) == 12) {
                return (Clock_Chip.getMinute());
            }
            else {
                return (Clock_Chip.getHour(h12Flag, pmFlag) * 60 + Clock_Chip.getMinute());
            }

        }
    }
    else {//24 hours format
        return (Clock_Chip.getHour(h12Flag, pmFlag) * 60 + Clock_Chip.getMinute());
    }

}

/* This function sets the time from minutes from midnight. It also handles
* the day wrap. Using minutes from midnight makes it much simpler, when working
* with both 24 and 12 AM/PM configurations
*/
void Time_Clock::SetTimeMWithMinFromMidnight(int TotalMin) {
    //Serial.println(TotalMin );
    //Handle Day Wrap
    if (TotalMin >= 1440) {
        TotalMin = 0;
    }
    else if (TotalMin < 0) {
        TotalMin = 1439;
    }

    Clock_Chip.setHour(TotalMin / 60);
    Clock_Chip.setMinute(TotalMin % 60);
    //SerialPrintTime();
    //Serial.println("\n");

    ClockSerialPrintTime();
}



/*This Function checks to see if the clock is in 12 or 24 hour mode
The chip does not seem to handle 24 hour to AM/PM, so time must be reset after change
Save time, adjust mode and resave time
h12Flag -> 24hour = false, 12hour = true
pmFlag -> True = PM, False = AM
*/
void Time_Clock::TwelveOrTwentyFour() {
    
    if (h12Flag) {  //In 12hour mode
        int temp = MinutesFromMidnight();
        Clock_Chip.setClockMode(false);
        SetTimeMWithMinFromMidnight(temp);
    }
    else {      //In 24hour mode
        int temp = MinutesFromMidnight();
        Clock_Chip.setClockMode(true);
        SetTimeMWithMinFromMidnight(temp);
    }

}

/*Set time was added to allow the 24/12 hour to be set without push button
 * The push button triggers randomly and causes issues
 */
void Time_Clock::Set24Hour(){
  int temp = MinutesFromMidnight();
  Clock_Chip.setClockMode(false);
  SetTimeMWithMinFromMidnight(temp);
}

void Time_Clock::Set12Hour(){
  int temp = MinutesFromMidnight();
  Clock_Chip.setClockMode(true);
  SetTimeMWithMinFromMidnight(temp);
}

/* Serial out time in nice format
*/
void Time_Clock::ClockSerialPrintTime() {
    if (h12Flag) {
        if (pmFlag) {
            Serial.print(Clock_Chip.getHour(h12Flag, pmFlag), DEC);
            Serial.print(":");
            Serial.print(Clock_Chip.getMinute(), DEC);
            Serial.println(" PM");
        }
        else {
            Serial.print(Clock_Chip.getHour(h12Flag, pmFlag), DEC);
            Serial.print(":");
            Serial.print(Clock_Chip.getMinute(), DEC);
            Serial.println(" AM");
        }
    }
    else {
        Serial.print(Clock_Chip.getHour(h12Flag, pmFlag), DEC);
        Serial.print(":");
        Serial.println(Clock_Chip.getMinute(), DEC);
    }
}

/* Serial out time in nice format
*/
int Time_Clock::TimeinInt() {
    int time = 0;
    if (h12Flag) {
        if (pmFlag) {
            time = Clock_Chip.getHour(h12Flag, pmFlag) * 100;
            time = time + Clock_Chip.getMinute();
        }
        else {
            time = Clock_Chip.getHour(h12Flag, pmFlag) * 100;
            time = time + Clock_Chip.getMinute();
        }
    }
    else {
        time = Clock_Chip.getHour(h12Flag, pmFlag) * 100;
        time = time + Clock_Chip.getMinute();
    }
    return time;
}
