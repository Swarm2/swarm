#include <SoftwareSerial.h>
SoftwareSerial abc(2,3);

#include <avr/io.h>
#include<avr/interrupt.h>
#define F_CPU 16000000
#define BAUD 9600
#define UBRR ((F_CPU/16/BAUD)-1)                   // setting baud rate
#include<string.h>

char ran[100],rec_data[100],p;
int i=0;
int t=0;
void setup()
{
  pinMode(3,OUTPUT);
  pinMode(2,INPUT);
  abc.begin(9600);
  uart_init();
  sei();
  
  //int t;
  //fr_api("hello", 0x10, 1);
 }
  void loop(){
  
  //fr_api("hello", 0x10, 1);
    //abc.println("mask");
  //abc.println("mask");
  if (i==17)
    {
      abc.println("in");
      extract();
      
      if(p=='0'){
        
        fr_api("hello", 0x10, 1);
       //delay(50);
        abc.println("vbb");
        /*delay (5);
        digitalWrite(LED_BUILTIN,HIGH);
        delay(5);
        digitalWrite(LED_BUILTIN,LOW);*/
       // abc.println("stop");
        //abc.print(i);
       //i=0;
        
         
      }
      for( t=0;t<17;t++)
    {
    //abc.print("chutiya");
    //delay(1000);
    ran[t] = 0;
    }
    i=0;

      //print rec_data
     }
  
  }

//isr for storing data as it comes

 ISR(USART_RX_vect)
 {
  
    ran[i++]=UDR0;
    if(ran[0]!='~')
    {i=0;}
    //abc.println(i);
   //abc.print(ran[i]);
    }

//extract function
void extract()
{
  p=ran[15];
/*for(i=15;i<20;i++)
{
rec_data[i-15]= ran[i];

//abc.println(rec_data[i]);

} */
}
//store function
/*void store()
{ 
  
//assuming we are getting 21 byte
    ran[i]=UDR0;
    abc.print(ran[i]);
    i++;

}*/
//uart_init

void uart_init(){
  DDRD |= 0b01000000;
  UBRR0H |= (UBRR>>8);                            // to use all the 16bits we shifted 8 bits
  UBRR0L |= UBRR;                                 //
  UCSR0B |= (1<<TXEN0)|(1<<RXEN0)| (1<<RXCIE0);              // enable Rx, Tx
  UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01) ;   // setting character size(first 2); last one is for 2 stop bits
  
}



//fr_api function
void fr_api(const char data[100], char api ,int xbee)
{
   
  unsigned char dil=0x7E;
  unsigned int sum= 0x000E + strlen(data);
  int len1=(((sum%16))+((sum/16)%16)*16);
  int len2=((((sum/256)%16))+((sum/4096)%16)*16);
  unsigned char fr_id= 0x01;
  unsigned char macid[8] = {0x00, 0x13, 0xA2, 0x00, 0x41, 0x63, 0x0CB, 0xF7};
  if(xbee==2)
  {
   //macid[5] = 0xDC;
   //macid[6] = 0x85;
   macid[7] = 0xAB;
  }
  unsigned char destadd[2];
   destadd[0]=0xFF;
   destadd[1]=0xFE;
  unsigned char br_rad= 0x00;
  unsigned char opt= 0x00;
  unsigned int datasum=0;
  unsigned char macsum =0;

  for(unsigned int n=0;n<strlen(data);n++)
  {
    datasum= datasum+ data[n];
  }
  
  for(unsigned int n=0;n<8;n++)
  {
  
    macsum= macsum+ macid[n];
  }

  unsigned int sum1=api + datasum+ fr_id + macsum + 0xFF + 0xFE + br_rad + opt;
  int checksum1=255-(((sum1%16))+((sum1/16)%16)*16);
  unsigned char checksum=checksum1; 


  char frame[500]={dil, len2, len1, api, fr_id};
  int j=5;

  for(int l=0;l<8;l++)
  {
  frame[j]=macid[l];
  j++;
  
  }

  frame[j]=destadd[0];
  frame[++j]=destadd[1];
  
  frame[++j]=br_rad;
    
  frame[++j] = opt;
  j++;   

  for(int f =0;data[f]!='\0';f++)
  {
  frame[j]= data[f];
  j++;
  }

  frame[j]=checksum;
  for(int k=0;k<=j;k++)
  {
  while((!(UCSR0A & (1<<UDRE0))))
  ; 
    UDR0= frame[k];
    }
}
  
