#include "lcd16x2_i2c.h"

uint8_t backlight_state = 1;  // Ð?nh nghia và kh?i t?o



void lcd_init(void)
{
	HAL_Delay(50);
	lcd_control_write(0x03);
	HAL_Delay(2);
	lcd_control_write(0x03);
	HAL_Delay(2);
	lcd_control_write(0x03);
	HAL_Delay(2);
	lcd_control_write(0x02);
	HAL_Delay(2);
	lcd_control_write(0x28);
	lcd_control_write(0x0C);
	lcd_control_write(0x06);
	lcd_control_write(0x01);
	HAL_Delay(2);
	
}
void lcd_write_nibble(uint8_t nibble, uint8_t rs)
{
	uint8_t data = nibble << D4_BIT;
	data |= rs << RS_BIT;
	data |= backlight_state << BL_BIT;
	data |= 1 << EN_BIT;
	
	HAL_I2C_Master_Transmit(&hi2c2, ADDRESS_I2C, &data, 1, 100);
	HAL_Delay(1);
	data &= ~(1 << EN_BIT);
	HAL_I2C_Master_Transmit(&hi2c2, ADDRESS_I2C, &data, 1, 100);
}


void lcd_data_write(char data)
{
	uint8_t high_byte = data >> 4;
	uint8_t low_byte  = data & 0x0F;
	
	lcd_write_nibble(high_byte, 1);
	lcd_write_nibble(low_byte, 1);
	if(data == 0x01 || data == 0x02)
	{
	HAL_Delay(2);
	}
	
	/*
	char data_h, data_l;
	uint8_t data_s[4];
	
	data_h = data & 0xF0;
	data_l = (data << 4) & 0xF0;
	
	//write data 
	data_s[0] = data_h | 0x0D;
	data_s[1] = data_h | 0x09;
	data_s[2] = data_l | 0x0D;
	data_s[3] = data_l | 0x09;
	HAL_I2C_Master_Transmit(&hi2c2, ADDRESS_I2C, (uint8_t *) data_s, 4, 100);
	*/
}

void lcd_control_write(char data)
{
	uint8_t high_byte = data >> 4;
	uint8_t low_byte  = data & 0x0F;
	
	lcd_write_nibble(high_byte, 0);
	lcd_write_nibble(low_byte, 0);
	if(data == 0x01 || data == 0x02)
	{
	HAL_Delay(2);
	}
	
	/*
	char data_h, data_l;
	uint8_t data_s[4];
	
	data_h = data & 0xF0;
	data_l = (data << 4) & 0xF0;
	
	//write data
	data_s[0] = data_h | 0x0C;
	data_s[1] = data_h | 0x08;
	data_s[2] = data_l | 0x0C;
	data_s[3] = data_l | 0x08;
	HAL_I2C_Master_Transmit(&hi2c2, ADDRESS_I2C, (uint8_t *) data_s, 4, 100);
	*/
}

void lcd_send_string(char *str)
{
	while(*str) lcd_data_write(*str++);
}

void lcd_goto_XY(int row, int column)
{
	uint8_t address;
    switch (row) {
        case 1:
            address = 0x00;
            break;
        case 2:
            address = 0x40;
            break;
        default:
            address = 0x00;
    }
    address += column - 1;
	lcd_control_write(0x80 | address);
	
}

void lcd_backlight(uint8_t state)
{
	if(state == 1)
	{
		backlight_state = 1;
	} else {
		backlight_state = 0;
	}
}

void lcd_clear(void)
{
	lcd_control_write(0x01);
	HAL_Delay(2);
}

