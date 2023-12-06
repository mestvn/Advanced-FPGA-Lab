// #define _DEBUG
#include "chu_init.h"
#include "gpio_cores.h"
#include "sseg_core.h"
#include "ps2_core.h"

GpoCore led(get_slot_addr(BRIDGE_BASE, S2_LED));
GpiCore sw(get_slot_addr(BRIDGE_BASE, S3_SW));
SsegCore sseg(get_slot_addr(BRIDGE_BASE, S8_SSEG));
Ps2Core ps2(get_slot_addr(BRIDGE_BASE, S11_PS2));

void update_sseg(SsegCore *sseg_p, int *speed, bool *paused) {
	uint8_t sp_hun, sp_ten, sp_one, pause_ss;

	if (*paused) {
		pause_ss = 0x0c;
		sseg_p->set_dp(0x80);
	}else {
		pause_ss = 0xff;
		sseg_p->set_dp(0x00);
	}

	sp_hun = sseg_p->h2s(*speed / 100);
	sp_ten = sseg_p->h2s((*speed / 10) % 10);
	sp_one = sseg_p->h2s(*speed % 10);

	const uint8_t data[] = {sp_one, sp_ten, sp_hun, 0x37,
							0x8c, 0x92, 0xff, pause_ss};
	sseg_p->write_8ptn((uint8_t*) data);

} // led[0] is left

int input_check(Ps2Core *ps2_p, SsegCore *sseg_p, int *speed, bool *paused, bool *change) {
	int lbtn, rbtn, xmov, ymov;
	int i;
	for (i = 0; i < 100; i++) {
		if(ps2_p->get_mouse_activity(&lbtn, &rbtn, &xmov, &ymov)) {
			if (lbtn == 1) {
				uart.disp("Pause\r\n");
				*paused = !(*paused);
			}
			if(rbtn == 1) {
				uart.disp("Speed\r\n");
				*change = !(*change);
			}
			if(*change){
				uart.disp(xmov);
				uart.disp("\r\n");
				*speed = *speed + xmov;
				if (*speed > 999) {
					*speed = 999;
				}else if (*speed < 0){
					*speed = 0;
				}
			}
		}
		update_sseg(sseg_p, speed, paused);
	}
	return *speed * (10 - 1000) / 999 + 1000;
}

void chasing_LEDs(GpoCore *led_p, Ps2Core *ps2_p, SsegCore *sseg_p, bool *paused, int *speed, bool *change) {
	// speed 0-999 --> 1500ms-20ms delay
	int conv_speed;
	int i;
	for (i = 0; i < 15; i++) {
		conv_speed = input_check(ps2_p, sseg_p, speed, paused, change);
		led_p->write(0x0000);
		led_p->write(1, i);
		if(*paused){
			while(*paused) {
				conv_speed = input_check(ps2_p, sseg_p, speed, paused, change);
			}
		}else{
			sleep_ms(conv_speed);
		}
		led_p->write(0, i);
		sleep_ms(conv_speed);
	}
	for (i = 0; i < 15; i++) {
		conv_speed = input_check(ps2_p, sseg_p, speed, paused, change);
		led_p->write(0x0000);
		led_p->write(1, 15-i);
		if(*paused){
			while(*paused) {
				conv_speed = input_check(ps2_p, sseg_p, speed, paused, change);
			}
		}else{
			sleep_ms(conv_speed);
		}
		led_p->write(0, 15-i);
		sleep_ms(conv_speed);
	}
}

int main() {
	bool paused = false;
	bool change = false;
	int speed = 499;
	int id;

	// init ps2 to pass into chasing_LEDs
	uart.disp("\n\rPS2 device (1-keyboard / 2-mouse): ");
	id = ps2.init();
	uart.disp(id);
	uart.disp("\n\r");

	while (1) {
		chasing_LEDs(&led, &ps2, &sseg , &paused, &speed, &change);
	} //while
} //main
