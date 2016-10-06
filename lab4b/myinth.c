#include "clib.h"

extern int KeyBuffer;
unsigned tickcounter = 0;

void reseth ()
{
// cease program execution.  call exit (0) when (Ctrl-R) is pressed.
	
	exit(0);	
	
}

void tickh ()
{
// increment a tick counter and display "TICK n". then return
	
	tickcounter++;
	
	printNewLine();
	printString("TICK ");
	printUInt(tickcounter);
	printNewLine();	
}


void keyboardh ()
{
	int delaycounter;
	delaycounter = 0;	
	// if d is pressed:
	if (KeyBuffer == 'd'){// this is how we refer to keyboard input????
		printNewLine();		
		printNewLine();
		printString("DELAY KEY PRESSED");
		printNewLine();
		printNewLine();
		for (delaycounter = 0; delaycounter < 5000; delaycounter++){
			//nothing
		}
		printNewLine();		
		printString("DELAY COMPLETE");
		printNewLine();
		printNewLine();
	} else { // if anything else is pressed	
		printNewLine();		
		printString("KEYPRESS ");
		printChar(KeyBuffer);
		printString(" IGNORED");
		printNewLine();			
	}


	




}
