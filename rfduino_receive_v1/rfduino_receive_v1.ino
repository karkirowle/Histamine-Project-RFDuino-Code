#include "RFduinoBLE.h"
#include <Wire.h>

char commandbuffer[50];
int j = 0;

void setup() {

  Serial.begin(9600, 2, 3);

  RFduinoBLE.advertisementData = "CouDow"; // shouldnt be more than 10 characters long RFduinoBLE.deviceName = "Timer"; // name of your RFduino. Will appear when other BLE enabled devices search for it
  memset(commandbuffer, 0, sizeof(commandbuffer));
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
    if (temp == '\n')
    {
      // Reads the last element (depends on after logic)
      // commandbuffer[j++] = temp; // decided not to have unnecesary linebreak
      // Interprets message
      if (commandbuffer[0] != 'm') // Not reading itself
      {
        RFduinoBLE.send(commandbuffer, (j+1)); // send the content from the MSP430
      }
      // Clear after interpretation
      memset(commandbuffer, 0, sizeof(commandbuffer));
      j = 0;
    }
    else if (j == 20)
    {
      // If more than 20, send what is in buffer than reset
      RFduinoBLE.send(commandbuffer, (j+1));
      memset(commandbuffer, 0, sizeof(commandbuffer));
      j = 0;
    }
    else
    {
      commandbuffer[j++] = temp;
    }
    /*
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
    */ // under revision
  }
}


void RFduinoBLE_onReceive(char *data, int len) {
  // This is what I receive on radio
  // display the first recieved byte
  Serial.print('m');
  for (int i = 0; i < len; i++)
  {
    Serial.print(data[i]);
  }
  Serial.print('\r');
  Serial.print('\n');
}

