
/*
 * The master transmits information to the slave and the 
 * slave listens for information from the master.
 * ROLE: 0   IS SLAVE 
 * ROLE: 1   IS MASTER
 * 
 * Master (or "central") devices scan for other devices, and initiate connection. 
 * Usually, the master is the smartphone/tablet/PC. 
 * Slave (or "peripheral") devices advertise and wait for connections.
*/



#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // CONNECT BT RX PIN TO ARDUINO 11 PIN | CONNECT BT TX PIN TO ARDUINO 10 PIN

void setup() 
{
  pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(9, HIGH); 
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
}

void loop()
{

  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available())
    Serial.write(BTSerial.read());

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    BTSerial.write(Serial.read());
}
