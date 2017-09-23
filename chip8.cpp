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

	case 0x1000: //jump to address
		pc = opcode & 0x0FFF;
	break;

	case 0x2000:
		stack[sp] = pc;
		++sp;
		pc = opcode & 0x0FFF;
	break;
	
	case 0x3000:
		if ([V(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
			pc += 4; //skip the next instruction
		else
			pc += 2; 
	break;

	case 0x4000:
		if ([V(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
			pc += 4; //skip the next instruction
		else
			pc += 2;
	break;

	case 0x5000: // 5XY0 skip if VX == VY
		if ([V(opcode & 0x0F00) >> 8] == (opcode & 0x00F0 >> 4))
			pc += 4; //skip the next instruction
		else
			pc += 2;
	break;

	case 0x6000: //6XNN sets VX to NN
		V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
		pc += 2;
		break;

	case 0x7000: //7XNN Vx == NN
		V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
		pc += 2;
		break;
	
	case 0x8000: //oh no! Multiples
		switch (opcode & 0x000F)
		{
			case 0x0000 // 08XY0 VX=Y
				V[opcode & 0x0F00 >> 8] = (opcode & 0x00F0 >> 4)
				pc += 2;
				break;

			case 0x0001 //08XY1 VX = VX|VY
				V[opcode & 0x0F00] |= (opcode & 0x00F0 >> 4))
				pc += 2;
				break;

			case 0x0002 //08XY2 VX = VX&VY
				V[opcode & 0x0F00] &= (opcode & 0x00F0 >> 4))
				pc += 2;
				break;

			case 0x0003 //08XY3 VX = VX ^ VY
				V[opcode & 0x0F00] ^= (opcode & 0x00F0 >> 4))
				pc += 2;
				break;

				case 0x0004 //08XY4 VX = VX + VY
					if V[(opcode & 0x00F0) >> 4] > (0xFF - V[(opcode & 0x0F00) >> 8])
						V[0xF] = 1; //there is a carry
					else
						V[0xF] = 0; //there is no carry
				V[opcode & 0x0F00] += (opcode & 0x00F0 >> 4))
				pc += 2;
				break;

			case 0x0005 //08XY5 VX = VX - VY
				V[opcode & 0x0F00] -= (opcode & 0x00F0 >> 4))
				pc += 2;
				break;

			case 0x0006 //08XY6 VX = VX - VY
				V[opcode & 0x0F00] = (opcode & 0x00F0 << 1))
				pc += 2;
				break;
		}


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

