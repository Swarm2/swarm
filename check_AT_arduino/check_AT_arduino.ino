#include <avr/io.h>
#define F_CPU 16000000
#define BAUD 9600
#define UBRR ((F_CPU/16/BAUD)-1)                     // setting baud rate

void setup()
{
  UBRR0H |= (UBRR>>8);                               // to use all the 16bits we shifted 8 bits
  UBRR0L |= UBRR;                                    //
  UCSR0B |= (1<<TXEN0) | (1<<RXEN0);                 // enable Rx, Tx
  UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01) | (1<<USBS0);   // setting character size(first 2); last one is for 2 stop bits
    UCSR0C &= ~((1<<UMSEL01)|(1<<UMSEL00)|(1<<UCSZ02));
    char *sendstr = "+++";
    char *recstr;
    int i=0;
    for(i=0;i<=2;i++)
    {
      UDR0=*(sendstr+i);
      }
    while(!(UCSR0A & (1<<RXC0)))               // wait for data to come
    ;
    do
    {
     
      //Serial.println("Ek character read kar liya");
      *(recstr)=UDR0;
      while(!(UCSR0A & (1<<RXC0)))
      ;
    }while(*(recstr++) != '\r');
    *(recstr)=*(recstr-2);
}
  
char *sendstr = "AT\r";
  char *recstr;
 
 void loop()
  {
     

    while(!(UCSR0A & (1<<UDRE0)))                // checking if it is ready to recive or not.(empty or not)
    ;
                            
    PORTB = (1<<5);
    do
    {
     
      //Serial.println("Ek character read kar liya");
      UDR0 = *(sendstr);
      while(!(UCSR0A & (1<<UDRE0)))
      ;
      PORTB = (1<<6);
    }while(*(sendstr++) != '\r');



    PORTB |= (1<<3);
    while(!(UCSR0A & (1<<RXC0)))               // wait for data to come
    ;
    do
    {
     PORTB |= (1<<4);
      //Serial.println("Ek character read kar liya");
      *(recstr)=UDR0;
      while(!(UCSR0A & (1<<RXC0)))
      ;
    }while(*(recstr++) != '\r');

    PORTB |= (1<<2);
      if(*(recstr)=="O" &&*(recstr+1)=="K" && *(recstr+2)=="\r")
      {
        PORTC |= (1<<0);
      
        }
      else if(*(recstr)=="O" &&*(recstr+1)=="K" && *(recstr+2)=="K"&&  *(recstr+2)=="\r")
      {
        PORTB |= (1<<0);
      
        }
     else
     {
        PORTB |= (1<<1);
      
        
      }
   /* if(UDR0==0b00001111)
    {
      PORTC = (1<<0);
      _delay_ms(100);
      PORTC = (0<<0);
      
    }*/
    
  }
