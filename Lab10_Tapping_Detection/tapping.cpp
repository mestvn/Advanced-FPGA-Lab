 #define _DEBUG
#include "chu_init.h"
#include "gpio_cores.h"
#include "xadc_core.h"
#include "sseg_core.h"
#include "spi_core.h"

double map(double x, double in_min, double in_max, double out_min, double out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double abs(double val) {
	if(val < 0) return val * -1;
	return val;
}

void led_check(GpoCore *led_p, int n) {
   int i;

   for (i = 0; i < n; i++) {
      led_p->write(1, i);
      sleep_ms(30);
      led_p->write(0, i);
      sleep_ms(10);
   }
}

double gsensor_check(SpiCore *spi_p, bool do_uart) {
   const uint8_t RD_CMD = 0x0b;
   const uint8_t DATA_REG = 0x08;
   const float raw_max = 127.0 / 2.0;  //128 max 8-bit reading for +/-2g

   int8_t xraw, yraw, zraw;
   float x, y, z;

   spi_p->set_freq(400000);
   spi_p->set_mode(0, 0);
   spi_p->assert_ss(0);    // activate
   spi_p->transfer(RD_CMD);  // for read operation
   spi_p->transfer(DATA_REG);
   xraw = spi_p->transfer(0x00);
   yraw = spi_p->transfer(0x00);
   zraw = spi_p->transfer(0x00);
   spi_p->deassert_ss(0);
   x = (float) xraw / raw_max;
   y = (float) yraw / raw_max;
   z = (float) zraw / raw_max;
   if (do_uart) {
	   uart.disp("x/y/z axis g values: ");
	   uart.disp(x, 3);
	   uart.disp(" / ");
	   uart.disp(y, 3);
	   uart.disp(" / ");
	   uart.disp(z, 3);
	   uart.disp("\n\r");
   }
   sleep_ms(10);
   return abs(x) + abs(y) + abs(z);
}

GpoCore led(get_slot_addr(BRIDGE_BASE, S2_LED));
GpiCore sw(get_slot_addr(BRIDGE_BASE, S3_SW));
SpiCore spi(get_slot_addr(BRIDGE_BASE, S9_SPI));

int main() {
	double vector, next_vector;
	int mapped;
	while(1) {
		next_vector = gsensor_check(&spi, false);
		mapped = map(abs(next_vector-vector), 0.2, 1.25, 1, 16);
		if(mapped > 0) {
			uart.disp("next_vector: ");
			uart.disp(next_vector,3);
			uart.disp("  vector: ");
			uart.disp(vector,3);
			uart.disp("  diff: ");
			uart.disp(abs(next_vector-vector), 3);
			uart.disp("\n\r");
			led_check(&led, mapped-1);
			gsensor_check(&spi, true);
			sleep_ms(10);
		}
		vector = next_vector;
	}
}
