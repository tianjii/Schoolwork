/*  Names: Skylar Sang, Matthew Rhie, WangKun Zhang
    Section: 4B
    Date: 9/25/17
    File name: lab1-2.c
    Description: LAB1-2
*/
/*
  This program demonstrates the use of A\D Conversion to adjust game settings
*/

#include <c8051_SDCC.h>// include files. This file is available online
#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
void Port_Init(void);      // Initialize ports for input and output
void Timer_Init(void);     // Initialize Timer 0
void Interrupt_Init(void); //Initialize interrupts
void Timer0_ISR(void) __interrupt 1;
unsigned char random(void);
unsigned int checkplayer(unsigned int);
int Slide_Switch(void);
int push_button1(void);
int push_button2(void);

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
__sbit __at 0xB3 BILED0;
__sbit __at 0xB4 BILED1;
__sbit __at 0xB0 PB1;
__sbit __at 0xB1 PB2;

__sbit __at 0xA0 SS;
__sbit __at 0xB6 LED0;
__sbit __at 0xB5 LED1;
__sbit __at 0xB7 BZ1;
    // Slide Switch associated with Port 2 Pin 0
// sbit settings are incomplete, include those developed
// in Lab 1-1 and add the sbit setting for LED1
unsigned int counts = 0;
unsigned int round = 0;
unsigned int rand_num = 3;
unsigned int last_rand = 3;
int score =0;


//***************
void main(void)
{
    Sys_Init();      // System Initialization
    Port_Init();     // Initialize ports 2 and 3
    Interrupt_Init();
    Timer_Init();    // Initialize Timer 0

    putchar(' ');    // the quote fonts may not copy correctly into SiLabs IDE

    while (1) /* the following loop prints the number of overflows that occur
                while the pushbutton is pressed, the BILED is lit while the
                button is pressed */
    {
		if (!Slide_Switch())
		{
			if (round == 10)
			{
			round = 0;
			}
			else
			{
				TR0 = 0;
			}
		}

		if (Slide_Switch() && round < 10){
			printf("Start Game\r\n");

			while (round < 10)
			{	//While loop to play game
				while (SS);
				while (last_rand == rand_num) {
					rand_num = random();
				}
				last_rand = rand_num;


				if (rand_num == 0) {
					LED0 = 0;
					LED1 = 1;
				}
				else if (rand_num == 1){
					LED0 = 1;
					LED1 = 0;
				}
				else if (rand_num == 2){
					LED0 = 0;
					LED1 = 0;
				}
				//wait one second
				counts = 0;
				TR0 = 1;
				TMR0 = 0;
				while (counts < 338);
				LED0 = 1;
				LED1 = 1;
				//check player input

				if (checkplayer(rand_num) == 1) {
					BILED0 = 1;
					BILED1 = 0;
					score++;
				}

				else {
					BILED0 = 0;
					BILED1 = 1;
				}


				TMR0 = 0;
				counts = 0;
				while (counts < 338);
				TR0 = 0;
				BILED0 = 0;
				BILED1 = 0;
				round++;

			}
			printf("Score: %d \r\n", score);
			score = 0;
		}


    }
}

//***************
void Port_Init(void)
{
    // use Port configuration from Lab 1-1
    // adding the output bit for LED1
	P3MDOUT |= 0xF8;
	P3MDOUT &= 0xFC;
	P3 |= 0x03;
	P2MDOUT &= 0xFE;
	P2 |= 0x01;

}

void Interrupt_Init(void)
{
    IE |= 0x02;      // enable Timer0 Interrupt request (by masking)
    EA = 1;       // enable global interrupts (by sbit)
}
//***************
void Timer_Init(void)
{

    CKCON |= 0x08;  // Timer0 uses SYSCLK as source
    TMOD &= 0xF0;   // clear the 4 least significant bits
    TMOD |= 01;   // Timer0 in mode 1
    TR0 = 0;           // Stop Timer0
    TMR0 = 0;           // Clear high & low byte of T0

}


//***************
void Timer0_ISR(void) __interrupt 1
{
// add interrupt code here, in this lab, the code will increment the
// global variable 'counts'
	counts++;
}

/******************************************************************************/
/*
  This function demonstrates how to obtain a random integer between 0 and 1 in
  C. You may modify and use this code to get a random integer between 0 and N.
*/

/*return a random integer number between 0 and 1*/
unsigned char random(void)
{
    return (rand()%3);  // rand returns a random number between 0 and 32767.
                        // the mod operation (%) returns the remainder of
                        // dividing this value by 2 and returns the result,
                        // a value of either 0 or 1 or 2.
}

int Slide_Switch(void)
{
	if (!SS) {
	return 1; }
	else return 0;
}

int push_button1(void)
{
    if (!PB1) {
	return 1;
	}
    else {
	} return 0;
}

int push_button2(void)
{

    if (!PB2) return 1;
    else     return 0;
}
unsigned int checkplayer(unsigned int n) {
	if (!push_button1() && push_button2() && n == 0) {
		return 1;
	}
	else if (push_button1() && !push_button2() && n == 1) {
		return 1;
	}
	else if (push_button1() && push_button2() && n == 2) {
		return 1;
	}
	else return 0;
}
