#include <reg51.h>

#define lcd_data_port P3       /* Define P3 as data port for LCD */
sbit rs = P2^0;                /* Register select pin */
sbit rw = P2^1;                /* Read/Write pin */
sbit en = P2^2;                /* Enable pin */

void delay(unsigned int count) /* Function to provide delay Approx 1ms */
{
    int i, j;
    for(i = 0; i < count; i++)
        for(j = 0; j < 112; j++);
}

void LCD_Command(unsigned char cmd) /* Send a command to the LCD */
{
    lcd_data_port = cmd;
    rs = 0;            /* Command register (rs = 0 for command) */
    rw = 0;            /* Write operation (rw = 0 for write) */
    en = 1;
    delay(1);          /* Small delay for enabling the command */
    en = 0;
    delay(5);          /* Additional delay to let the command execute */
}

void LCD_Char(unsigned char char_data) /* Write a character to the LCD */
{
    lcd_data_port = char_data;
    rs = 1;            /* Data register (rs = 1 for data) */
    rw = 0;            /* Write operation */
    en = 1;
    delay(1);
    en = 0;
    delay(5);
}

void LCD_String(unsigned char *str) /* Write a string to the LCD */
{
    int i;
    for(i = 0; str[i] != 0; i++) /* Write each character till NULL */
    {
        LCD_Char(str[i]);
    }
}

void LCD_Init(void) /* Initialize the LCD */
{
    delay(20);           /* LCD Power ON Initialization time >15ms */
    LCD_Command(0x38);   /* 8-bit mode, 2 lines, 5x7 font */
    LCD_Command(0x0C);   /* Display ON, Cursor OFF */
    LCD_Command(0x06);   /* Auto Increment cursor */
    LCD_Command(0x01);   /* Clear display */
    LCD_Command(0x80);   /* Set cursor at home position */
}

void main()
{
    LCD_Init();          /* Initialize LCD */
    LCD_String("JIIT");  /* Write string on the first line */
    while(1);            /* Infinite loop to hold display */
}