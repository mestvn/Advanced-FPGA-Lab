#include "blinker_core.h"

BlinkerCore::BlinkerCore(uint32_t core_base_addr){
	base_addr = core_base_addr;
	wr_data = 0;
}
BlinkerCore::~BlinkerCore() {
}

void BlinkerCore::write(uint32_t data, int led_reg) {
	wr_data = data & COUNTER_FIELD;
	io_write(base_addr, led_reg, wr_data);
}
