
#ifndef NIXIEDISPLAY
#define NIXIEDISPLAY

class NixieDisplay {

public:

	NixieDisplay(int latch_pin, int clock_pin, int data_pin, int oe_pin);

	void NumberToPrint(int num, bool PM);
	bool Need_PM();
  


private:
	int Latch_Pin, Clock_Pin, Data_Pin, OE_Pin;

	int AIndex(int i);
	int BIndex(int i);

};

#endif
