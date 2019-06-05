#include <reg52.h> 
#include <intrins.h>
#include<stdio.h>
#include<string.h>
#define uchar  unsigned char
#define uint  unsigned int
/**********************8266连接端口所需字串***********************************/ 
code uchar a[]="AT+CWMODE=3";
code uchar b[]="AT+RST";
code uchar c[]="AT+CIPMUX=0";
code uchar d[]="AT+CWJAP=\"Needle\",\"ldgzs105\"";
code uchar e[]="AT+CIPSTART=\"TCP\",\"192.168.3.20\",10800";
code uchar f[]="AT+CIPSEND=18";
/******************************定义变量***********************************/ 
unsigned char  g[18];
unsigned char  h[4];
int people,up,down;
int station,No;
int day,time; 
uint panding; 				//计数初始化
/**********************端口定义***********************************/
sbit 	KEY1 	= 	P2 ^ 2; //设置传感器第一个接在P1.5
sbit 	KEY2 	= 	P2 ^ 1; //设置传感器第二个接在P1.6
sbit    led0    =   P1 ^ 0;
sbit    led1	=	P1 ^ 1;
sbit    zhong=P3^2;
/**********************函数定义***********************************/ 
void update_disbuf();
void Delayms(uint j);
void UART_SendData(uchar dat);
void UART_SendString(uchar *p);
void UART_Init(void);
/**********************主函数*************************************/ 
void main(void)
{	int i=2;
	led0=1;
	UART_Init();
	IE=0X81; 	//开总中断和外中断0
	IT0=1;
	P0=0xff;		//初始化io口
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

		UART_SendString(a);	   //发送字符串
		UART_SendData('\r');   //回车
		UART_SendData('\n');   //换行
		Delayms(500);		   //延时		
		UART_SendString(b);	   //发送字符串
		UART_SendData('\r');   //回车
		UART_SendData('\n');   //换行
		Delayms(500);		   //延时		
		UART_SendString(c);	   //发送字符串
		UART_SendData('\r');   //回车
		UART_SendData('\n');   //换行
		Delayms(500);		   //延时	
		UART_SendString(d);	   //发送字符串
		UART_SendData('\r');   //回车
		UART_SendData('\n');   //换行
		Delayms(5000);		   //延时
		UART_SendString(e);	   //发送字符串
		UART_SendData('\r');   //回车
		UART_SendData('\n');   //换行
		Delayms(5000);		   //延时
/**********************红外线监测人数*************************************/ 		
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

/**********************中断子函数*************************************/ 
void zhongduan() interrupt 0
{
	int zong;
	if(zhong==0)
	{
        people=people+up-down;
		if(people<0)people=0;//防止人数低于0
        zong=up*100+down;//将当前人数数据计算
        sprintf(g, "%04d%04d%02d%04d",day,time,people,zong);
		sprintf(h, "%02d%02d",No,station);//将多段数据拼接为一个字串符发送
		strcat(g,h);		   //数据整理并拼接在一起
		UART_SendString(f);	   //发送字符串
		UART_SendData('\r');   //回车
		UART_SendData('\n');   //换行
		Delayms(500);		   //延时
		UART_SendString(g);	   //发送字符串
		UART_SendData('\r');   //回车
		UART_SendData('\n');   //换行
		Delayms(500);		   //延时
		station++;
		if(station==11)		  //判断站数
		station=1;
		up=0;
		down=0;
		time++;
	}
}
/**********************延迟子程序*************************************/
void Delayms(int n)
{
     int i,j;
     for(i=0;i<=n;i++)
     for(j=0;j<=115;j++);
}
/**********************发送字符子函数*************************************/
void UART_SendString(uchar *p)
{
  while(*p!='\0')
  {
   UART_SendData(*p++);
  }

}
/**********************发送数据函数*************************************/
void UART_SendData(uchar dat)
{
	SBUF=dat;      //发送数据
	while(TI==0);  //判断是否发送完
	TI=0;	
}
/**********************初始化函数*************************************/
void UART_Init(void)
{
	SCON=0x50;
    TMOD=0x20;				   
	PCON=0x00;
    TH1 =0xfd;
	TL1 =0xfd;  //预置初值，设波特率为9600
	TR1 =1;	
   	ES  =1;
	EA  =1;
    IT0 =0;
    EX0 =1;		//开中断
}
            