# Nixie-Clock

This is the code used with custom build PCB to create a NIXIE Clock. 
The board has exposed pins on all connection pins and can easily be modified.

To use the tx and rx pins the below lines must be commented out.

C:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\leonardo

```
#define TX_RX_LED_INIT//	DDRD |= (1<<5), DDRB |= (1<<0)
#define TXLED0//			PORTD |= (1<<5)
#define TXLED1//			PORTD &= ~(1<<5)
#define RXLED0//			PORTB |= (1<<0)
#define RXLED1//			PORTB &= ~(1<<0)
```

The board uses:

- Micro Controller - ATMEGA32U4-AU
- Real Time Clock - DS3231SN#T_R

