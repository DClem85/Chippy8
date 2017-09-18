#pragma once
class chip8 {
public:
	chip8();
	~chip8();

	bool drawFlag;

	void emulateCycle();
	void debugRender();
	bool loadApplication(const char * filename);

//Chip8

private:
	unsigned short opcode;
	unsigned char memory[4096];
	unsigned char V[16];			// CPU Registers
	unsigned short I;				// Index Register
	unsigned short pc;				// program counter
	unsigned char gfx[64 * 32];		// graphics array
	unsigned char delay_timer;		// counts down 
	unsigned char sound_timer;		// counts down
	unsigned short stack[16];		// store the PC in the stack before jumping
	unsigned short sp;				// stack pointer for when it jumps
	unsigned char key[16];			// keyboard 0x0-0xF

	void init();
};


