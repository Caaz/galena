#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <maxmod.h>

#include <stdio.h>
#include <stdlib.h>

#include "soundbank.h"
#include "soundbank_bin.h"

void playMusic(u8 n);
void playSfx(u8 n);

static u16 keys_pressed = 0;

//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------


	// the vblank interrupt must be enabled for VBlankIntrWait() to work
	// since the default dispatcher handles the bios flags no vblank handler
	// is required
	irqInit();
	irqSet( IRQ_VBLANK, mmVBlank);
	irqEnable(IRQ_VBLANK);

	consoleDemoInit();

	// ansi escape sequence to set print co-ordinates
	// /x1b[line;columnH
	iprintf("\x1b[10;10HHello World!\n");
	
	mmInitDefault((mm_addr)soundbank_bin, 8);
	playMusic(0);
	

	while (1) {
		VBlankIntrWait();
		mmFrame();
		
		scanKeys();
		keys_pressed = keysDown();
		
		if (keys_pressed & KEY_A) playSfx(0);
		
	}
}

void playMusic(u8 n) {
	mmStop();
	
	switch (n)
	{
		case 0: mmStart(MOD_MUS0, MM_PLAY_LOOP); break;
	}
	
}

void playSfx(u8 n) {
	switch(n)
	{
		case 0: mmEffect(SFX_SND0); break;
	}
	
}


