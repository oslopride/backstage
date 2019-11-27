/* Backstagr
 * @author: Hanne Johnsen - Bouvet Norge
 */
#include "backstagechip.h"
void loop() {
  runRFID();
  runLeds();
  runWifi();
}

void setup() {
    // Initialise the ring
  Serial.begin(115200);
  Serial.println("Running setup");
  initPixelRing();
  initRfid();
  initWifi();
 }
