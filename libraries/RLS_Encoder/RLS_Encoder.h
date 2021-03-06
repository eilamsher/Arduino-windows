#ifndef tl
#define tl

#if (arduino >=100)
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif


class RLS_Encoder {
	public:
		// Constructor
		RLS_Encoder(); 
		
		// Methods
		void begin(long baudRate);
		void blink(int N);
		void get_status();
		void get_status_long();
		void set_baud(long baudRate, byte dir);
		void set_zero();
		void unlock();
		void calibrate();
		void set_read();
		void start_response();
		void stop_response();
		void reset();
		int  Encoder_Pos();
		void save_conf();
		float get_pos();
		uint32_t get_raw_data();
		
	private:
	
};
#endif
