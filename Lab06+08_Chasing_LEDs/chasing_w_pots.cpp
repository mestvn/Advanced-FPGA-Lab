#define _DEBUG
#include "chu_init.h"
#include "gpio_cores.h"
#include "xadc_core.h"

bool enable(GpiCore *sw_p){
	int s;
	s = sw_p->read();
	return (bool) (s & 0x0001);
}

int adc_2_speed(XadcCore *adc_p) {
	double reading = adc_p->read_adc_in(0);
	sleep_ms(100);
	return (int) ((reading - 0) * (31 - 0) / (0.999 - 0) + 0); // map function
}

int uart_check(XadcCore *adc_p, int lst_speed) {
	int nxt_speed = adc_2_speed(adc_p) + 1;
	if (nxt_speed != lst_speed){
		uart.disp("current speed: ");
		uart.disp(nxt_speed);
		uart.disp("\n\r");
	}
	return nxt_speed;
}

GpoCore led(get_slot_addr(BRIDGE_BASE, S2_LED));
GpiCore sw(get_slot_addr(BRIDGE_BASE, S3_SW));
XadcCore adc(get_slot_addr(BRIDGE_BASE, S5_XDAC));

void chasing_LEDs(GpoCore *led_p, GpiCore *sw_p, XadcCore *adc_p) {
   int i;
   char speed, last_speed;
   bool en;

   for (i = 0; i < 15; i++) {
	   speed = uart_check(adc_p, last_speed);
	   en = enable(sw_p);
	   if(en){
		   led_p->write(0x0001);
		   i=0;
	   }else{
		   led_p->write(0x0000);
		   led_p->write(1, i);
		   sleep_ms(640/(speed));
		   led_p->write(0, i);
		   sleep_ms(640/(speed));
	   }
	   last_speed = speed;
   }
   for (i = 0; i < 15; i++) {
	   speed = uart_check(adc_p, last_speed);
	   en = enable(sw_p);
	   if(en){
		   led_p->write(0x0001);
		   break;
	   }else{
		   led_p->write(0x0000);
		   led_p->write(1, 15-i);
		   sleep_ms(640/(speed));
		   led_p->write(0, 15-i);
		   sleep_ms(640/(speed));
	   }
	   last_speed = speed;
   }
}

int main() {
	while (1) {
		chasing_LEDs(&led,&sw,&adc);
	} //while
} //main

