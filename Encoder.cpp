#include "Encoder.h"
#include "Arduino.h"
#include "Time_Clock.h"

Encoder::Encoder(int CLK, int DT, int HB) {

	bool PressLock = false;
	inputCLK = CLK;
	inputDT = DT;
	HourButton = HB;
	
  
	//Set all pins for encoder
	pinMode(inputCLK, INPUT);
	pinMode(inputDT, INPUT);
	pinMode(HourButton, INPUT);
  

	// Read the initial state of inputCLK
	// Assign to previousStateCLK variable
	previousStateCLK = digitalRead(inputCLK);

}


/*This function checks if the encoder has moved. It then calls the time set function accordingly.
* The Time_Clock function is passed in, and then pointed TimeClock Function is pointed to.
*/
bool Encoder::EncoderCheck(Time_Clock *time_clock) {
    bool Change = false; 
    currentStateCLK = digitalRead(inputCLK);
    // If the previous and the current state of the inputCLK are different then a pulse has occured
    if (currentStateCLK != previousStateCLK) {
        // If the inputDT state is different than the inputCLK state then
        if (digitalRead(inputDT) != currentStateCLK) {
            // Encoder is rotating counterclockwise
            //Serial.println("CCW");
            time_clock->SetTimeMWithMinFromMidnight(time_clock->MinutesFromMidnight() - 1);    
            Change = true;
        }
        else {
            // Encoder is rotating clockwise
            //Serial.println("CW");
            time_clock->SetTimeMWithMinFromMidnight(time_clock->MinutesFromMidnight() + 1);
            Change = true;
        }
    }
    // Update previousStateCLK with the current state
    previousStateCLK = currentStateCLK;
    return Change;
}

/*This Function handles the button press which switches between 24 hour and 12hour
* Time must be reset after switch as it does not handle the swap well
*/
bool Encoder::ButtonPressCheck() {
  
    if ((digitalRead(HourButton) == 1) && (PressLock == false)) {
        PressLock = true;
        return false;
    }
    else if ((digitalRead(HourButton) == 0) && (PressLock == true)) {
        PressLock = false;
        Serial.println("Push Button");
        //Button Pressed
        return true;
    }
   
    return false;
}
