
#include "LCD.h"


#include "stm32f1xx_hal.h"


#define RS_Pin GPIO_PIN_1
#define RS_GPIO_Port GPIOA
#define RW_Pin GPIO_PIN_2
#define RW_GPIO_Port GPIOA
#define EN_Pin GPIO_PIN_3
#define EN_GPIO_Port GPIOA
#define D4_Pin GPIO_PIN_4
#define D4_GPIO_Port GPIOA
#define D5_Pin GPIO_PIN_5
#define D5_GPIO_Port GPIOA
#define D6_Pin GPIO_PIN_6
#define D6_GPIO_Port GPIOA
#define D7_Pin GPIO_PIN_7
#define D7_GPIO_Port GPIOA



void delay (uint16_t us)


{
	int oo = 0;

	while (oo < us) {
		oo++;
}
	}



void send_to_lcd (char data, int rs)
{
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, rs);


	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, ((data>>3)&0x01));
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, ((data>>2)&0x01));
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, ((data>>1)&0x01));
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, ((data>>0)&0x01));


	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 1);
	HAL_Delay(10);
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 0);
	HAL_Delay(10);
}

void lcd_send_cmd (char cmd)
{
    char datatosend;


    datatosend = ((cmd>>4)&0x0f);
    send_to_lcd(datatosend,0);


    datatosend = ((cmd)&0x0f);
	send_to_lcd(datatosend, 0);
}

void lcd_send_data (char data)
{
	char datatosend;


	datatosend = ((data>>4)&0x0f);
	send_to_lcd(datatosend, 1);


	datatosend = ((data)&0x0f);
	send_to_lcd(datatosend, 1);
}

void lcd_clear (void)
{
	lcd_send_cmd(0x01);
	HAL_Delay(2);
}

void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    lcd_send_cmd (col);
}


void lcd_init (void)
{

	HAL_Delay(10);
	lcd_send_cmd (0x02);
	lcd_send_cmd (0x28);
	lcd_send_cmd (0x08);
	lcd_send_cmd (0x01);
	lcd_send_cmd (0x06);
	lcd_send_cmd (0x0C);
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}


