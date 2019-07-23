/////////////////////////////////////////////////////////////////
/*
    Arduino Library to calculate the ESP8266 (Feather Huzzah) LiPo battery level.
	Created by Lennart Hennigs, November 4, 2017.
*/
/////////////////////////////////////////////////////////////////

#pragma once

#ifndef ESPBattery_h
#define ESPBattery_h

/////////////////////////////////////////////////////////////////

#include "Arduino.h"

/////////////////////////////////////////////////////////////////


#define ESPBATTERY_CHARGING 840		// lower boundary
#define ESPBATTERY_FULL     645		// lower boundary
#define ESPBATTERY_OK       620		// picked value
#define ESPBATTERY_LOW      561		// upper boundary
#define ESPBATTERY_CRITICAL 526		// upper boundary

/////////////////////////////////////////////////////////////////

class ESPBattery {
  private:
    byte pin;
    unsigned int level;
    float v;
    int percentage;
    int min_level, max_level;
    int interval, last_read;
    int state, last_state;

    void readData();

    typedef void (*CallbackFunction) (ESPBattery&);
    
    CallbackFunction changed_cb = NULL;
    CallbackFunction low_cb = NULL;
    CallbackFunction critical_cb = NULL;
    CallbackFunction charging_cb = NULL;
    
  public:
    ESPBattery(byte analog_pin = A0, int polling_interval_ms = 500, int min_lvl = ESPBATTERY_CRITICAL, int max_lvl = ESPBATTERY_FULL);

	float getVoltage();
    int getPercentage();
    int getLevel();
    int getState();
    int getPreviousState();
	String stateToString(int state);
    
    void setLevelChangedHandler(CallbackFunction f);
    void setLevelLowHandler(CallbackFunction f);
    void setLevelCriticalHandler(CallbackFunction f);    
    void setLevelChargingHandler(CallbackFunction f);    

	void loop();
};

/////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////

// https://github.com/lobeck/adafruit-feather-huzzah-8266-battery-monitor
// https://learn.adafruit.com/li-ion-and-lipoly-batteries?view=all
// https://learn.sparkfun.com/tutorials/battery-technologies/lithium-polymer
// https://forums.adafruit.com/viewtopic.php?f=22&t=91646#p462472
// https://www.wolframalpha.com/input/?i=10k%CE%A9%2F(47k%CE%A9%2B10k%CE%A9)*3.2v

// the 10kΩ/47kΩ voltage divider reduces the voltage, so the ADC Pin can handle it
// According to Wolfram Alpha, this results in the following values:
// 10kΩ/(47kΩ+10kΩ)*  5v = 0.8772v
// 10kΩ/(47kΩ+10kΩ)*3.7v = 0.649v
// 10kΩ/(47kΩ+10kΩ)*3.2v = 0.561
// 10kΩ/(47kΩ+10kΩ)*3.1v = 0.544
// 10kΩ/(47kΩ+10kΩ)*3.0v = 0.526
// * i asumed 3.1v as minimum voltage => see LiPO discharge diagrams
// the actual minimum i've seen was 467, which would be 2.7V immediately before automatic cutoff
// a measurement on the LiPo Pins directly resulted in >3.0V, so thats good to know, but no danger to the battery.

// 865(866) --> CHARGING 
// 561 --> LOW
// 526 --> CRITICAL
