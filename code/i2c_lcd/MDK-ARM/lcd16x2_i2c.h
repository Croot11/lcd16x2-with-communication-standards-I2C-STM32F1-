#include "stm32f1xx_hal.h" 
#include "main.h"
#include "i2c.h"


#define ADDRESS_I2C 0x4E
#define RS_BIT 0 // Register select bit
#define EN_BIT 2 // Enable bit
#define BL_BIT 3 // Backlight bit
#define D4_BIT 4 // Data 4 bit
#define D5_BIT 5 // Data 5 bit
#define D6_BIT 6 // Data 6 bit
#define D7_BIT 7 // Data 7 bit

extern uint8_t backlight_state;

void lcd_init(void);
void lcd_write_nibble(uint8_t nibble, uint8_t rs);
void lcd_data_write(char data);
void lcd_control_write(char data);
void lcd_send_string(char *str);
void lcd_goto_XY(int row, int col);
void lcd_clear(void);
void lcd_backlight(uint8_t state);

