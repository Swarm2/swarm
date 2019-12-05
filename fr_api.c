void fr_api(const char data[100], char api ,int xbee)
{
 	
	unsigned char dil=0x7E;
	unsigned int sum= 0x000E + strlen(data);
	int len1=(((sum%16))+((sum/16)%16)*16);
	int len2=((((sum/256)%16))+((sum/4096)%16)*16);
 	unsigned char fr_id= 0x01;
	unsigned char macid[8] = {0x00, 0x13, 0xA2, 0x00, 0x40, 0xA2, 0x09, 0xA3};
	if(xbee==2)
	{
	 macid[5] = 0xDC;
	 macid[6] = 0x85;
	 macid[7] = 0x16;
	}
	unsigned char destadd[2];
	 destadd[0]=0xFF;
	 destadd[1]=0xFE;
	unsigned char br_rad= 0x00;
	unsigned char opt= 0x00;
	unsigned int datasum=0;
	unsigned char macsum =0;

	for(unsigned int i=0;i<strlen(data);i++)
	{
		datasum= datasum+ data[i];
	}
	
	for(unsigned int i=0;i<8;i++)
	{
	
		macsum= macsum+ macid[i];
	}

	unsigned int sum1=api + datasum+ fr_id + macsum + 0xFF + 0xFE + br_rad + opt;
	int checksum1=255-(((sum1%16))+((sum1/16)%16)*16);
	unsigned char checksum=checksum1;	


	char frame[500]={dil, len2, len1, api, fr_id};
	int j=5;

 	for(int i=0;i<8;i++)
	{
  frame[j]=macid[i];
  j++;
  
	}

	frame[j]=destadd[0];
  frame[++j]=destadd[1];
  
	frame[++j]=br_rad;
    
	frame[++j]=opt;
   
	j++;
	for(int i=0;data[i]!='\0';i++)
	{
	frame[j]=data[i];
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

