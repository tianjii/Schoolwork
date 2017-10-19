/*  Names: Skylar Sang, Matthew Rhie, WangKun Zhang
    Section: 4B
    Date: 10/6/2017
    File name: lab1-1.c
    Program description:
*/
/*
  This program is incomplete. Part of the code is provided as an example. You
  need to modify the code, adding code to satisfy the stated requirements. Blank
  lines have also been provided at some locations, indicating an incomplete line.
*/
#include <c8051_SDCC.h> // include files. This file is available online
#include <stdio.h>

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
void Port_Init(void);  // Initialize ports for input and output
void Set_outputs(void);// function to set output bits
int push_button1(void);// function which checks Pushbutton 1
int push_button2(void);//function which checks Pushbutton 2
int slide_switch(void);// function that checks the Slide switch

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
__sbit __at 0xB6 LED0; // LED0, associated with Port 3 Pin 6
__sbit __at 0xB3 BILED0; // BILED0, associated with Port 3 Pin 3
__sbit __at 0xB4 BILED1; // BILED1, associated with Port 3 Pin 4
__sbit __at 0xB7 BZ1; // Buzzer, associated with Port 3 Pin 7
__sbit __at 0xA0 SS1;   // Slide switch, associated with Port 2 Pin 0
__sbit __at 0xB0 PB1;  // Push button 1, associated with Port 3, Pin 0
__sbit __at 0xB1 PB2; // Push button 2, associated with Port 3 Pin 1


//***************
void main(void)
{
    Sys_Init();        // System Initialization
    putchar(' ');      // the quote fonts may not copy correctly into SiLabs IDE
    Port_Init();       // Initialize ports 2 and 3

    while (1)          // infinite loop
    {
        // main program manages the function calls
        Set_outputs();
    }
}


//***************
/* Port_Init - Initializes Ports 2 and 3 in the desired modes for input and output */

void Port_Init(void)
{
    // Port 3
	P3MDOUT |= 0xD8; // set Port 3 output pins to push-pull mode (fill in the blank)
	P3MDOUT &= 0xFC; // set Port 3 input pins to open drain mode (fill in the blank)
	P3 |= ~0xFC; // set Port 3 input pins to high impedance state (fill in the blank)

    // Port 2
	P2MDOUT &= 0xFE; // set Port 2 input pins to open drain mode (fill in the blank)
	P2 |= 0x01;
//
//
}

//***************
// Set outputs:
void Set_outputs(void)
{
    if (slide_switch())  // if Slide Switch activated wait for button response
    {
		if (push_button1() && !push_button2()) { //if only button 1 is pressed, buzzer on
			printf("\r Switch is on and button 1 is pressed. Buzzer should be on.\n");
			BZ1 = 0;
			BILED1 = 1;
			BILED0 = 1;
			LED0 = 1;


		}
		else if (!push_button1() && push_button2()) { //if only button 2 is pressed, LED is on
			printf("\r Switch is on and button 2 is pressed. LED should be on \n");
			LED0 = 0;
			BILED1 = 1;
			BILED0 = 1;
			BZ1 = 1;
		}

		else if (push_button1() && push_button2()) { //both buttons are not pressed
			printf("Switch is on and both buttons are pushed. BILED is red \n");
			LED0 = 1;
			BZ1 = 1;
			BILED1 = 1;
			BILED0 = 0;
		}
		else {
		 	printf("\r Slide switch is on \n");
			LED0 = 1;
			BZ1 = 1;
		 	BILED1 = 1;
			BILED0 = 1;
		}

    }


	else {
		printf("\r Slide switch is off, BILED is green \n");
		LED0 = 1;
		BZ1 = 1;
		BILED0 = 1;
		BILED1 = 0;
	}


}

//***************
// Sensor - Returns a 0 if Pushbutton 1 not activated
//          or a 1 if Pushbutton 1 is activated.
//          This code reads a single input only, associated with PB0
// Note this code is not used by function yet, you must incorporate it
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


//***************
// Sensor - Returns a 0 if Slide Switch is 'off'
//          or a 1 if Slide switch  is 'on'
//          This code reads a single input only, associated with SS
int slide_switch(void)
{

    if (!SS1) return 1;
    else return 0;
}

