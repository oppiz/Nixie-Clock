#include "NixieDisplay.h"
#include "Arduino.h"

NixieDisplay::NixieDisplay(int latch_pin, int clock_pin, int data_pin, int oe_pin) {
	
  Latch_Pin = latch_pin;
	Clock_Pin = clock_pin;
	Data_Pin = data_pin;
	OE_Pin = oe_pin;
    
    //Set Pin Modes
    pinMode(Latch_Pin, OUTPUT);
    pinMode(Data_Pin, OUTPUT);
    pinMode(Clock_Pin, OUTPUT);
    pinMode(OE_Pin, OUTPUT);
    
    //Turn all outputs off for start up. 
    digitalWrite(OE_Pin, HIGH);
    digitalWrite(Latch_Pin, LOW);
    shiftOut(Data_Pin, Clock_Pin, LSBFIRST, 0);
    shiftOut(Data_Pin, Clock_Pin, LSBFIRST, 0);
    shiftOut(Data_Pin, Clock_Pin, LSBFIRST, 0);
    shiftOut(Data_Pin, Clock_Pin, LSBFIRST, 0);
    shiftOut(Data_Pin, Clock_Pin, LSBFIRST, 0);
    shiftOut(Data_Pin, Clock_Pin, LSBFIRST, 0);
    shiftOut(Data_Pin, Clock_Pin, LSBFIRST, 0);
    shiftOut(Data_Pin, Clock_Pin, LSBFIRST, 0);
    digitalWrite(Latch_Pin, HIGH);
    digitalWrite(OE_Pin, LOW);
}


void NixieDisplay::NumberToPrint(int num) {

    //Split time into digits needed to display
    int HF = num % 10;
    num = num / 10;
    int HS = num % 10;
    num = num / 10;
    int MF = num % 10;
    num = num / 10;
    int MS = num % 10;
    num = num / 10;
    
    byte HF_A, HF_B, HS_A, HS_B, MF_A, MF_B, MS_A, MS_B;

    bitSet(HF_A, AIndex(HF));
    bitSet(HF_B, BIndex(HF));
    bitSet(HS_A, AIndex(HS));
    bitSet(HS_B, BIndex(HS));
    bitSet(MF_A, AIndex(MF));
    bitSet(MF_B, BIndex(MF));
    bitSet(MS_A, AIndex(MS));
    bitSet(MS_B, BIndex(MS));
      
    digitalWrite(OE_Pin, HIGH);
    digitalWrite(Latch_Pin, LOW);
    shiftOut(Data_Pin, Clock_Pin, LSBFIRST, MS_A);
    shiftOut(Data_Pin, Clock_Pin, LSBFIRST, MS_B);
    shiftOut(Data_Pin, Clock_Pin, LSBFIRST, MF_A);
    shiftOut(Data_Pin, Clock_Pin, LSBFIRST, MF_B);
    shiftOut(Data_Pin, Clock_Pin, LSBFIRST, HS_A);
    shiftOut(Data_Pin, Clock_Pin, LSBFIRST, HS_B);
    shiftOut(Data_Pin, Clock_Pin, LSBFIRST, HF_A);
    shiftOut(Data_Pin, Clock_Pin, LSBFIRST, HF_B);

    
    digitalWrite(Latch_Pin, HIGH);
    digitalWrite(OE_Pin, LOW);

    //ChipA
    //1 == NULL
    //2 == 9
    //4 == 0
    //8 == right comma
    //16 == left comm
    //32 == 1
    //64 == 2
    
    //ChipB
    //1 == NULL
    //2 == 3
    //4 == 4
    //8 == 5
    //16 == 6
    //32 == 7
    //64 == 8
}   


//Switch between the number desired and the pin needed on the board.
//Numbers 0,1,2,9 are on Chip A
//Numbers 3,4,5,6,7,8 are on Chip B
int NixieDisplay::AIndex(int i) {
    switch (i) {
    case 0:
        return (2);
        break;
    case 1:
        return (5);
        break;
    case 2:
        return (6);
        break;
    case 3:
        return (0);
        break;
    case 4:
        return (0);
        break;
    case 5:
        return (0);
        break;
    case 6:
        return (0);
        break;
    case 7:
        return (0);
        break;
    case 8:
        return (0);
        break;
    case 9:
        return (1);
        break;
    default:
        return (0);
        break;
    }

}
int NixieDisplay::BIndex(int i) {
    switch (i) {
    case 0:
        return (0);
        break;
    case 1:
        return (0);
        break;
    case 2:
        return (0);
        break;
    case 3:
        return (1);
        break;
    case 4:
        return (2);
        break;
    case 5:
        return (3);
        break;
    case 6:
        return (4);
        break;
    case 7:
        return (5);
        break;
    case 8:
        return (6);
        break;
    case 9:
        return (0);
        break;
    default:
        return (0);
        break;
    }
}
