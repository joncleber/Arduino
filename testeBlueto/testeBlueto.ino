#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1); // RX, TX

long BaudRate[] = {300,1200,2400,4800,9600,14400,19200,28800,38400,57600,115200,230400,460800,921600,1382400}; 

void setup()
{ 
  Serial.begin(9600);
  Serial.println("Finding Baud"); 
  
  for(int x=0; x < 15;x++){
    Serial.print("Baud: ");
    Serial.println(BaudRate[x]);   
    
    mySerial.begin(BaudRate[x]); 
    delay(10);
    mySerial.write("AT");
    delay(1000);
    
    if (mySerial.available()){
     String strData;
      while (mySerial.available()){
        strData += (char)mySerial.read(); 
      }
      Serial.println(strData);
      break;
    }
    mySerial.end();
  }
  //mySerial.begin(1200); 
  //mySerial.begin(2400); 
  //mySerial.begin(4800); 
  //mySerial.begin(57600); 
  //mySerial.begin(19200); 
  //mySerial.begin(38400); 
  //mySerial.begin(57600); 
  //mySerial.begin(115200); 
  //mySerial.begin(230400); 
  mySerial.begin(460800); 
  //mySerial.begin(921600); 
  //mySerial.begin(1382400);
}

void loop()
{
  if (Serial.available()){
    mySerial.write(Serial.read());
  }
  if (mySerial.available()){
    Serial.write(mySerial.read());
  }
}
