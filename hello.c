
/*
A simple "hello world" example.
Set the screen background color and palette colors.
Then write a message to the nametable.
Finally, turn on the PPU to display video.
*/

#include "neslib.h"


// link the pattern table into CHR ROM
//#link "chr_generic.s"
void delaycode(unsigned char frames) {
  while (frames > 0) {
    ppu_wait_nmi();
    frames--;
  }
}

void clear_screen(void) {
  ppu_off();
  vram_adr(NTADR_A(0,0));
  vram_fill(0, 1024);
  ppu_on_all();
}

void startingseq() {
  clear_screen();
        vram_adr(NTADR_A(2,2));
        vram_write("STARTING...", 11);
        delaycode(60);
        vram_adr(NTADR_A(2,4));
        vram_write("3", 1);
        delaycode(60);
        vram_adr(NTADR_A(2,6));
        vram_write("2", 1);
        delaycode(60);
        vram_adr(NTADR_A(2,8));
        vram_write("1", 1);
        delaycode(60);
        vram_adr(NTADR_A(2,10));
        vram_write("STARTED", 8);
        delaycode(60);
        clear_screen();
        vram_adr(NTADR_A(2,2));
        vram_write("MY NAME IS...", 13);
        delaycode(60);
        clear_screen();
        vram_adr(NTADR_A(2,2));
        vram_write("MY NAME IS", 10);
        vram_adr(NTADR_A(2,4));
        vram_write("JOY ENTERTAINMENT SYSTEM", 24);
        delaycode(60);
        vram_adr(NTADR_A(2,6));
        vram_write("OR [JES]", 8);
        delaycode(60);
        vram_adr(NTADR_A(2,10));
        vram_write("JES: WHAT IS YOUR NAME?", 23);
        delaycode(90);
        vram_adr(NTADR_A(2,12));
        vram_write("???: Finn!", 10);
        delaycode(60);
        vram_adr(NTADR_A(2,14));
        vram_write("JES: Hello...", 13);
        delaycode(60);
        vram_adr(NTADR_A(2,14));
        vram_write("JES: Hello FINN", 15);
  	delaycode(120);
  	clear_screen();
  	vram_adr(NTADR_A(2,2));
        vram_write("TODAY WE WILL BEING", 19);
  	vram_adr(NTADR_A(2,4));
        vram_write("PLAYING A FEW GAMES!", 19);
  	delaycode(60);
  	vram_adr(NTADR_A(2,8));
        vram_write("I CURRENTLY HAVE...", 19);
  	delaycode(60);
	vram_adr(NTADR_A(2,10));
        vram_write("1", 1);
  	delaycode(60);
  	vram_adr(NTADR_A(2,12));
        vram_write("GAME(S)", 7);
  	delaycode(60);
  	vram_adr(NTADR_A(2,14));
        vram_write("WHAT DO YOU WANT TO PLAY", 24);
  	delaycode(120);
  	clear_screen();
}





// main function, run after console reset
void main(void) {
  unsigned char pad;
  
  // gamestates: 0: Menu,  
  unsigned char gamestate = 0;
  
  // set palette colors
  pal_col(0,0x02);	// set screen to dark blue
  pal_col(1,0x14);	// fuchsia
  pal_col(2,0x20);	// grey
  pal_col(3,0x30);	// white

  // write text to name table
  if (gamestate == 0) {
  vram_adr(NTADR_A(2,2));		// set address
  vram_write("WELCOME TO FUNLAND!", 19);	// write bytes to video RAM
  vram_adr(NTADR_A(2,4));		// set address
  vram_write("PRESS START TO RUN PROGRAM!", 27);
  vram_adr(NTADR_A(2,6));		// set address
  vram_write("UP: STORY MODE", 14);
  vram_adr(NTADR_A(2,8));		// set address
  vram_write("DOWN: ARCADE MODE", 17);
  }
  // enable PPU rendering (turn on screen)
  ppu_on_all();

  // infinite loop
  while (1) {
   ppu_wait_nmi();
   pad = pad_poll(0);
   
    
    
    
    
    
   // inputs
   if (pad & PAD_UP) {
      if (gamestate == 0) {
      // 1. Tell the PPU where to write
      	gamestate = 1;
        startingseq();
    }
    
    if (pad & PAD_DOWN) {
      // 1. Tell the PPU where to write
      vram_adr(NTADR_A(2,2));
      
      // 2. Write "UP" and add spaces to clear out "HI THERE!"
      vram_write("DOWN     ", 9); 
    }
    
    if (pad & PAD_LEFT) {
      // 1. Tell the PPU where to write
      vram_adr(NTADR_A(2,2));
      
      // 2. Write "UP" and add spaces to clear out "HI THERE!"
      vram_write("LEFT     ", 9); 
    }
    if (pad & PAD_RIGHT) {
      // 1. Tell the PPU where to write
      vram_adr(NTADR_A(2,2));
      
      // 2. Write "UP" and add spaces to clear out "HI THERE!"
      vram_write("RIGHT    ", 9); 
    }
    
    if (pad & PAD_START) {
      
        
      }
    }
    
  }
    
}
