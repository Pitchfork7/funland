
/*
A simple "hello world" example.
Set the screen background color and palette colors.
Then write a message to the nametable.
Finally, turn on the PPU to display video.
*/

#include "neslib.h"

unsigned char rpsfirsttime = 1;
unsigned char gamestate = 0;
unsigned char pad;
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

void gamesel(void) {
  clear_screen();
  vram_adr(NTADR_A(2,2));
  vram_write("UP: ROCK PAPER SCISSORS", 23);
}

void startingseq(void) {
  
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
  	
}



// games

void rpsgame(void) {
  unsigned char jeschoice;
  pad = pad_trigger(0);
  
  if (rpsfirsttime == 1) {
  
    
  clear_screen();
  vram_adr(NTADR_A(2,2));
  vram_write("UP: ROCK", 8);
  vram_adr(NTADR_A(2,4));
  vram_write("A: PAPER", 9);
  vram_adr(NTADR_A(2,6));
  vram_write("B: SCISSOR", 11);
  rpsfirsttime = 2;
  }
  
  if (pad & PAD_UP || PAD_A || PAD_B) {
     if (rpsfirsttime == 2) {
       rpsfirsttime = 3;
       jeschoice = rand8() % 3;
     }
  }
  
  
  

  
}





// main function, run after console reset
void main(void) {
  unsigned char pad;
  
  // gamestates: 0: Menu, 1: start seq, 2: game sel 

  
  // set palette colors
  pal_col(0,0x38);	// set screen to dark blue
  pal_col(1,0x17);	// fuchsia
  pal_col(2,0x20);	// grey
  pal_col(3,0x30);	// white

  // write text to name table
  if (gamestate == 0) {
  vram_adr(NTADR_A(2,2));		// set address
  vram_write("WELCOME TO FUNLAND!", 19);	// write bytes to video RAM
  vram_adr(NTADR_A(2,6));		// set address
  vram_write("UP: STORY MODE", 14);
  vram_adr(NTADR_A(2,8));		// set address
  vram_write("DOWN: ARCADE MODE", 17);
  }
  
  if (gamestate == 3) {
    
  }
  // enable PPU rendering (turn on screen)
  ppu_on_all();

  // infinite loop
  while (1) {
   ppu_wait_nmi();
   pad = pad_trigger(0);
    
    
   if (gamestate == 0) {
     if (pad & PAD_UP) {
       gamestate = 1;
       startingseq();
       gamestate = 2;
       gamesel();
     }
     
     if (pad & PAD_DOWN) {
     	gamestate = 3;
     }
   }
    
    
    
    
   if (gamestate == 2) {
     if (pad & PAD_UP) { 
       gamestate = 3;
     }
   }
    
   if (gamestate == 3) {
     rpsgame();
   }
    
    
   
    }
    
}
