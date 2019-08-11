#include "gdk101_i2c.h"
#include <Wire.h>

GDK101_I2C::GDK101_I2C(uint8_t addr) {
  _addr = addr;
}

void GDK101_I2C::init() {
  gamma_mod_read(RESET); //
  get_fw_version();
}

bool GDK101_I2C::reset() {
  bool val;
  gamma_mod_read(RESET); //
  val = rw_buffer[0];
  return val;
}

void GDK101_I2C::update_all(){
  get_10min_avg();
  get_1min_avg();
  get_vib();
  get_status();
  get_measuring_time_min();
  get_measuring_time_sec();
}

float GDK101_I2C::get_fw_version(){
  gamma_mod_read(READ_STATUS);
  fw_version = rw_buffer[0] + (rw_buffer[1] / 100);
  return fw_version;
}

float GDK101_I2C::get_10min_avg() {
  gamma_mod_read(READ_10MIN_AVG);
  mea_10min_avg = rw_buffer[0] + (float)rw_buffer[1] / 100;
  return mea_10min_avg;
}

float GDK101_I2C::get_1min_avg() {
  gamma_mod_read(READ_1MIN_AVG);
  mea_1min_avg = rw_buffer[0] + (float)rw_buffer[1] / 100;
  return mea_1min_avg;
}

bool GDK101_I2C::get_vib(){
  gamma_mod_read(READ_STATUS);
  vib = rw_buffer[1];
  return vib;
}

byte GDK101_I2C::get_status(){
  //0 = Ready, 1 = 10min Waiting, 2 = Normal
  gamma_mod_read(READ_STATUS);
  gdk_status = rw_buffer[0];
  return gdk_status;
}

byte GDK101_I2C::get_measuring_time_min(){
  gamma_mod_read(READ_MEASURING_TIME);
  mea_time_min = rw_buffer[0];
  return mea_time_min;
}

byte GDK101_I2C::get_measuring_time_sec(){
  gamma_mod_read(READ_MEASURING_TIME);
  mea_time_sec = rw_buffer[1];
  return mea_time_sec;
}

float GDK101_I2C::to_rtg(float usv){
   float rtg;
   rtg = usv * SV_TO_RTG_CONST;
   return rtg;
}


//PRIVATE

void GDK101_I2C::gamma_mod_read(uint8_t reg) {
  byte lg = 2;
  Wire.beginTransmission(_addr);
  Wire.write(reg);
  Wire.endTransmission();
  delay(10);
  Wire.requestFrom(_addr, lg);
  byte i = 0;
  while (Wire.available())
  {
    rw_buffer[i] = Wire.read();
    i++;
  }
};
