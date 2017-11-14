/////////////////////////////////////////////////////////////////

#include "ESPBattery.h";

/////////////////////////////////////////////////////////////////

ESPBattery battery = ESPBattery();

/////////////////////////////////////////////////////////////////

void setup() {
  // setup serial port
  Serial.begin(9600);
  delay(50);
  
  // attach handler function
  battery.setLevelChangedHandler(stateHandler);
  Serial.println("\n\nLevel Handler Demo");
  // call the handler once to display the current status
  stateHandler(battery);  
}

/////////////////////////////////////////////////////////////////

void loop() {
  battery.loop();
}

/////////////////////////////////////////////////////////////////

// function that will be called when the battery state changes
void stateHandler(ESPBattery& b) {
  int state = b.getState();
  int level = b.getLevel();

  Serial.print("\nCurrent state: ");
  Serial.println(b.stateToString(state));
  Serial.print("Current level: ");
  Serial.println(b.getLevel());
}

/////////////////////////////////////////////////////////////////
