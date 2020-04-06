#include "RLS_Encoder_Tiny.h"
#define onBoardLED 13
#define PPR17 131072.0		// 17Bits 2^17
#define PPR18 262144.0		// 18Bits 2^18

// Constructor
RLS_Encoder_Tiny::RLS_Encoder_Tiny(){
	//pinMode(onBoardLED, OUTPUT);
}

//Methods
void RLS_Encoder_Tiny::blink(int N){
	pinMode(13, OUTPUT);
	for (int i=0; i<N; i++){
		digitalWrite(onBoardLED, HIGH);
		delay(200);
		digitalWrite(onBoardLED, LOW);
		delay(200);
	}
}
void RLS_Encoder_Tiny::begin(long baudRate){
	Serial2.begin(baudRate);
	//while(!Serial2);
	//Serial2.begin(baudRate);
	//while(!Serial2);
	//Serial2.println("-->Encoder Started.");
}

void RLS_Encoder_Tiny::get_status(){
	Serial2.flush();
	Serial2.write(0x69); delay(5);
	byte b1 = Serial2.read();
	byte b2 = Serial2.read();
	Serial2.print("--> Encoder status: ");
	Serial2.print(b1,HEX);
	Serial2.print(":");
	Serial2.print(b2);
	Serial2.println(";");
}


void RLS_Encoder_Tiny::set_baud(long baudRate, byte dir){
	byte b[4];
	b[0]=(baudRate&0xFF); //extract first byte
	b[1]=((baudRate>>8)&0xFF); //extract second byte
	b[2]=((baudRate>>16)&0xFF); //extract third byte
	b[3]=((baudRate>>24)&0xFF); //extract fourth byte
	Serial2.flush();
	RLS_Encoder_Tiny::unlock();
	Serial2.write(0x42); delay(5);

	if(dir){
		for (int i = 0; i < 4; i++) {
			Serial2.write(b[i]);
			delay(5);
			
		}
	}
	else{
		for (int i = 3; i >= 0; i--) {
			Serial2.write(b[i]);
			delay(5);
		}
	}
	delay(10);
	RLS_Encoder_Tiny::save_conf(); delay(10);
}

void RLS_Encoder_Tiny::set_zero(){
	RLS_Encoder_Tiny::unlock();
	Serial2.write(0x5A); delay(5);
	Serial2.write(0xFF); delay(5);
	Serial2.write(0x00); delay(5);
	Serial2.write(0x00); delay(5);
	Serial2.write(0xFF); delay(5);
	RLS_Encoder_Tiny::save_conf(); delay(10);
	Serial2.println("--> Encoder zero set");

}

void RLS_Encoder_Tiny::get_status_long(){
	Serial2.flush();
	byte b1 = Serial2.read();
	byte b2 = Serial2.read();
	byte b3 = Serial2.read();
	byte b4 = Serial2.read();
	byte b5 = Serial2.read();
	byte b6 = Serial2.read();
	Serial2.print("--> Encoder status: ");
	Serial2.print(b1,HEX);
	Serial2.print(":");
	Serial2.print(b2,HEX);
	Serial2.print(":");
	Serial2.print(b3,HEX);
	Serial2.print(":");
	Serial2.print(b4,HEX);
	Serial2.print(":");
	Serial2.print(b5,BIN);
	Serial2.print(":");
	Serial2.print(b6,BIN);
	Serial2.println(";");
}

void RLS_Encoder_Tiny::unlock(){
	Serial2.write(0xCD); delay(5);
	Serial2.write(0xEF); delay(5);
	Serial2.write(0x89); delay(5);
	Serial2.write(0xAB); delay(5);
	Serial2.println("--> Encoder unlock");
}

void RLS_Encoder_Tiny::calibrate(){
	// Start calibration sequence
	Serial2.println("--> Starting calibration sequence: ");
	RLS_Encoder_Tiny::unlock();
	Serial2.write(0x41); delay(5);
	Serial2.println("--> calibration sequence Ended.");
	RLS_Encoder_Tiny::get_status();
}

void RLS_Encoder_Tiny::set_read(){
	RLS_Encoder_Tiny::unlock();
	Serial2.write(0x54); delay(5);		// Continues Read = 'T'
	Serial2.write(0x01); delay(5);		// Auto-start enable = 1
	Serial2.write(0x33); delay(5);		// Short response = '3'
	Serial2.write(0x00); delay(5);		// Period (250 micro-sec) (byte 8)
	Serial2.write(0xFA); delay(5);		// Period (250 micro-sec) (byte 9)
	Serial2.println("--> Encoder Set to Continues read mode '1'.\n\tDont forget to start using 'start_response()'");
	RLS_Encoder_Tiny::save_conf();
	//RLS_Encoder_Tiny::get_status();
}

void RLS_Encoder_Tiny::start_response(){
	//RLS_Encoder_Tiny::unlock();
	Serial2.write(0x53); delay(5);		// Continues Read = 'S'
	Serial2.println("--> Encoder Set to start continues read.");
	RLS_Encoder_Tiny::save_conf();
	//RLS_Encoder_Tiny::get_status();
}

void RLS_Encoder_Tiny::stop_response(){
	//RLS_Encoder_Tiny::unlock();
	Serial2.write(0x50); delay(5);		// Continues Read = 'P'
	Serial2.println("--> Encoder Set to stop continues read.");
	RLS_Encoder_Tiny::save_conf();
	//RLS_Encoder_Tiny::get_status();
}

void RLS_Encoder_Tiny::reset(){
	RLS_Encoder_Tiny::unlock();
	Serial2.write(0x72); delay(5);		// reset configuration parameters = 'r'
	Serial2.println("--> Encoder reset to factory settings.");
}
int RLS_Encoder_Tiny::Encoder_Pos(){
	return Serial2.parseInt();
}

float RLS_Encoder_Tiny::get_pos(){
	byte b1 = Serial2.read();
	byte b2 = Serial2.read();
	byte b3 = Serial2.read();
	uint32_t pos = b3 + (b2<<8) + (b1<<16);

	pos = (pos>>7);
	float pos_ang = pos*360.0/PPR17;
	return pos_ang;
}

uint32_t RLS_Encoder_Tiny::get_raw_data(){
	byte b1 = Serial2.read();
	byte b2 = Serial2.read();
	byte b3 = Serial2.read();
	uint32_t pos = b3 + (b2<<8) + (b1<<16);
	return (pos>>7);
}

void RLS_Encoder_Tiny::save_conf(){
	RLS_Encoder_Tiny::unlock();
	Serial2.write(0x63); delay(5);		// save configuration parameters = 'c'
	Serial2.println("--> Encoders Configurations saved.\nYou have to reset the Encoder.");
}
