#include<reg51.h>
#define segment P3
sbit button1 = P1^0;
sbit button2 = P1^1;
sbit button3 = P1^2;
sbit button4 = P1^3;
sbit button5 = P1^4;
sbit button6 = P1^5;
sbit button7 = P1^6;
sbit button8 = P1^7;
unsigned char arr[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char a;
void delay (unsigned int itime)
{
unsigned int i, j;
for (i=0;i<itime;i++)
for (j=0;j<1275;j++);
}
void main(void){
while(1)
{
segment = arr[0]; // send zero
if (button1 == 0)
{
segment= arr[1];
delay(100);
}
else if (button2 == 0)
{
segment= arr[2];
delay(100);
}
else if (button3 == 0)
{
segment= arr[3];
delay(100);
}
else if (button4 == 0)
{
segment= arr[4];
delay(100);
}
else if (button5 == 0)
{
segment= arr[5];
delay(100);
}
else if (button6 == 0)
{
segment= arr[6];
delay(100);
}
else if (button7 == 0)
{
segment= arr[7];
delay(100);
}
else if (button8 == 0)
{segment= arr[8];
delay(100);
}
else{
segment= arr[0];
delay(100);
}}
}
