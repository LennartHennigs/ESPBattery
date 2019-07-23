/////////////////////////////////////////////////////////////////
/*
  Arduino Library to calculate the ESP8266 (Feather Huzzah) LiPo battery level.
  Created by Lennart Hennigs, November 4, 2017.
*/
/////////////////////////////////////////////////////////////////

#include "ESPBattery.h"

/////////////////////////////////////////////////////////////////

ESPBattery::ESPBattery(byte analog_pin, int polling_interval_ms, int min_lvl, int max_lvl) {
  pin = analog_pin;
  interval = polling_interval_ms;
  min_level = min_lvl;  
  max_level = max_lvl;
  
  readData();
}

/////////////////////////////////////////////////////////////////

void ESPBattery::readData() {
  last_read = millis();
  level = analogRead(pin);
  v = (float) level / 1000 / (10000. / (47000 + 10000));
  percentage = map(level, min_level, max_level, 0, 100);

  if (percentage < 0) {
    percentage = 0;  
  } else if (percentage > 100) {
    percentage = 100;
  }
  getState();
}

/////////////////////////////////////////////////////////////////

void ESPBattery::loop() {
  if (millis() > last_read + interval) {
    readData();
  }
}

/////////////////////////////////////////////////////////////////

float ESPBattery::getVoltage() {
  return v;
}

/////////////////////////////////////////////////////////////////

int ESPBattery::getPercentage() {
  return percentage;
}

/////////////////////////////////////////////////////////////////

int ESPBattery::getLevel() {
  return level;
}

/////////////////////////////////////////////////////////////////

int ESPBattery::getState() {
    last_state = state;
    if (level >= ESPBATTERY_CHARGING) {
        state = ESPBATTERY_CHARGING;
    } else if (level >= ESPBATTERY_FULL) {
        state = ESPBATTERY_FULL;        
    } else if (level <= ESPBATTERY_CRITICAL) {
        state = ESPBATTERY_CRITICAL;        
    } else if (level <= ESPBATTERY_LOW) {
        state = ESPBATTERY_LOW;        
    } else {
        state = ESPBATTERY_OK;
    }
        
    if (state != last_state) {
        if (changed_cb != NULL) changed_cb (*this);    
        switch (state) {
            case ESPBATTERY_CHARGING:
                if (charging_cb != NULL) charging_cb (*this);    
                break;
            case ESPBATTERY_CRITICAL:
                if (critical_cb != NULL) critical_cb (*this);    
                break;
            case ESPBATTERY_LOW:
                if (low_cb != NULL) low_cb (*this);    
                break;
        }   
    }
    return state;
}

/////////////////////////////////////////////////////////////////

String ESPBattery::stateToString(int state) {
	switch (state) {
		case ESPBATTERY_OK:
			return "OK";
		case ESPBATTERY_FULL:
			return "FULL";
		case ESPBATTERY_CHARGING:
			return "CHARGING";
		case ESPBATTERY_CRITICAL:
			return "CRITICAL";
		case ESPBATTERY_LOW:
			return "LOW";
	}
}

/////////////////////////////////////////////////////////////////

int ESPBattery::getPreviousState() {
    return last_state;
}

/////////////////////////////////////////////////////////////////

void ESPBattery::setLevelChangedHandler(CallbackFunction f) {
    changed_cb = f;
}

/////////////////////////////////////////////////////////////////

void ESPBattery::setLevelLowHandler(CallbackFunction f) {
    low_cb = f;
}

/////////////////////////////////////////////////////////////////

void ESPBattery::setLevelCriticalHandler(CallbackFunction f) {
    critical_cb = f;
}

/////////////////////////////////////////////////////////////////

void ESPBattery::setLevelChargingHandler(CallbackFunction f) {
    charging_cb = f;    
}

/////////////////////////////////////////////////////////////////
