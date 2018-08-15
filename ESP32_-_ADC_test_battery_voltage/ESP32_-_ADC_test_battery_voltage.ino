/*
 BAT+ -----7k------T-----15k-------GND
                   |
                   | 
 */
unsigned int percentage = 0;

unsigned long previousMillis = 0;
const long interval = 1000;

// setup
void setup() {
  Serial.begin(115200);
  analogReadResolution(12);             // Sets the sample bits and read resolution, default is 12-bit (0 - 4095), range is 9 - 12 bits
  analogSetWidth(12);                   // Sets the sample bits and read resolution, default is 12-bit (0 - 4095), range is 9 - 12 bits

  adcAttachPin(36);
  analogSetClockDiv(255); // 1338mS
}

// loop
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    float voltage = map(analogRead(36), 0, 4095, 0, 5000) / 1000.0F; // depends on ADC range/mode set

    if (voltage > 4.18) percentage = 100;
    else if (voltage < 3.0) percentage = 0;
    else
      percentage = (voltage - 3.0) * 100 / (4.18 - 3.0);

    Serial.println("Voltage: " + String(voltage));
    Serial.println(String(percentage) + " %");
  }
}

