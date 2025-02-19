#include<reg52.h>
Sbit LED = P0^0; 
 void main (void)
 { while (1) 
    { LED = 1; 
        Delay ();
         LED = 0;
          Delay (); 
         } } 
    void Delay(void)
     { int j; int i; 
         for (i=0; i<10;i++) {
            for (j=0; j<10000; j++)
             { } 
            } 
        }