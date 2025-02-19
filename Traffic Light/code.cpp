#include <reg51.h>

#define segment P1 // 7-segment display
sbit yellow = P2^0; // Yellow light pin
sbit green = P2^1;  // Green light pin
sbit red = P2^2;    // Red light pin
sbit sensor = P3^2; // LDR sensor input pin

// Array for displaying numbers on a 7-segment display
unsigned char arr[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
unsigned char a;

// Function to initialize external interrupt
void Ext_int_Init() {
    EA = 1;   /* Enable global interrupt */
    EX0 = 1;  /* Enable External Interrupt 0 */
    IT0 = 1;  /* Select Ext. interrupt0 on falling edge */
}

// Delay function
void delay(unsigned int itime) {
    unsigned int i, j;
    for (i = 0; i < itime; i++)
        for (j = 0; j < 1275; j++);
}

// Count down function from a specified number
void count_down(unsigned char start) {
    for (a = start; a > 0; a--) {
        segment = arr[a];  // Display current count
        delay(100);        // Delay between counts
    }
    segment = arr[0];       // Display zero at the end of count
    delay(100);             // Hold zero briefly
}

void main() {
    Ext_int_Init(); // Call interrupt initialization once
    segment = 0xff; // Turn off 7-segment display initially

    while (1) {
        yellow = 0; green = 1; red = 1; // Turn on yellow light only
        delay(100);
        yellow = 1; green = 1; red = 1; // Turn off yellow light only
        delay(100);
    }
}

// External interrupt service routine for traffic light control
void External0_ISR() interrupt 0 {
    segment = arr[0];       // Initialize 7-segment display to zero
    P2 = 0xff;              // Turn off all LEDs initially
    delay(200);             // Brief delay before starting sequence

    yellow = 0; green = 1; red = 1; // Yellow light on
    count_down(5);                  // Count down from 5 for yellow light

    yellow = 1; green = 0; red = 1; // Green light on
    count_down(9);                  // Count down from 9 for green light

    yellow = 1; green = 1; red = 0; // Red light on
    count_down(9);                  // Count down from 9 for red light
}