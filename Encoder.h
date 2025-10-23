
#ifndef ENCODER
#define ENCODER

#include "Arduino.h"
#include "Time_Clock.h"

class Encoder {

public:

	Encoder(int CLK, int DT, int HB);

	bool EncoderCheck(Time_Clock *time_clock);
	bool ButtonPressCheck();

private:
  
	int  inputCLK, inputDT, HourButton;
	bool PressLock; //used to prevent mutiple button presses
	int currentStateCLK, previousStateCLK; //Used for encoder
	
};

#endif
