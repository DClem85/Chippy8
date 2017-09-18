#include
#include // openGL
#include "chip8.h"

chip8 myChip8;

int main(int argc, char **argv)
{
	//setup render and input 
	setupGraphics();
	setupInput();

	myChip8.initialize();
	myChip8.loadgame("pong")

		//emulation loop
		for (;;) 
		{
		//emulate single cycle
			myChip8.emulateCycle();

		// draw flag set? Then update screen
			if (myChip8.drawFlag)
				drawGraphics();

		// store keypress state (Press and release)
			myChip8.setKeys();
		}
	return 0;
}