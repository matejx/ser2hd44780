#ifndef MAT_HWDEFS_H
#define MAT_HWDEFS_H
	#define DDR(x) (*(&x - 1))
	#define PIN(x) (*(&x - 2))

	#define INTF_SEL_PORT PORTB
	#define INTF_SEL_PIN 4

	#define LCD_RS_PORT PORTD
	#define LCD_RS_PIN 5

	#define LCD_RW_PORT PORTD
	#define LCD_RW_PIN 3

	#define LCD_E_PORT PORTD
	#define LCD_E_PIN 4

	#define LCD_D0_PORT PORTA
	#define LCD_D0_BIT 0

	#define LCD_D1_PORT PORTD
	#define LCD_D1_BIT 2

	#define LCD_D2_PORT PORTD
	#define LCD_D2_BIT 6

	#define LCD_D3_PORT PORTA
	#define LCD_D3_BIT 1

	#define LCD_D4_PORT PORTB
	#define LCD_D4_BIT 1

	#define LCD_D5_PORT PORTB
	#define LCD_D5_BIT 0

	#define LCD_D6_PORT PORTB
	#define LCD_D6_BIT 3

	#define LCD_D7_PORT PORTB
	#define LCD_D7_BIT 2

	#define LCD_BL_PORT PORTB
	#define LCD_BL_BIT 6

	#define PORT_USI PORTB
	#define PORT_USI_SCL 7
	#define PORT_USI_SDA 5
#endif
