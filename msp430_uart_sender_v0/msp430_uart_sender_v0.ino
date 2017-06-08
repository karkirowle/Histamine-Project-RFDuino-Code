char commandbuffer[50];
int j = 0;
const char* example = "cv";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("v x 15 20 y 30 40");

  if (Serial.available()) {
    delay(10);
    char temp = Serial.read();
    if (temp == '\n' || j == 20) // 20 is max message length
    {
      // Serial.println(j);
      if (temp == '\n' && j < 20)
      {
        commandbuffer[j++] = temp;
        //Serial.println(commandbuffer); // each to newline
        if (commandbuffer[0] == 'c' && commandbuffer[1] == 'v')
        {
          Serial.println("v x 10 20 y 30 40");
        }
      }
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
  delay(500);
}
