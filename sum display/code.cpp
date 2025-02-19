#include <reg51.h>
#include <stdlib.h>

#define lcd_data_port P3 /* Define P3 as data port for LCD */
sbit rs = P2^0;         /* Register select pin */
sbit rw = P2^1;         /* Read/Write pin */
sbit en = P2^2;         /* Enable pin */
sbit sw1 = P1^0;        /* Switch for Number 1 */
sbit plus = P1^1;       /* Switch for '+' sign */
sbit sw2 = P1^2;        /* Switch for Number 2 */
sbit enter = P1^3;      /* Enter switch to display sum */
sbit clear = P1^4;      /* Clear display switch */

unsigned char x = 0, y = 0, sum = 0;

void delay(unsigned int count) {
    int i, j;
    for (i = 0; i < count; i++)
        for (j = 0; j < 112; j++);
}

void LCD_Command(unsigned char cmd) {
    lcd_data_port = cmd;
    rs = 0; /* Command register */
    rw = 0; /* Write operation */
    en = 1; delay(1);
    en = 0; delay(5);
}

void LCD_Char(unsigned char char_data) {
    lcd_data_port = char_data;
    rs = 1; /* Data register */
    rw = 0; /* Write operation */
    en = 1; delay(1);
    en = 0; delay(5);
}

void LCD_String(unsigned char *str) {
    int i;
    for (i = 0; str[i] != 0; i++) {
        LCD_Char(str[i]);
    }
}

void LCD_Init(void) {
    delay(20);           /* LCD Power ON Initialization time >15ms */
    LCD_Command(0x38);   /* Initialization of 16X2 LCD in 8bit mode */
    LCD_Command(0x0F);   /* Display ON Cursor Blinking */
    LCD_Command(0x06);   /* Auto Increment cursor */
    LCD_Command(0x01);   /* Clear display */
    LCD_Command(0x80);   /* Cursor at home position */
}

void disp_num(char num) {
    unsigned char UnitDigit = 0;
    unsigned char TenthDigit = 0;
    int numb = (int)num;
   
    TenthDigit = (numb / 10);    // Find tenth place digit
    if (TenthDigit != 0)         // Display only if it's non-zero
        LCD_Char(TenthDigit + 0x30);
       
    UnitDigit = numb - TenthDigit * 10;
    LCD_Char(UnitDigit + 0x30);  // Display unit place digit
    delay(200);
}

void main() {
    LCD_Init(); /* Initialize LCD */
    x = rand() % 50;   /* Initialize random numbers for x and y */
    y = rand() % 50;

    while (1) {
        if (sw1 == 0) {               // If button for number 1 is pressed
            LCD_Command(0x80);        // Set cursor position
            disp_num(x);              // Display number x
            delay(200);
            while (sw1 == 0);         // Wait until button is released
        }
        else if (plus == 0) {         // If button for '+' is pressed
            LCD_Command(0x82);        // Set cursor position
            LCD_Char('+');            // Display '+' sign
            delay(200);
            while (plus == 0);        // Wait until button is released
        }
        else if (sw2 == 0) {          // If button for number 2 is pressed
            LCD_Command(0x83);        // Set cursor position
            disp_num(y);              // Display number y
            delay(200);
            while (sw2 == 0);         // Wait until button is released
        }
        else if (enter == 0) {        // If 'enter' button is pressed
            sum = x + y;              // Calculate the sum
            LCD_Command(0xC0);        // Move to the next line on LCD
            disp_num(sum);            // Display the sum
            delay(200);
            while (enter == 0);       // Wait until button is released
        }
        else if (clear == 0) {        // If 'clear' button is pressed
            LCD_Init();               // Reinitialize the LCD
            x = rand() % 50;          // Generate new random numbers for x and y
            y = rand() % 50;
            delay(200);
            while (clear == 0);       // Wait until button is released
        }
    }
}