#include "RFduinoBLE.h"
#include <Wire.h>

char commandbuffer[50];
int j = 0;

void setup() {

  Serial.begin(9600,2,3);

  RFduinoBLE.advertisementData = "CouDow"; // shouldnt be more than 10 characters long RFduinoBLE.deviceName = "Timer"; // name of your RFduino. Will appear when other BLE enabled devices search for it

  RFduinoBLE.begin(); // begin
 //Wire.beginOnPins(2, 3); // Starts the I2C interface with SCL on GPIO 2 and SDA on GPIO 3
 //Wire.begin();        // join i2c bus (address optional for master)
 // SoftwareSerial.begin(9600);  // start serial for output

}

void loop() {

// Sending from COM port
// In theory this is also good if it receives anything on serial port
   if (Serial.available()) {
    delay(10); 
    char temp = Serial.read();
    if (temp == '\n' || j == 20) // 20 is max message length
    {
      Serial.println(commandbuffer);
      RFduinoBLE.send(commandbuffer, (j+1));
      memset(commandbuffer, 0, sizeof(commandbuffer));
      if (j == 20)
      {
        j = 0; // Reset
        commandbuffer[j++] = temp;
      }
      else
      {
        j = 0; // Reset
      }
      
      
    }
    else
    {
      commandbuffer[j++] = temp;
    }
  }

}


void RFduinoBLE_onReceive(char *data, int len) {

  // display the first recieved byte
  for (int i = 0; i < len; i++)
  {
    Serial.print(data[i]);
  }
  Serial.println();
}

