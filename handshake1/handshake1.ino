#include <SoftwareSerial.h>
SoftwareSerial abc(2,3);
#include <avr/io.h>
#include<avr/interrupt.h>
#define F_CPU 16000000
#define BAUD 9600
#define UBRR ((F_CPU/16/BAUD)-1)                   // setting baud rate
#include<string.h>

char ran[100],rec_data[100];
int i=0;
void setup()
{
  pinMode(3,OUTPUT);
  pinMode(2,INPUT);
  pinMode(LED_BUILDIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  abc.begin(9600);
  uart_init();
  sei();
  fr_api("0", 0x10, 1);
 }
  void loop(){
  
  //fr_api("hello", 0x10, 1);
  abc.println(i);
  
  if (i==21)
    {
      abc.println(' ');
      for (int t=0;t<21;t++)
  {
    abc.print(ran[t],HEX);
    abc.print(' ');
  }
      extract();
      //abc.print(rec_data);
      if(rec_data[0]=='h' && rec_data[1]=='e' && rec_data[2]=='l' && rec_data[3]=='l' && rec_data[4]=='o')
      {
       digitalWrite(LED_BUILTIN,HIGH);
        }
      i=0;
      //print rec_data
      for (int q=0;q<21;q++)
  {
    ran[q]=0;
  }
      }
      
  
  }

//isr for storing data as it comes

 ISR(USART_RX_vect)
 {
  
    ran[i++]=UDR0;
    if(ran[0]!='~')
    {
      i=0;    
    }
    else if(ran[10]==0x25)
    {
      for (int q=0;q<21;q++)
         {
            ran[q]=0;
            }
       i=0;
      }
    //abc.println(i);
   //abc.print(ran[i]);
    }

//extract function
void extract()
{
for(i=15;i<20;i++)
{
rec_data[i-15]= ran[i];

//abc.println(rec_data[i]);

} 
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
  
  for(unsigned int m=0;m<8;m++)
  {
  
    macsum= macsum+ macid[m];
  }

  unsigned int sum1=api + datasum+ fr_id + macsum + 0xFF + 0xFE + br_rad + opt;
  int checksum1=255-(((sum1%16))+((sum1/16)%16)*16);
  unsigned char checksum=checksum1; 


  char frame[500]={dil, len2, len1, api, fr_id};
  int j=5;

  for(int u=0;u<8;u++)
  {
  frame[j]=macid[u];
  j++;
  
  }

  frame[j]=destadd[0];
  frame[++j]=destadd[1];
  
  frame[++j]=br_rad;
    
  frame[++j]=opt;
   
  j++;
  for(int p=0;data[p]!='\0';p++)
  {
  frame[j]=data[p];
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
  
