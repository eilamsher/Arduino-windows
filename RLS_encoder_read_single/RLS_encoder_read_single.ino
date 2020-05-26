

//==============================================================================
//Shmulik Edelman
//shmulike@post.bgu.ac.il
//==============================================================================

//=====[ INCULDE ]==============================================================
#include "RLS_Encoder.h"
#define PPR17 131072.0

//#include <ros.h>
//#include <std_msgs/Float32MultiArray.h>
//#include <i2c_t3.h>

//=====[ Constants ]========================================
//#define N_links 4
//float joint_offset[] = {5.0, 5.0, 3.0, 1.0};

union u_tag {
  byte b[4];
  float fval;
} u;

//=====[ VARIABLES ]============================================================
RLS_Encoder enc;
int bau = 57600;
//ros::NodeHandle nh;
byte data[4] = {0};
byte b[3];
//int value = 0;
float enc1_val;
//float arr[N_links]={0};
//std_msgs::Float32MultiArray joint_ang;
//ros::Publisher pub_joints("/robot_snake_1/joint_val", &joint_ang);
//int count=0;
//uint8_t slave_add[3] = {100, 101, 102};
//uint8_t slave_1 = 0x66;
//=====[ SETUP ]================================================================
void setup() {
  int abc = 40000;
  Serial.begin(115200); while (!Serial);
  //Serial.println("Start");
  enc.begin(115200);
  delay(5);
  enc.set_read();
  delay(5);
  //enc.set_baud(abc, 0);
  delay(5);
  //enc.begin(abc);
  delay(5);
  //Serial1.begin(115200);


  /*
    Serial2.end();

    enc.begin(bau);
    delay(5);

    enc.set_read();
    delay(5);
  */
  //enc.start_response();
  // nh.getHardware()->setBaud(115200);
  //nh.initNode();
  //nh.advertise(pub_joints);
  //joint_ang.data_length = N_links;
  // Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
  //Wire.setDefaultTimeout(250000); // 250ms default timeout
}

//=====[ LOOP ]=================================================================
void loop() {
  //Serial.println(x++);
  //Serial.print("line:\t");
  //enc.get_status_long();

  // Read first=this encoder position

  Serial2.flush();
  while (Serial2.available()) {
    //if (Serial2.read()=='1'){
    //enc1_val = enc.get_pos();
    b[0] = Serial2.read();
    b[1] = Serial2.read();
    b[2] = Serial2.read();
    //if (enc1_val > 180.0)
    //enc1_val -= 360.0;
    break;
  }

  long pos = b[0];
  pos = (pos << 8);
  pos = pos | b[1];
  pos = (pos << 8);
  pos = pos | b[2];
  pos = (pos >> 7);
  enc1_val = pos * 360.0 / PPR17;


  Serial.print("val : ");            // uncomment this for printing
//  byte v = enc1_val;
  Serial.println(enc1_val, 2);          // uncomment this for printing
  delay(5);
}
//==============================================================================
