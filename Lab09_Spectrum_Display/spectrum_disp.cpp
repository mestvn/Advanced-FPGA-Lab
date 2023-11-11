 #define _DEBUG
#include "chu_init.h"
#include "gpio_cores.h"
#include "xadc_core.h"
#include "sseg_core.h"

double adc_read(XadcCore *adc_p) {
	double reading = adc_p->read_adc_in(0);
	sleep_ms(100);
	return reading;
}

double map(double x, double in_min, double in_max, double out_min, double out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void red(PwmCore *pwm_p, double val) {
	double duty;
	if((val > 0 && val < 0.1667) || val > 0.8333) {		// 0.0001-0.1666,0.8334-0.9999
		duty = 0.25;
	}else if(val >= 0.1667 && val <= 0.3333) {			// 0.1667-0.3333
		duty = map(val, 0.1667, 0.3333, 0.25, 0);
	}else if(val >= 0.6667 && val <= 0.8333) {			// 0.6667-0.8333
		duty = map(val, 0.6667, 0.8333, 0, 0.25);
	}else{												// 0.3334-0.6666
		duty = 0;
	}
	pwm_p->set_duty(duty,2);
}

void green(PwmCore *pwm_p, double val) {
	double duty;
	if(val > 0.1667 && val < 0.5) {						// 0.1668-0.4999
		duty = 0.25;
	}else if(val >= 0 && val <= 0.1667) {				// 0-0.1667
		duty = map(val, 0, 0.1667, 0, 0.25);
	}else if(val >= 0.5 && val <= 0.6667) {				// 0.5-0.6667
		duty = map(val, 0.5, 0.6667, 0.25, 0);
	}else{												// 0.6668-0.9999
		duty = 0;
	}
	pwm_p->set_duty(duty,1);
}

void blue(PwmCore *pwm_p, double val) {
	double duty;
	if(val > 0.5 && val < 0.8333) {						// 0.5001-0.8332
		duty = 0.25;
	}else if(val >= 0.8333) {							// 0.8333-0.9999
		duty = map(val, 0.8333, 0.9999, 0.25, 0);
	}else if(val >= 0.3333 && val <= 0.5) {				// 0.3333-0.5
		duty = map(val, 0.3333, 0.5, 0, 0.25);
	}else{												// 0.0001-0.3332
		duty = 0;
	}
	pwm_p->set_duty(duty,0);
}

void pwm_rgb_led(PwmCore *pwm_p, double val) {
	pwm_p->set_freq(50);
	red(pwm_p, val);
	green(pwm_p, val);
	blue(pwm_p, val);
}

void sseg_disp(SsegCore *sseg_p, double val) {
	int one = (int) val;
	int tenth = (int) (val * 10) % 10;
	int hundth = (int) (val * 100) % 10;
	int thouth = (int) (val * 1000) % 10;

	sseg_p->write_1ptn(sseg_p->h2s(one), 3);
	sseg_p->write_1ptn(sseg_p->h2s(tenth), 2);
	sseg_p->write_1ptn(sseg_p->h2s(hundth), 1);
	sseg_p->write_1ptn(sseg_p->h2s(thouth), 0);
	sseg_p->set_dp(0x8);
}

GpoCore led(get_slot_addr(BRIDGE_BASE, S2_LED));
GpiCore sw(get_slot_addr(BRIDGE_BASE, S3_SW));
XadcCore adc(get_slot_addr(BRIDGE_BASE, S5_XDAC));
PwmCore pwm(get_slot_addr(BRIDGE_BASE, S6_PWM));
SsegCore sseg(get_slot_addr(BRIDGE_BASE, S8_SSEG));

int main() {
	double pot;
	while (1) {
		pot = adc_read(&adc);
		sseg_disp(&sseg,pot);
		pwm_rgb_led(&pwm,pot);
	} //while
} //main

