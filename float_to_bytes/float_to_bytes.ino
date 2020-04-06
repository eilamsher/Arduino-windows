
/*
  typedef union
  {
  float num;
  byte bytes[4];
  } f_union;

  f_union my_float;

  my_float.num = 123.4567;


  union cvt {
  float val;
  byte bytes[4];
  };

  union MyUnion {
  byte b[4];
  float fval;
  };
  float a = 123.4567;


  MyUnion myUnion;

  //u.fval = 2.4;

  x.val = a;


*/
float a = 123.456;

union u_tag {
  float temp_float ;
  byte bytes[4] ;
} u;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //u.temp_float = a;
/*
  for (int i = 0; i < 4; i++) {
    Serial.print(u.bytes[i]);
    Serial.print("  ");
  }
  */

  u.bytes[0] = 122;
  u.bytes[1] = 233;
  u.bytes[2] = 246;
  u.bytes[3] = 66;
  Serial.print(u.temp_float,10);
}

void loop() {
  // put your main code here, to run repeatedly:

}
