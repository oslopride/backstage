#include "Arduino.h" 
#include "MFRC522.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

const uint INTERVAL = 20;             // SAS token validity period in minutes
const int REFRESHPERCENTAGE = 80;     // Percentage of SAS token validity used when reauthentication is attempted
const int MISSEDTOOMANY = 10;         // Reconnect to MQTT when consecutively missed this many messages 
const int BLINKER = BUILTIN_LED;
const int BLINKTIME = 700;
const int BLINKOFF = LOW;
const int BLINKON = HIGH;              // Set to BLINKOFF to disable LED

const int RAINBOW = 0;     // RAINBOW pattern
const int GLITTER = 1;     // RAINBOW pattern
const int REDDOTS = 2;     // RAINBOW pattern
const int BMP = 3;     // RAINBOW pattern

void initRfid();
void runRFID();
void runMqtt();
void initPixelRing();
void connectToIoTHub();
void sendMqttMessage(String card);
void initWifi();
void sendGet(String card);
void runLeds();
void runWifi();
