#include "Vault.h"

// Constructor
Vault::Vault(){
	
}

//Methods
void Vault::blink(int N){
	pinMode(13, OUTPUT);
	for (int i=0; i<N; i++){
		digitalWrite(13, HIGH);
		delay(200);
		digitalWrite(13, LOW);
		delay(200);
	}
}

void print_arr_byte(byte arr[][], byte row, byte col) {
  for (int i = 0; i < row; i++)  {
    for (int j = i; j < col + i; j++) {
      Serial.print(arr[i * row + j]);
      Serial.print(",");
    }
    Serial.print("\n");
  }
  Serial.println("---------------------------------------");
}

void print_arr_byte(byte arr) {
  Serial.print(arr);
  Serial.print(",");
  Serial.print("\n");
  Serial.println("---------------------------------------");
}