/* Arduino MIDI Drum Pads *

  This sketch reads three piezo different disks and if value exceeds allowed sensitivity
  limit a MIDI note is sent.

  Both the sensitivity value and the pseudo debounce behaviour using millis() can be adjusted
  as required to prevent double triggering of pads.

   The circuit:
    * + connection of piezo 1 attached to analog in 0
    * - connection of piezo 1 attached to ground
    * 1-megohm resistor attached from analog in 0 to ground

    * + connection of piezo 2 attached to analog in 1
    * - connection of piezo 2 attached to ground
    * 1-megohm resistor attached from analog in 1 to ground

    * + connection of piezo 3 attached to analog in 2
    * - connection of piezo 3 attached to ground
    * 1-megohm resistor attached from analog in 2 to ground

 */


const int pads[] = {A0, A1, A2};
const int sensitivity = 500;  // threshold value to decide when the detected sound is a knock or not

int padReading = 0;
unsigned long lastHitMillis[] = {0,0,0};

void setup() {
  Serial.begin(9600);
}

void loop() {

  //Iterate through each pad
  for(int i = 0; i < 3; i++){
    unsigned long currentMillis = millis();

    /*To avoid false triggers test if the debounce delay
    period has passed*/
    if(currentMillis - lastHitMillis[i] >= 70){

      padReading = analogRead(pads[i]);

      /*
      * if the sensor reading is greater than the sensitivity limit:
      */
      if (padReading >= sensitivity) {

        //Set the hit time for pseudo debouncing
        lastHitMillis[i] = millis();
        Serial.write(i);
        //TODO - Send MIDI Note On here
      }
    }

  }

}
