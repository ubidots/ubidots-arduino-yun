// This example is to save a variable with context to the Ubidots API

/****************************************
 * Include Libraries
 ****************************************/
#include <UbidotsYUN.h>

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "YOUR_TOKEN_HERE"
#define VARIABLE_LABEL "position"  // Change for your variable label desired

char str_lat[15];
char str_lng[15];

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
  
  char context[50];
  
  float lat = 25.761681; // Assign the Latitude desired
  float lng = -80.191788; // Assign the Longitude desired
  
  /* float value is copied onto str_lat/str_lng */
  dtostrf(lat, 4, 6, str_lat);
  dtostrf(lng, 4, 6, str_lng);
  
  /* Build the coordinates context to be sent*/
  sprintf(context, "lat=%s\\$lng=%s", str_lat, str_lng);
  /* Send variable with coordinates context to Ubidots*/
  client.add(VARIABLE_LABEL, 1, context);
  client.sendAll();
  delay(1000);
}