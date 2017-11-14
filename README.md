ESPBattery
==========

* Author: Lennart Hennigs (https://www.lennarthennigs.de)
* Copyright (C) 2017 Lennart Hennigs.
* Released under the MIT license.

Arduino Library to calculate the ESP8266 (Feather Huzzah) LiPo battery level.

Description
-----------

It uses the Huzzah's ADC pin and a voltage divider.
The circuit is documented here: 
https://github.com/lobeck/adafruit-feather-huzzah-8266-battery-monitor

How to Use
----------

These are the constructor and the member functions the library provides:

```
    ESPBattery(
		byte analog_pin = A0, 
		int polling_interval_ms = 500, 
		int min_lvl = ESPBATTERY_CRITICAL, 
		int max_lvl = ESPBATTERY_FULL
		);

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
```

The library provides several callback handlers to be notified when the battery levels changes.

**Note:** For the class to work, you need to call the `loop()` member function in your sketch's `loop()` function. See the example for more details.


Installation
------------
Open the Arduino IDE choose "Sketch > Include Library" and search for "ESP Battery". 
Or download the ZIP archive (https://github.com/lennarthennigs/ESPBattery/zipball/master), and choose "Sketch > Include Library > Add .ZIP Library..." and select the downloaded file.


License
-------

MIT License

Copyright (c) 2017 Lennart Hennigs

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
