#ifndef _BLINKER_CORE_H_INCLUDED
#define _BLINKER_CORE_H_INCLUDED

#include "chu_io_rw.h"
#include "chu_io_map.h"

class BlinkerCore{
public:
	enum {
		COUNTER_FIELD = 0x0000FFFF
	};

	BlinkerCore(uint32_t core_base_addr);
	~BlinkerCore();

	void write(uint32_t data, int led_reg);

private:
   uint32_t base_addr;
   uint32_t wr_data;
};

#endif  // _BLINKER_CORE_H_INCLUDED
