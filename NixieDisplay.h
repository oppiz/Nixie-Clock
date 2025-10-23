
#ifndef NIXIEDISPLAY
#define NIXIEDISPLAY

class NixieDisplay {

public:

	NixieDisplay(int HWPINS[16]);

	void NumberToPrint(int num);
  


private:

int HW_PINS[16];
void PrintNumber(int NUM, int A, int B, int C, int D);

};

#endif
