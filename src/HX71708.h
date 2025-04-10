#pragma once
//
//    FILE: HX71708.h

// HX71708 library
//  AUTHOR: Ben Iseman
// VERSION: 0.1.0
// PURPOSE: Library for load cells for Arduino
//     URL: https://github.com/beniseman/HX71708

// Adapted from the HX711 library by Rob Tillaart
//  AUTHOR: Rob Tillaart
// VERSION: 0.5.2
// PURPOSE: Library for load cells for Arduino
//     URL: https://github.com/RobTillaart/HX711_MP
//     URL: https://github.com/RobTillaart/HX711

// Licensed under the MIT License


//
//  NOTES
//  Superset of interface of HX71708 class of Bogde
//  uses float instead of long as float has 23 bits mantissa
//  which almost perfectly matches the 24 bit ADC.




#include "Arduino.h"

#define HX71708_LIB_VERSION               (F("0.1.0"))


const uint8_t HX71708_AVERAGE_MODE = 0x00;
//  in median mode only between 3 and 15 samples are allowed.
const uint8_t HX71708_MEDIAN_MODE  = 0x01;
//  medavg = average of the middle "half" of sorted elements
//  in medavg mode only between 3 and 15 samples are allowed.
const uint8_t HX71708_MEDAVG_MODE  = 0x02;
//  runavg = running average
const uint8_t HX71708_RUNAVG_MODE  = 0x03;
//  causes read() to be called only once!
const uint8_t HX71708_RAW_MODE     = 0x04;



//  supported values for set_data_rate()
const uint8_t HX71708_DATA_RATE_10 = 1;
const uint8_t HX71708_DATA_RATE_20 = 2;
const uint8_t HX71708_DATA_RATE_80 = 3;  
const uint8_t HX71708_DATA_RATE_320 = 4; // default



class HX71708
{
public:
  HX71708();
  ~HX71708();

  
  void     begin(uint8_t dataPin, uint8_t clockPin, bool fastProcessor = false);

  void     reset();

  //  checks if load cell is ready to read.
  bool     is_ready();

  //  wait until ready,
  //  check every ms
  void     wait_ready(uint32_t ms = 0);
  //  max # retries
  bool     wait_ready_retry(uint8_t retries = 3, uint32_t ms = 0);
  //  max timeout
  bool     wait_ready_timeout(uint32_t timeout = 1000, uint32_t ms = 0);


  ///////////////////////////////////////////////////////////////
  //
  //  READ
  //
  //  raw read
  float    read();

  //  get average of multiple raw reads
  //  times = 1 or more
  float    read_average(uint8_t times = 10);

  //  get median of multiple raw reads
  //  times = 3..15 - odd numbers preferred
  float    read_median(uint8_t times = 7);

  //  get average of "middle half" of multiple raw reads.
  //  times = 3..15 - odd numbers preferred
  float    read_medavg(uint8_t times = 7);

  //  get running average over times measurements.
  //  the weight alpha can be set to any value between 0 and 1
  //  times = 1 or more.
  float    read_runavg(uint8_t times = 7, float alpha = 0.5);


  ///////////////////////////////////////////////////////////////
  //
  //  MODE
  //
  //  get set mode for get_value() and indirect get_units().
  //  in median and medavg mode only 3..15 samples are allowed.
  void     set_raw_mode();
  void     set_average_mode();
  void     set_median_mode();
  void     set_medavg_mode();
  //  set_run_avg will use a default alpha of 0.5.
  void     set_runavg_mode();
  uint8_t  get_mode();

  //  corrected for offset.
  //  in HX71708_RAW_MODE the parameter times will be ignored.
  float    get_value(uint8_t times = 1);
  //  converted to proper units, corrected for scale.
  //  in HX71708_RAW_MODE the parameter times will be ignored.
  float    get_units(uint8_t times = 1);


  //  TARE
  //  call tare to calibrate zero
  void     tare(uint8_t times = 10);
  float    get_tare();
  bool     tare_set();



  bool     set_data_rate(uint8_t data_rate = HX71708_DATA_RATE_320, bool forced = false);
  uint8_t  get_data_rate();



  ///////////////////////////////////////////////////////////////
  //
  //  CALIBRATION
  //
  //  SCALE > 0
  //  returns false if scale == 0;
  bool     set_scale(float scale = 1.0);
  float    get_scale();

  //  OFFSET > 0
  void     set_offset(int32_t offset = 0);
  int32_t  get_offset();

  //  clear the scale
  //  call tare() to set the zero offset
  //  put a known weight on the scale
  //  call calibrate_scale(weight)
  //  scale is calculated.
  void     calibrate_scale(uint16_t weight, uint8_t times = 10);


  ///////////////////////////////////////////////////////////////
  //
  //  POWER MANAGEMENT
  //
  void     power_down();
  void     power_up();


  //  TIME OF LAST READ
  uint32_t last_time_read();
  uint32_t last_read();  //  obsolete in the future


  //  PRICING
  float    get_price(uint8_t times = 1) { return get_units(times) * _price; };
  void     set_unit_price(float price = 1.0) { _price = price; };
  float    get_unit_price() { return _price; };


private:
  uint8_t  _dataPin;
  uint8_t  _clockPin;

  uint8_t  _data_rate;
  int32_t  _offset;
  float    _scale;
  uint32_t _lastTimeRead;
  float    _price;
  uint8_t  _mode;
  bool     _fastProcessor;

  void     _insertSort(float * array, uint8_t size);
  uint8_t  _shiftIn();
};


//  -- END OF FILE --

