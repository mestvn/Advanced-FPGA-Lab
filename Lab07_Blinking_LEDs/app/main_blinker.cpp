#define _DEBUG
#include "chu_init.h"
#include "gpio_cores.h"
#include "blinker_core.h"

void blink(GpiCore *sw_p, BlinkerCore *blk_p) {
	int x;
	x = sw_p->read();
	blk_p->write(x,3);
	blk_p->write(x/2,2);
	blk_p->write(x/4,1);
	blk_p->write(x/8,0);
}

// instantiate switch, blinker
GpiCore sw(get_slot_addr(BRIDGE_BASE, S3_SW));
BlinkerCore blinker(get_slot_addr(BRIDGE_BASE, S4_USER));

int main() {
	while(1) {
		blink(&sw, &blinker);
	}
}
