
#include "gdk101_i2c.h"

//
//http://www.eleparts.co.kr/data/goods_old/design/product_file/Hoon/AN_GDK101_V1.0_I2C.pdf
//

//A0 Short, A1 Short : 0x18
//A0 Open,  A1 Short : 0x19
//A0 Short, A1 Open  : 0x1A
//A0 Open,  A1 Open  : 0x1B

#define DEF_ADDR 0x18

GDK101_I2C gdk101(DEF_ADDR);

float avg10min;
float avg1min;
float fw_vers;
int _status;

bool vibration;
byte mea_min;
byte mea_sec;

//output
char out_buff[48];

void setup() {
  Serial.begin(115200);
  gdk101.init();
  //gdk101.reset();
}

void loop() {
  avg10min = gdk101.get_10min_avg();
  avg1min = gdk101.get_1min_avg();
  mea_min = gdk101.get_measuring_time_min();
  mea_sec = gdk101.get_measuring_time_sec();
  _status = gdk101.get_status();
  vibration = gdk101.get_vib();

  sprintf(out_buff, "Time: %i:%i", mea_min, mea_sec);
  Serial.println(out_buff);

  sprintf(out_buff, "Radiation uSv/h 10min: %0.2f \t min: %0.2f ", avg10min, avg1min);
  Serial.println(out_buff);

  sprintf(out_buff, "Status: %i vibration: %i version %0.2f", _status, vibration, fw_vers);
  Serial.println(out_buff);
  Serial.println();
  
  delay(2000);
}
