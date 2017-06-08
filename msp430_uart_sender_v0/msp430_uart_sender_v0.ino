char commandbuffer[50];
int j = 0;
const char* example = "cv";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  memset(commandbuffer, 0, sizeof(commandbuffer)); // zero init if anything remains in the memory accidently
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("v x 15 20 y 30 40");

  if (Serial.available()) 
  {
    delay(10);
    char temp = Serial.read();
    if (temp == '\n')
    {
      // Reads the last element (depends on after logic)
      commandbuffer[j++] = temp;
      // Interprets message
      if (commandbuffer[1] == 'c' && commandbuffer[2] == 'v') // because of m they are from first
      {
        Serial.println("v x 10 20 y 30 40");
      }
      // Clear after interpretation
      memset(commandbuffer, 0, sizeof(commandbuffer));
      j = 0;
    }
    else if (j == 20)
    {
      // Design decision - if it is more than 20 than it is overloaded, just clear
      memset(commandbuffer, 0, sizeof(commandbuffer));
      j = 0;
    }
    else
    {
      commandbuffer[j++] = temp;
    }
  }
  /* //under revision
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
    }*/
delay(10); // 500 ori
}
