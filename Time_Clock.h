#ifndef TIME_CLOCK
#define TIME_CLOCK

#include <Wire.h>
#include <DS3231.h>

class Time_Clock {

public:
	
	Time_Clock(bool x);

	int MinutesFromMidnight();
	void SetTimeMWithMinFromMidnight(int TotalMin);
	void TwelveOrTwentyFour();
	void ClockSerialPrintTime();
  int TimeinInt();
  bool Need_PM();

private:

	DS3231 Clock_Chip;
	bool h12Flag, pmFlag;

};

#endif
