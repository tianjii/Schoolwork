/*  Names: Skylar Sang, Matthew Rhie, WangKun Zhang
    Section: 4B
    Date: 10/6/17
    File name: lab2.c
    Description: LAB2
*/
/*
 This program demonstrates a game where we use A/D conversion to play a game
*/

#include <c8051_SDCC.h>// include files. This file is available online
#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
void Port_Init(void);     // Initialize ports for input and output
void Timer_Init(void);     // Initialize Timer 0
void Interrupt_Init(void); //Initialize interrupts
void ADC_Init(void);
unsigned char read_AD_input(unsigned char n); //A/D Conversion
unsigned char random(void);
void mode_1(void);
void mode_2(void);


//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
__sbit __at 0xB3 BILED0;
__sbit __at 0xB4 BILED1;
__sbit __at 0xB0 PB3;
__sbit __at 0xB1 PB2;
__sbit __at 0xA1 PB1;
__sbit __at 0xA2 PB0;

__sbit __at 0xA0 SS;
__sbit __at 0xB6 LED0;
__sbit __at 0xB2 LED1;
__sbit __at 0xB5 LED2;
__sbit __at 0xB7 BZ1;

int input;
int counts;
int score;
int round;
int binary;
int number;
int result=0;
int wait_time;
float round_time;
int pts;
float calc;

/* This program demonstrates how to perform an A/D Conversion */
void main(void)
{
 	Sys_Init(); /* Initialize the C8051 board */
 	Port_Init(); /* Configure P1.0 for analog input */
 	ADC_Init(); /* Initialize A/D conversion */
	Timer_Init(); /*Initialize Timer 0*/
	Interrupt_Init(); //Initialize Timer 0 Interrupts
	putchar(' ');
 	while (1)
 	{
 		printf("Slide switch left or right to select mode 1 or 2 \r\nPress the leftmost button to start \r\n");
		while (PB3);
		result = read_AD_input(0);
		printf("result:  %d\r\n", result);

		round_time = result*4.5/255;//time in sec greater than 0.5
		round_time = round_time+0.5;
		wait_time = round_time*338;
		printf("Wait Time:  %d counts\r\n", wait_time);
		counts = 0;
		TR0 = 1;
		BZ1 = 0;
		while (counts < 169); //sound buzzer
		BZ1 = 1;

		if(SS) {
			mode_1();
		}
		else if(!SS) {
			mode_2();
		}



	}
}
void Port_Init(void)
{

	P1MDIN &= ~0x01; /* Set P1.0 for analog input */
	P1MDOUT &= ~0x01; /* Set P1.0 to open drain */
	P1 |= 0x01; /* Send logic 1 to input pin P1.0 */
	P2MDOUT &= ~0x07;
	P2 |= 0x07;
	P3MDOUT = ~0x03;
	P3 |= 0x03;
}
void ADC_Init(void)
{
	REF0CN = 0x03; /* Set Vref to use internal reference voltage (2.4
V) */
	ADC1CN = 0x80; /* Enable A/D converter (ADC1) */
	ADC1CF |= 0x01; /* Set A/D converter gain to 1 */
}
void Timer_Init(void)
{

    CKCON |= 0x08;  // Timer0 uses SYSCLK as source
    TMOD &= 0xF0;   // clear the 4 least significant bits
    TMOD |= 01;   // Timer0 in mode 1
    TR0 = 0;           // Stop Timer0
    TMR0 = 0;  // Clear high & low byte of T0
}
void Interrupt_Init(void)
{
    IE |= 0x02;      // enable Timer0 Interrupt request (by masking)
    EA = 1;       // enable global interrupts (by sbit)
}
void Timer0_ISR(void) __interrupt 1
{
// add interrupt code here, in this lab, the code will increment the
// global variable 'counts'
	counts++;
}
unsigned char read_AD_input(unsigned char n)
{
 	AMX1SL = n; /* Set P1.n as the analog input for ADC1 */
 	ADC1CN = ADC1CN & ~0x20; /* Clear the “Conversion Completed” flag */
 	ADC1CN = ADC1CN | 0x10; /* Initiate A/D conversion */
 	while ((ADC1CN & 0x20) == 0x00); /* Wait for conversion to complete */
 	return ADC1; /* Return digital value in ADC1 register */
}

//MODE 1
void mode_1(void) {
	printf("Binary lights up. Enter Hex. Repeat\r\n");
	score = 0;
	round = 0;;
	while (round < 8) {
	//Execute round
		LED0 = 1;
		LED1 = 1;
		LED2 = 1;
		counts = 0;
		TMR0 = 0;
		TR0 = 1;
		while (counts < 169);
		pts = 0;
		number = random();
		binary = number;
		if (binary >= 4) {
			LED2 = 0;
			binary-=4;
		}
		if (binary >= 2) {
			LED1 = 0;
			binary-=2;
		}
		if (binary >= 1) {
			LED0 = 0;
		}
		counts = 0;
		TMR0 = 0;
		input = getchar()-48;
		if (input == number) {
			calc = ((float)counts/wait_time);
			if (calc <= 1.0) {
				pts = 10-(10*calc);
			}
			else {
				pts = 0;
			}
			score+=pts;
			printf("\r\npoints: %d\r\n", pts);
			printf("score: %d\r\n", score);
			BILED0 = 1;
			BILED1 = 0;

		}
		else {
			printf("\r\npoints: %d\r\n", pts);
			printf("score: %d\r\n", score);
			BILED0 = 0;
			BILED1 = 1;

		}

		counts = 0;
		TMR0 = 0;
		while (counts < 169);
		BILED0 = 1;
		BILED1 = 1;
		TR0 = 0;
		round++;

	}

	counts = 0;
	TR0 = 1;
	LED0 = 1;
	LED1 = 1;
	LED2 = 1;

	printf("Final Score: %d\r\n", score);
	BZ1 = 0;
	while (counts < 169);
	BZ1 = 1;
	TR0 = 0;



}
//MODE 2
void mode_2(void) {
	printf("Hex shows onscreen, press buttons for binary. Repeat.\r\n");
	score = 0;
	round = 0;
    //Execute Round
	while (round < 8) {
		LED0 = 1;
		LED1 = 1;
		LED2 = 1;
		binary = 0;
		number = random();
		printf("%d\r\n", number);
		counts = 0;
		TMR0 = 0;
		TR0 = 1;
		while (counts < wait_time) {
			if (!PB0)
			{
				LED0 = 0;
			}
			if (!PB1)
			{
				LED1 = 0;
			}
			if (!PB2)
			{
				LED2 = 0;
			}
		}
		if (LED2== 0) {
			binary+=4;
		}
		if (LED1 == 0) {
			binary+=2;
		}
		if (LED0 == 0) {
			binary+=1;
		}
		if (binary == number) {
			BILED0 = 1;
			BILED1 = 0;
			score+=10;
			printf("\r\npoints: 10\r\n", pts);
			printf("score: %d\r\n", score);
		}
		else {
			printf("\r\npoints: 0\r\n", pts);
			printf("score: %d\r\n", score);
			BILED0 = 0;
			BILED1 = 1;
		}
		counts = 0;
		TMR0 = 0;
		while (counts < 169);
		BILED0 = 1;
		BILED1 = 1;
		TR0 = 0;
		round++;
	}
	printf("Final Score: %d\r\n", score);
	counts = 0;
	TR0 = 1;
	BZ1 = 0;
	while (counts < 169);
	BZ1 = 1;
	TR0 = 0;
	LED0 = 1;
	LED1 = 1;
	LED2 = 1;


}


unsigned char random(void)
{
    return (rand()%8);  // rand returns a random number between 0 and 32767.
                        // the mod operation (%) returns the remainder of
                        // dividing this value by 2 and returns the result,
                        // a value of either 0 or 1 or 2.
}
