/**
serial 2 hd44780 lcd using attiny2313

@file		main.c
@author		Matej Kogovsek
@copyright	GPL v2
*/

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "lcd.h"
#include "serque.h"
#include "i2c_usi.h"
#include "hwdefs.h"

// ------------------------------------------------------------------

uint8_t rxbuf[16];
uint8_t txbuf[16];
uint8_t intf_i2c;
uint8_t adr_ = 0x4c;

// ------------------------------------------------------------------

uint8_t intf_getc(uint8_t* const d)
{
	if( intf_i2c ) {
		return i2c_usi_getc(d);
	} else {
		return ser_getc(0, d);
	}
}

// ------------------------------------------------------------------

int main(void)
{
	wdt_reset();
	wdt_enable(WDTO_2S);

	ACSR |= _BV(ACD);         			// analog comparator poweroff

	DDR(LCD_E_PORT) |= _BV(LCD_E_PIN);	// make LCD E pin idle asap
	LCD_E_PORT &= ~_BV(LCD_E_PIN);

	INTF_SEL_PORT |= _BV(INTF_SEL_PIN);	// pullup on intf select pin
	_delay_us(10);
	intf_i2c = PIN(INTF_SEL_PORT) & _BV(INTF_SEL_PIN);
	if( intf_i2c ) {
		i2c_usi_init(adr_, txbuf, sizeof(txbuf), rxbuf, sizeof(rxbuf));
	} else {
		ser_init(0, BAUD_9600, txbuf, sizeof(txbuf), rxbuf, sizeof(rxbuf));
	}

	_delay_ms(300);
	lcd_init(0);

	uint8_t cl = 1;			// current LCD line

	sei();

	while( 1 ) {
		wdt_reset();
		uint8_t c;
		if( intf_getc(&c) ) {
			if( c < ' ' ) {
				switch( c ) {
					case 1:
					case 2:
					case 3:
					case 4:
						lcd_line(c);
						cl = c;
						break;
					case 5:
						lcd_init(0);
						cl = 1;
						break;
					case 6:
						lcd_clear();
						cl = 1;
						break;
					case 7:
					case 8:
						lcd_bl(c == 7);
						break;
					case 0x0d:	// cr
						lcd_endl();
						break;
					case 0x0a:	// lf
						lcd_line(cl);
						break;
				}
			} else {
				lcd_putc(c);
			}
		}
	}
}
