// This example is to save a variable with timestamp to the Ubidots API

/****************************************
 * Include Libraries
 ****************************************/
#include <UbidotsYUN.h>

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "YOUR_TOKEN_HERE"
#define VARIABLE_LABEL "temperature"  // Change for your variable label desired

long unsigned timestamp = 1429272000; // init timestamp value - (timestamp in SECONDS)

Ubidots client(TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

//Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/
void setup() {
  client.init();
  Serial.begin(9600);
}

void loop() {
  float value = analogRead(A0);
  /* Send variable with timestamp to Ubidots*/
  client.add(VARIABLE_LABEL, value, NULL, timestamp);
  client.sendAll();
  timestamp = timestamp + 600;
  delay(1000);
}
