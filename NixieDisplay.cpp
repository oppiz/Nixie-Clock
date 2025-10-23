#include "NixieDisplay.h"
#include "Arduino.h"

NixieDisplay::NixieDisplay(int HWPINS[16]) {
	
    for (int i = 0; i < 16; i++){
      HW_PINS[i] = HWPINS[i];
      pinMode(HW_PINS[i], OUTPUT);
      //digitalWrite(i, LOW);
    }


    PrintNumber(0, HW_PINS[0], HW_PINS[1], HW_PINS[2], HW_PINS[3]);
    PrintNumber(0, HW_PINS[4], HW_PINS[5], HW_PINS[6], HW_PINS[7]);
    PrintNumber(0, HW_PINS[8], HW_PINS[9], HW_PINS[10], HW_PINS[11]);
    PrintNumber(0, HW_PINS[12], HW_PINS[13], HW_PINS[14], HW_PINS[15]);

}


void NixieDisplay::NumberToPrint(int num) {
    
    //Split time into digits needed to display
    int MS = num % 10;
    num = num / 10;
    int MF = num % 10;
    num = num / 10;
    int HS = num % 10;
    num = num / 10;
    int HF = num % 10;
    num = num / 10;

    
    //send each digit to the digit writer. The array has the pins for A B C & D for each tube
    PrintNumber(MS, HW_PINS[0], HW_PINS[1], HW_PINS[2], HW_PINS[3]);
    PrintNumber(MF, HW_PINS[4], HW_PINS[5], HW_PINS[6], HW_PINS[7]);
    PrintNumber(HS, HW_PINS[8], HW_PINS[9], HW_PINS[10], HW_PINS[11]);
    PrintNumber(HF, HW_PINS[12], HW_PINS[13], HW_PINS[14], HW_PINS[15]);
} 

void NixieDisplay::PrintNumber(int NUM, int A, int B, int C, int D){

  switch (NUM){
      case 0:
          digitalWrite(A, LOW);
          digitalWrite(B, HIGH);
          digitalWrite(C, LOW);
          digitalWrite(D, LOW);
          break;
      case 1:
          digitalWrite(A, HIGH);
          digitalWrite(B, LOW);
          digitalWrite(C, LOW);
          digitalWrite(D, HIGH);
          break;
      case 2:
          digitalWrite(A, LOW);
          digitalWrite(B, LOW);
          digitalWrite(C, LOW);
          digitalWrite(D, HIGH);
          break;
      case 3:
          digitalWrite(A, LOW);
          digitalWrite(B, LOW);
          digitalWrite(C, LOW);
          digitalWrite(D, LOW);
          break;
      case 4:
          digitalWrite(A, HIGH);
          digitalWrite(B, LOW);
          digitalWrite(C, LOW);
          digitalWrite(D, LOW);
          break;
      case 5:
          digitalWrite(A, HIGH);
          digitalWrite(B, LOW);
          digitalWrite(C, HIGH);
          digitalWrite(D, LOW);
          break;
      case 6:
          digitalWrite(A, LOW);
          digitalWrite(B, LOW);
          digitalWrite(C, HIGH);
          digitalWrite(D, LOW);
          break;
      case 7:
          digitalWrite(A, LOW);
          digitalWrite(B, HIGH);
          digitalWrite(C, HIGH);
          digitalWrite(D, LOW);
          break;
       case 8:
          digitalWrite(A, HIGH);
          digitalWrite(B, HIGH);
          digitalWrite(C, HIGH);
          digitalWrite(D, LOW);
          break;
      case 9:
          digitalWrite(A, HIGH);
          digitalWrite(B, HIGH);
          digitalWrite(C, LOW);
          digitalWrite(D, LOW);
          break;   
    }
   
  
}
