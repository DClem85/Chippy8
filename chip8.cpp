#include 
#include "chip8.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned char chip8_fontset[80] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, //0
	0x20, 0x60, 0x20, 0x20, 0x70, //1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
	0x90, 0x90, 0xF0, 0x10, 0x10, //4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
	0xF0, 0x10, 0x20, 0x40, 0x40, //7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
	0xF0, 0x90, 0xF0, 0x90, 0x90, //A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
	0xF0, 0x80, 0x80, 0x80, 0xF0, //C
	0xE0, 0x90, 0x90, 0x90, 0xE0, //D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
	0xF0, 0x80, 0xF0, 0x80, 0x80  //F
};

void chip8::emulateCycle()
{
	opcode = memory[pc] << 8 | memory[pc + 1]

	case 0x0000:
		switch (opcode & 0x000F)
		{
		case 0x0000: // 0x00E0: Clears the screen
			for (int i = 0; i < 2048; ++i)
				gfx[i] = 0x0;
			drawFlag = true;
			pc += 2;
			break;

		case 0x000E: // 0x00EE: Returns from subroutine
			--sp;			// 16 levels of stack, decrease stack pointer to prevent overwrite
			pc = stack[sp];	// Put the stored return address from the stack back into the program counter					
			pc += 2;		// Don't forget to increase the program counter!
			break;

		default:
			printf("Unknown opcode [0x0000]: 0x%X\n", opcode);
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
		if(V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
			pc += 4; //skip the next instruction
		else
			pc += 2; 
	break;

	case 0x4000:
		if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
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
		case 0x0000: // 08XY0 VX=Y
			V[opcode & 0x0F00 >> 8] = (opcode & 0x00F0 >> 4)
			pc += 2;
		break;

		case 0x0001: //08XY1 VX = VX|VY
			V[opcode & 0x0F00] |= (opcode & 0x00F0 >> 4))
			pc += 2;
		break;

		case 0x0002: //08XY2 VX = VX&VY
			V[opcode & 0x0F00] &= (opcode & 0x00F0 >> 4))
			pc += 2;
		break;

		case 0x0003 //08XY3 VX = VX ^ VY
			V[opcode & 0x0F00] ^= (opcode & 0x00F0 >> 4))
			pc += 2;
		break;

		case 0x0004: //08XY4 VX = VX + VY
			if(V[(opcode & 0x00F0) >> 4] > (0xFF - V[(opcode & 0x0F00) >> 8]))
					V[0xF] = 1; //there is a carry
			else
					V[0xF] = 0; //there is no carry
			V[opcode & 0x0F00] += (opcode & 0x00F0 >> 4))
			pc += 2;
		break;

		case 0x0005: //08XY5 VX = VX - VY. VF = 0 when borrow, 1 when not
			if(V[(opcode & 0x00F0) >> 4] > V[(opcode & 0x0F00) >> 8])
					V[0xF] = 0; // X needs to borrow! (But where are we borrowing from?!)
			else
					V[0xF] = 1; // X has enough
			V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0 >> 4)];
			pc += 2;
		break;
		//NEED TO IMPLEMENT ABILITY TO CHANGE THE OPERATIONS OF 6 and E!!!!!!
		case 0x0006: //08XY6 VF = (VX & 0x1) and V[X] = (X >>= 1) ___OR___ VX= (VY << 1) VF = (VY & 0x1) 
			V[0xF] = V[(opcode & 0x0F00) >> 8] & 0x1;
			V[(opcode & 0x0F00) >> 8] >>= 1;
			pc += 2;
		break;

		case 0x0007: // VX = VY - VX. VF = 1 when no borrow is used
			if(V[(opcode & 0x0F00) >> 8] > [v(opcode & 0x00F0) >> 4])
				V[0xF] = 0;
			else
				V[0xF] = 1;
			V[opcode & 0x0F00] = ((opcode & 0x00F0) >> 4) - ((opcode & 0x0F00) >> 8);
			pc += 2;
		break;

		case 0x000E: // VX <<=1, VF = MSB of VX before the shift ___OR___ Vx=Vy=Vy<<1 
			V[0xF] = V[(opcode & 0x0F00) >> 8] >> 7;
			V[(opcode & 0x0F00) >> 8] <<= 1;
			pc += 2;
		break;

		default:
			printf("Unknown opcode [0x8000]: 0x%X\n", opcode);
		}
		break;

	case 0x9000: // skip next instruction if VX != VY.
		if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 7])
			pc += 4;
		else
			pc += 2;
		break;

	case 0xA000: // ANNN: sets I to NNN 
		I = opcode & 0x0FFF;
		pc += 2;
		break;

	case 0xB000: //BNNN: jumps to NNN plus V0
		pc = ((opcode & 0x0FFF) + V[0]);\
	break;

	case 0xC000: //CXNN: VX = random value & NN
		V[(opcode & 0x0F00) >> 8] = (rand() % 0xFF) & (opcode & 0x00FF);
		pc += 2;
		break;

	case 0xD000: //DXYN: Draws a sprite at coordinate(VX, VY) that has a width of 8 pixels and a height of N pixels.
				 // Each row of 8 pixels is read as bit-coded starting from memory location I; 
				 // I value doesn't change after the execution of this instruction. 
				 // VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, 
				 // and to 0 if that doesn't happen
	{
		unsigned short x = V[(opcode & 0x0F00) >> 8];
		unsigned short y = V[(opcode & 0x00F0) >> 4];
		unsigned short height = opcode & 0x000f;
		unsigned short pixel;
		V[0xF] = 0;
		for (int yline = 0; yline < height; yline++)
		{
			pixel = memory[I + yline];
			for (int xline = 0; xline < 8; xline++;)
			{
				if ((pixel & (0x80 >> xline)) != 0)
				{
					if (gfx[(x + xline + ((y + yline) * 64))] == 1)
						v[0xF] = 1;
					gfx[x + xline + ((y + yline) * 64)] ^= 1;
				}
			}
		}
		drawFlag = true;
		pc += 2;
	}
	break;

	case 0xE000:
		switch (opcode & 0x00FF)
		{
		case 0x009E: //Skips the next instruction if the key stored in VX is pressed
			if (key[V[opcode & 0x0F00) >> 8]] != 0)
			pc += 4;
			else
			pc += 2;
		break;
		
		case 0x00A1: //Skips the next instruction if the key stored in VX isn't pressed.
			if (key[V[opcode & 0x0F00) >> 8]] == 0)
				pc += 4;
			else 
				pc += 2;
		break;
		
		default:
			printf("unknown opcode 0xE000: 0x%X\n", opcode);
		}

	case 0xF000:
		switch (opcode & 0x00FF)
		{
		case 0x0007:
			V[(opcode & 0x0F00) >> 8] = delay_timer;
			pc += 2;
		break;

		case 0x000A:
		{
			bool keyPress = false;

			for (int i = 0; i < 16; i++)
			{
				if (key[i] != 0)
				{
					V[(opcode & 0x0F00) >> 8] = i;
					keyPress = true;
				}
			}
			if (!keyPress)
				return;

			pc += 2;
		}
		break;

		case 0x0015: //FX15 delay timer = X
			delay_timer = V[(opcode & 0x0F00) >> 8];
			pc += 2;
		break;

		case 0x0018: xJKIOP; [[;/ ]]
			sound_timer = V[(opcode & 0x0F00) >> 8];
			pc += 2;
		break;

		case 0x001E: // add VX to I and sets VF to 1 if overflows
			if (I + (V[(opcode & 0x0F00) >> 8]) > 0xFFF)
				V[0xF] = 1;
			else
				V[0xF] = 0;
			I = +V[(opcode & 0x0F00) >> 8];
			pc += 2;
		break;

		case 0x0029: // sets I to the location of the sprite in VX. I still dont understand this one and need to play around with it. 
			I = V[(opcode & 0x0F00) >> 8] * 0x5;
			pc += 2;
		break;

		case 0x0033: // storing the binary coded decimal of VX in various integers. using TJA's solution for this. need to lookup binary coded decimal. 
			memory[I] = V[(opcode & 0x0F00) >> 8] / 100;
			memory[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;
			memory[I + 2] = (V[(opcode & 0x0F00) >> 8] % 100) % 10;
			pc += 2;
		break;

		case 0x0055: //stores V0 to VX in memory starting at I -- Register Dump
			for(int i = 0; i <= ((opcode & 0x0F00) >> 8); i++;
				memory[I + i] = V[i];
				// on the original, once over I = I + X + 1
			I += ((opcode & 0x0F00) >>8) + 1;
			pc += 2;
		break;

		case 0x0065: // fills the register from F[0] to(and including) F[X] with values from memory starting at I
			for(int i = 0; i <= ((opcode & 0x0F00) >>8); i++)
				V[i] = memory[I + i]
				// on the original, once over I = I + X + 1
			I += ((opcode & 0x0F00) >> 8) + 1;
			pc += 2;
		break;

		default:
			printf("unknown opcode 0xF000: 0x%X\n", opcode);
		}
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

//everything below here needs to be researched for understanding
void chip8::debugRender()
{
	// Draw
	for (int y = 0; y < 32; ++y)
	{
		for (int x = 0; x < 64; ++x)
		{
			if (gfx[(y * 64) + x] == 0)
				printf("O");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}

bool chip8::loadApplication(const char * filename)
{
	init();
	printf("Loading: %s\n", filename);

	// Open file
	FILE * pFile = fopen(filename, "rb");
	if (pFile == NULL)
	{
		fputs("File error", stderr);
		return false;
	}

	// Check file size
	fseek(pFile, 0, SEEK_END);
	long lSize = ftell(pFile);
	rewind(pFile);
	printf("Filesize: %d\n", (int)lSize);

	// Allocate memory to contain the whole file
	char * buffer = (char*)malloc(sizeof(char) * lSize);
	if (buffer == NULL)
	{
		fputs("Memory error", stderr);
		return false;
	}

	// Copy the file into the buffer
	size_t result = fread(buffer, 1, lSize, pFile);
	if (result != lSize)
	{
		fputs("Reading error", stderr);
		return false;
	}

	// Copy buffer to Chip8 memory
	if ((4096 - 512) > lSize)
	{
		for (int i = 0; i < lSize; ++i)
			memory[i + 512] = buffer[i];
	}
	else
		printf("Error: ROM too big for memory");

	// Close file, free buffer
	fclose(pFile);
	free(buffer);

	return true;
}