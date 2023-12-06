//#define _DEBUG
#include "chu_init.h"
#include "gpio_cores.h"
#include "vga_core.h"
#include "ps2_core.h"
#include "xadc_core.h"

int map(double x, double in_min, double in_max, int out_min, int out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int num2ascii(int num){
	return 48 + num;
}

void info_disp(OsdCore *osd_p, int *max, int *counter){
	// Round #: XX
	int info_txt1[11] = {82,111,117,110,100,0,35,58,0,0,0};
	// Max Rnd: XX
	int info_txt2[11] = {77,97,120,0,82,110,100,58,0,0,0};

	// hard coding if 10
	if(*counter > 9){
		info_txt1[9] = num2ascii(1);
		info_txt1[10] = num2ascii(0);
	}else{
		info_txt1[9] = 0;
		info_txt1[10] = num2ascii(*counter);
	}

	if(*max > 9){
		info_txt2[9] = num2ascii(1);
		info_txt2[10] = num2ascii(0);
	}else{
		info_txt2[9] = 0;
		info_txt2[10] = num2ascii(*max);
	}

	for (int i = 0; i < 11; i++) {
		osd_p->wr_char(2 + i, 1, info_txt1[i]);
		osd_p->wr_char(2 + i, 2, info_txt2[i]);
	}
}

void start(Ps2Core *ps2_p, FrameCore *frame_p, OsdCore *osd_p, int *state,
		int *id){
	// Click to Start!
	int start_txt[15] = {67,108,105,99,107,0,116,111,0,83,116,97,114,116,33};

	// orange state
	if (*state == -1){
		frame_p->bypass(0);
		osd_p->bypass(0);
		frame_p->clr_screen(0x1ea); 					// orange (111 101 010)
		osd_p->clr_screen();
		osd_p->set_color(0xfff, 0xfb5); 				// white/orange
		for (int i = 0; i < 15; i++) {
			osd_p->wr_char(32 + i, 15, start_txt[i]);
		}
	}
}

void round_start(Ps2Core *ps2_p, XadcCore *adc_p, int *id, SpriteCore *mouse_p,
		FrameCore *frame_p, OsdCore *osd_p, int *state, int *counter,
		int *max, int *total) {
   int lbtn, rbtn, xmov, ymov;
   double adc_read;
   int x, y;
   unsigned long timer;

   // Wait for Green...
   int red_txt[17] = {87,97,105,116,0,102,111,114,0,71,114,101,101,110,46,46,46};
   // CLICK NOW!!!
   int green_txt[12] = {67,76,73,67,75,0,78,79,87,33,33,33};
   // XXXXX ms
   int num_txt[14] = {0,0,0,0,0,0,0,0,0,109,115,0,0,0};
   // Keep Clicking.
   int blue_txt[14] = {75,101,101,112,0,67,108,105,99,107,105,110,103,46};

   // initialize mouse & background
   x = 320;
   y = 240;
   frame_p->bypass(0);
   mouse_p->bypass(0);
   osd_p->bypass(0);
   mouse_p->move_xy(x,y);

   do {
      if (*id == 2) {  // mouse
    	  if(*state == -1) {
    		  adc_read = adc_p->read_adc_in(0);
    		  *max = map(adc_read,0,0.999,1,10);
    		  uart.disp(*max);
    		  info_disp(osd_p,max,counter);
    	  }
    	  if (ps2_p->get_mouse_activity(&lbtn, &rbtn, &xmov, &ymov)) {
    		  x = x + xmov;
    		  y = y - ymov;
    		  mouse_p->move_xy(x,y);

    		  if (lbtn && (*state == -1 || *state == 0)) {

    			  // red state
    			  *state = 1;
    			  osd_p->clr_screen();
    			  frame_p->clr_screen(0x1ca); 			// red (111 001 010)
    			  osd_p->set_color(0xfff, 0xf35); 		// white/red
    			  for (int i = 0; i < 17; i++) {
    				  osd_p->wr_char(32 + i, 15, red_txt[i]);
    			  }
    			  sleep_ms(500 + (rand() % 3500));		// wait random time 0.5-4secs

    			  // green state
    			  osd_p->clr_screen();
    			  frame_p->clr_screen(0x0f2); 			// green (011 110 010)
    			  timer = now_ms();						// start reaction timer
    			  osd_p->set_color(0xfff, 0x7d5); 		// white/green
    			  for (int i = 0; i < 12; i++) {
    				  osd_p->wr_char(32 + i, 15, green_txt[i]);
    			  }
    		  }else if (lbtn && *state == 1){
    			  // blue state
    			  timer = (int)(now_ms()-timer);		// end reaction timer
    			  if (timer >= 99999) timer = 99999;	// limit 99,999 timer
    			  *total = *total + timer;

    			  // parse timer into text
    			  num_txt[7] = num2ascii(timer % 10);
    			  if(timer > 9){
    				  num_txt[6] = num2ascii(timer / 10 % 10);
    			  }else{
    				  num_txt[6] = 0;
    			  }
    			  if(timer > 99){
    				  num_txt[5] = num2ascii(timer / 100 % 10);
    			  }else{
    				  num_txt[5] = 0;
    			  }
    			  if(timer > 999){
    				  num_txt[4] = num2ascii(timer / 1000 % 10);
    			  }else{
    				  num_txt[4] = 0;
    			  }
    			  if(timer > 9999){
    				  num_txt[3] = num2ascii(timer / 10000 % 10);
    			  }else{
    				  num_txt[3] = 0;
    			  }

    			  frame_p->clr_screen(0x0af); 			// blue (010 101 111)
    			  osd_p->clr_screen();
    			  osd_p->set_color(0xfff, 0x5bf); 		// white/blue
    			  for (int i = 0; i < 14; i++) {
    				  osd_p->wr_char(32 + i, 14, num_txt[i]);
    				  osd_p->wr_char(32 + i, 15, blue_txt[i]);
    			  }
    			  *counter = *counter + 1;				// increase rounds
    			  *state = 0;							// change state
    			  info_disp(osd_p,max,counter);
    			  uart.disp("Reaction Time: ");
    			  uart.disp((int)timer);
    			  uart.disp("\n\r");
    			  uart.disp("Round: ");
    			  uart.disp(*counter);
    			  uart.disp("\n\r");
    			  uart.disp("Total: ");
    			  uart.disp(*total);
    			  uart.disp("\n\r");
    		  }
    	  }
      }
   } while (*counter < *max);
   *state = 2;
}

void game_end(Ps2Core *ps2_p, FrameCore *frame_p, OsdCore *osd_p,
		SpriteCore *mouse_p, int *state, int *counter, int *max,
		int *total, int *id){
	int avg = (int)((float)*total / (float)*counter);
	int lbtn, rbtn, xmov, ymov;
	int x, y;

	// WOW. You're Fast!
	int congrats_txt[22] = {0,0,0,87,79,87,46,0,89,111,117,39,114,101,0,70,97,115,116,33,0,0};
	// Average Time: XXXXX ms
	int time_txt[22] = {65,118,101,114,97,103,101,0,84,105,109,101,58,0,0,0,0,0,0,0,109,115};

	if(*state == 2) {
		sleep_ms(1500);
		if(avg >= 99999) avg = 99999;					// limit timer 99,999

		// parse avg into text
		time_txt[18] = num2ascii(avg % 10);
		if(avg > 9){
			time_txt[17] = num2ascii(avg / 10 % 10);
		}else{
			time_txt[17] = 0;
		}
		if(avg > 99){
			time_txt[16] = num2ascii(avg / 100 % 10);
		}else{
			time_txt[16] = 0;
		}
		if(avg > 999){
			time_txt[15] = num2ascii(avg / 1000 % 10);
		}else{
			time_txt[15] = 0;
		}
		if(avg > 9999){
			time_txt[14] = num2ascii(avg / 10000 % 10);
		}else{
			time_txt[14] = 0;
		}

		// end state
		osd_p->clr_screen();
		frame_p->clr_screen(0x116); 					// purple (100 010 110)
		osd_p->set_color(0xfff, 0x95d); 				// white/purple
		for (int i = 0; i < 22; i++) {
			osd_p->wr_char(30 + i, 14, congrats_txt[i]);
			osd_p->wr_char(30 + i, 15, time_txt[i]);
		}
		do {
			if (*id == 2) {
				if (ps2_p->get_mouse_activity(&lbtn, &rbtn, &xmov, &ymov)) {
					x = x + xmov;
		            y = y - ymov;
		            mouse_p->move_xy(x,y);
		            if (lbtn) {
		            	*state = -1;
		            	*counter = 0;
		            	*total = 0;
		            }
				}
			}
		} while (*state == 2);
	}
}

// external core instantiation
XadcCore adc(get_slot_addr(BRIDGE_BASE, S5_XDAC));
FrameCore frame(FRAME_BASE);
SpriteCore ghost(get_sprite_addr(BRIDGE_BASE, V3_GHOST), 1024);
SpriteCore mouse(get_sprite_addr(BRIDGE_BASE, V1_MOUSE), 1024);
OsdCore osd(get_sprite_addr(BRIDGE_BASE, V2_OSD));
Ps2Core ps2(get_slot_addr(BRIDGE_BASE, S11_PS2));

int main() {
	int state = -1;
	int counter = 0;
	int total = 0;
	int max = 3;

	// bye bye ghosty
	ghost.bypass(1);

	// init ps2 once so it stays running
	int id = ps2.init();
	uart.disp("\n\rPS2 device (1-keyboard / 2-mouse): ");
	uart.disp(id);
	uart.disp("\n\r");

	while (1) {
		start(&ps2, &frame, &osd, &state, &id);
		round_start(&ps2, &adc, &id, &mouse, &frame, &osd, &state, &counter, &max, &total);
		game_end(&ps2, &frame, &osd, &mouse, &state, &counter, &max, &total, &id);
	} // while
} //main
