#define _DEBUG
#include "chu_init.h"
#include "gpio_cores.h"

bool enable(GpiCore *sw_p){
	int s;
	s = sw_p->read();
	return (bool) (s & 0x0001);
}

void uart_check(int nxt_speed, int lst_speed) {
	if (nxt_speed != lst_speed){
		uart.disp("current speed: ");
		uart.disp(nxt_speed);
		uart.disp("\n\r");
	}
}

char speed_check(GpiCore *sw_p,char last_speed){
	int s;
	char next_speed;

	s = sw_p->read();
	next_speed = (char) ((s & 0x003E) >> 1);
	uart_check(next_speed+1,last_speed);
	return next_speed+1;
}

GpoCore led(get_slot_addr(BRIDGE_BASE, S2_LED));
GpiCore sw(get_slot_addr(BRIDGE_BASE, S3_SW));

void chasing_LEDs(GpoCore *led_p, GpiCore *sw_p, int n) {
   int i;
   char speed, last_speed;
   bool en;

   for (i = 0; i < n; i++) {
	   speed = speed_check(sw_p, last_speed);
	   en = enable(sw_p);
	   if(en){
		   led_p->write(0x0001);
		   i=0;
	   }else{
		   led_p->write(0x0000);
		   led_p->write(1, i);
		   sleep_ms(320/(speed));
		   led_p->write(0, i);
		   sleep_ms(320/(speed));
	   }
	   last_speed = speed;
   }
   for (i = 0; i < n; i++) {
	   speed = speed_check(sw_p, last_speed);
	   en = enable(sw_p);
	   if(en){
		   led_p->write(0x0001);
		   break;
	   }else{
		   led_p->write(0x0000);
		   led_p->write(1, 15-i);
		   sleep_ms(320/(speed));
		   led_p->write(0, 15-i);
		   sleep_ms(320/(speed));
	   }
	   last_speed = speed;
   }
}

int main() {

   while (1) {
	  chasing_LEDs(&led,&sw,15);
   } //while
} //main

