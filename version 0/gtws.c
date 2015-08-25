// Global Thermonuclear War Simulator 1995
// Chris Bowers
//
// Created for Ludum Dare #33
// 8/21/2015

#include <gb/gb.h>
#include <gb/drawing.h>

extern unsigned char earth_tiledata[];
extern unsigned char earth_tilemap[];
extern unsigned char title_tiledata[];
extern unsigned char title_tilemap[];
extern unsigned char end_tiledata[];
extern unsigned char end_tilemap[];

unsigned char crosshair_tiledata[] = {
	0x20,0x20,0x20,0x20,0xF8,0xF8,0x20,0x20, 0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x00
};

unsigned char explode_tiledata[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18, 0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x18,0x18,0x3C,0x3C, 0x3C,0x3C,0x18,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x18,0x18,0x3C,0x3C,0x7E,0x7E, 0x7E,0x7E,0x3C,0x3C,0x18,0x18,0x00,0x00,
	0x3C,0x3C,0x7E,0x7E,0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF,0x7E,0x7E,0x3C,0x3C,
	0x00,0x3C,0x00,0x7E,0x00,0xFF,0x00,0xFF, 0x00,0xFF,0x00,0xFF,0x00,0x7E,0x00,0x3C,
	0x3C,0x00,0x7E,0x00,0xFF,0x00,0xFF,0x00, 0xFF,0x00,0xFF,0x00,0x7E,0x00,0x3C,0x00
};
	
void end(){
	wait_vbl_done();
	DISPLAY_OFF;
	HIDE_SPRITES;
	SWITCH_ROM_MBC1(1);
	set_bkg_data(0, 221, end_tiledata);
	set_bkg_tiles(0, 0, 20, 18, end_tilemap);
	SHOW_BKG;
	DISPLAY_ON;
	while(1);
}

void main(){
	int xpos = 8 + GRAPHICS_WIDTH / 2;
	int ypos = 16 + GRAPHICS_HEIGHT / 2;
	int count = 0;
	int joy, i;
	set_sprite_data(0, 1, crosshair_tiledata);
	set_sprite_data(1, 6, explode_tiledata);
	SWITCH_ROM_MBC1(3);
	set_bkg_data(0, 179, title_tiledata);
	set_bkg_tiles(0, 0, 20, 18, title_tilemap);
	SHOW_BKG;
	DISPLAY_ON;
	waitpad(J_START);
	DISPLAY_OFF;
	SWITCH_ROM_MBC1(2);
	set_bkg_data(0, 182, earth_tiledata);
	set_bkg_tiles(0, 0, 20, 18, earth_tilemap);
	set_sprite_tile(0,0);
	move_sprite(0, xpos, ypos);
	SHOW_SPRITES;
	DISPLAY_ON;
	waitpadup();
	while (1){
		wait_vbl_done();
		joy = joypad();
		if (joy & J_UP && ypos > 14)
			--ypos;
		if (joy & J_DOWN && ypos < GRAPHICS_HEIGHT + 13)
			++ypos;
		if (joy & J_LEFT && xpos > 8)
			--xpos;
		if (joy & J_RIGHT && xpos < GRAPHICS_WIDTH + 8)
			++xpos;
		if (joy & J_A || joy & J_B){
			++count;
			move_sprite(count, xpos - 2, ypos - 2);
			for (i = 1; i != 7; ++i){
				set_sprite_tile(count, i);
				wait_vbl_done();
				wait_vbl_done();
			}
			set_sprite_tile(count, 4);
			set_sprite_prop(count, 1 << 4);
			if (count == 39){
				delay(500);
				end();
			}
		}		
		move_sprite(0, xpos, ypos);
	}
}