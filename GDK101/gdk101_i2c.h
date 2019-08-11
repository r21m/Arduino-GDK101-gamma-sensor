#ifndef GDK101_I2C_H
#define GDK101_I2C_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//I2C register
#define READ_FIRMWARE 0xB4
#define RESET 0xA0

#define READ_STATUS 0xB0
#define READ_MEASURING_TIME 0xB1
#define READ_10MIN_AVG 0xB2 //Read Measuring Value (10min avg / 1min update)
#define READ_1MIN_AVG  0xB3 //Read Measuring Value (1min avg / 1min update)

#define SV_TO_RTG_CONST 107.185

//
//http://www.eleparts.co.kr/data/goods_old/design/product_file/Hoon/AN_GDK101_V1.0_I2C.pdf
//

class GDK101_I2C
{
  public:
    explicit GDK101_I2C(uint8_t addr);

    void init();
    bool reset();
    void update_all();
    
    float get_fw_version();
    float get_10min_avg();
    float get_1min_avg();
    bool  get_vib();
    byte  get_status();
    byte  get_measuring_time_min();
    byte  get_measuring_time_sec();
    float to_rtg(float usv);

    float fw_version = 0.0f;
    float mea_10min_avg;
    float mea_1min_avg;
    byte  gdk_status;
    bool  vib = false; 
    byte  mea_time_min;
    byte  mea_time_sec;
    String measuring_unit = ("uSv/hr");
        
  private:
    uint8_t _addr;
    byte rw_buffer[2] = {0, 0};
    void gamma_mod_read(uint8_t _reg);
};

#endif
//
// END OF FILE
//
