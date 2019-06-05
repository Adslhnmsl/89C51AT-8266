#include <reg52.h> 
#include <intrins.h>
#include<stdio.h>
#include<string.h>
#define uchar  unsigned char
#define uint  unsigned int
/**********************8266���Ӷ˿������ִ�***********************************/ 
code uchar a[]="AT+CWMODE=3";
code uchar b[]="AT+RST";
code uchar c[]="AT+CIPMUX=0";
code uchar d[]="AT+CWJAP=\"Needle\",\"ldgzs105\"";
code uchar e[]="AT+CIPSTART=\"TCP\",\"192.168.3.20\",10800";
code uchar f[]="AT+CIPSEND=18";
/******************************�������***********************************/ 
unsigned char  g[18];
unsigned char  h[4];
int people,up,down;
int station,No;
int day,time; 
uint panding; 				//������ʼ��
/**********************�˿ڶ���***********************************/
sbit 	KEY1 	= 	P2 ^ 2; //���ô�������һ������P1.5
sbit 	KEY2 	= 	P2 ^ 1; //���ô������ڶ�������P1.6
sbit    led0    =   P1 ^ 0;
sbit    led1	=	P1 ^ 1;
sbit    zhong=P3^2;
/**********************��������***********************************/ 
void update_disbuf();
void Delayms(uint j);
void UART_SendData(uchar dat);
void UART_SendString(uchar *p);
void UART_Init(void);
/**********************������*************************************/ 
void main(void)
{	int i=2;
	led0=1;
	UART_Init();
	IE=0X81; 	//�����жϺ����ж�0
	IT0=1;
	P0=0xff;		//��ʼ��io��
	P1=0x00;
	EA=1;
    IT0=0;
    EX0=1;
	people=0;
	up=0;
    down=0;
	No=55;
	station=1;
	day=327;
	time=1948;

		UART_SendString(a);	   //�����ַ���
		UART_SendData('\r');   //�س�
		UART_SendData('\n');   //����
		Delayms(500);		   //��ʱ		
		UART_SendString(b);	   //�����ַ���
		UART_SendData('\r');   //�س�
		UART_SendData('\n');   //����
		Delayms(500);		   //��ʱ		
		UART_SendString(c);	   //�����ַ���
		UART_SendData('\r');   //�س�
		UART_SendData('\n');   //����
		Delayms(500);		   //��ʱ	
		UART_SendString(d);	   //�����ַ���
		UART_SendData('\r');   //�س�
		UART_SendData('\n');   //����
		Delayms(5000);		   //��ʱ
		UART_SendString(e);	   //�����ַ���
		UART_SendData('\r');   //�س�
		UART_SendData('\n');   //����
		Delayms(5000);		   //��ʱ
/**********************�����߼������*************************************/ 		
	while(1)
	{	
		if(KEY1 == 0&&KEY2 == 1)
			while(1)
			{
				if(KEY1 == 0&&KEY2 == 0)
				{
					up++;
					led0=~led0;	
					break;
				}
				if(KEY1 == 1&&KEY2 == 1)
	 	   		break;
			}
		if(KEY1 == 0&&KEY2 == 0)
			while(1)
			{
				if(KEY1 == 0&&KEY2 == 1)
				{
					down++;	  
					led1=~led1;	
					break;
				}
				if(KEY1 == 1&&KEY2 == 0)
	 	 	 	break;
			}
	}
}	

/**********************�ж��Ӻ���*************************************/ 
void zhongduan() interrupt 0
{
	int zong;
	if(zhong==0)
	{
        people=people+up-down;
		if(people<0)people=0;//��ֹ��������0
        zong=up*100+down;//����ǰ�������ݼ���
        sprintf(g, "%04d%04d%02d%04d",day,time,people,zong);
		sprintf(h, "%02d%02d",No,station);//���������ƴ��Ϊһ���ִ�������
		strcat(g,h);		   //��������ƴ����һ��
		UART_SendString(f);	   //�����ַ���
		UART_SendData('\r');   //�س�
		UART_SendData('\n');   //����
		Delayms(500);		   //��ʱ
		UART_SendString(g);	   //�����ַ���
		UART_SendData('\r');   //�س�
		UART_SendData('\n');   //����
		Delayms(500);		   //��ʱ
		station++;
		if(station==11)		  //�ж�վ��
		station=1;
		up=0;
		down=0;
		time++;
	}
}
/**********************�ӳ��ӳ���*************************************/
void Delayms(int n)
{
     int i,j;
     for(i=0;i<=n;i++)
     for(j=0;j<=115;j++);
}
/**********************�����ַ��Ӻ���*************************************/
void UART_SendString(uchar *p)
{
  while(*p!='\0')
  {
   UART_SendData(*p++);
  }

}
/**********************�������ݺ���*************************************/
void UART_SendData(uchar dat)
{
	SBUF=dat;      //��������
	while(TI==0);  //�ж��Ƿ�����
	TI=0;	
}
/**********************��ʼ������*************************************/
void UART_Init(void)
{
	SCON=0x50;
    TMOD=0x20;				   
	PCON=0x00;
    TH1 =0xfd;
	TL1 =0xfd;  //Ԥ�ó�ֵ���貨����Ϊ9600
	TR1 =1;	
   	ES  =1;
	EA  =1;
    IT0 =0;
    EX0 =1;		//���ж�
}
            