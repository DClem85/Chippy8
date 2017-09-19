#include 
#include "chip8.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void chip8::emulateCycle()
{
	opcode = memory[pc] << 8 | memory[pc + 1]

	switch (opcode & 0xF000)
	{
	case 0x000: // multiple matches!
		switch (opcode & 0x000F)
		{
		case 0x0000:  //screen clear
		//do some stuff
		break;

		case 0x000E: //returns from subroutine
		//do the stuffs
		break;
		
		default:
			printf("Unknown opcode: 0x%X\n", opcode);
		}
		break;

	case 0xA000: // 
		I = opcode & 0x0FFF;
		pc += 2;
		break;

	

	default:
		printf("Unknown opcode: 0x%X\n", opcode);
	}

	if (delay_timer > 0)
		--delay_timer;

	if (sound_timer > 0)
	{
		if (sound_timer == 1)
			printf("BEEP!\n");
		--sound_timer;
	}
}

