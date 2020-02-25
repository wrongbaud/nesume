//this example code shows how to put some text in nametable
//it assumes that you have ASCII-encoded font in the CHR tiles $00-$3f
//it also shows how to detect PAL/NTSC video system

#include "neslib.h"



//put a string into the nametable

void put_str(unsigned int adr,const char *str)
{
	vram_adr(adr);

	while(1)
	{
		if(!*str) break;

		vram_put((*str++)-0x20);//-0x20 because ASCII code 0x20 is placed in tile 0 of the CHR
	}
}


static unsigned char x,y,i,w;

void workexp(void){
	put_str(NTADR_A(2,2),"WORK EXPERIENCE");
}
void main(void)
{
	//rendering is disabled at the startup, the palette is all black

	pal_col(1,0x30);//set while color
	pal_col(17,0x30);//white color for sprite

	//you can't put data into vram through vram_put while rendering is enabled
	//so you have to disable rendering to put things like text or a level map
	//into the nametable

	//there is a way to update small number of nametable tiles while rendering
	//is enabled, using set_vram_update and an update list

	put_str(NTADR_A(7,2),"WRONGBAUD RESUME");
	put_str(NTADR_A(8,6),"WORK EXPERIENCE");
	put_str(NTADR_A(8,8),"SKILLS");
	put_str(NTADR_A(8,10),"EDUCATION");
	put_str(NTADR_A(8,12),"AWARDS");

	ppu_on_all();//enable rendering
	x=52;
	y=48;
	w = 0;
	while(1){
		
		ppu_wait_frame();//wait for next TV frame
		oam_spr(x,y,0x1E,0,0);//put sprite
		if(w==5){
			i=pad_poll(0);
			if(i&PAD_UP) { sfx_play(2,2); y-=16; } 
			if(i&PAD_DOWN) {sfx_play(2,2); y+=16;}
			if(i&PAD_START) {sfx_play(0,0);}
			if(y<48) y = 48;
			if(y>96) y = 96;
			w=0;
		}
		w+=1;
	}
		//do nothing, infinite loop
}