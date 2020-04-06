#ifndef Vault_h
#define Vault_h

#include "Arduino.h"


class Vault {
	public:
		// Constructor
		Vault(); 
		
		// Methods
		void blink(int N);
		void print_arr_byte(byte arr, byte row, byte col);
		void print_try(byte arr);
	private:
	
};
#endif
