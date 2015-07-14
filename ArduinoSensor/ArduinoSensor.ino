#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <stdio.h>


// MAC address and IP address for the controller.
byte mac[] = { 0x28, 0xD2, 0x44, 0xAC, 0x1D, 0x58 };
// IPAddress boardIp(169, 254, 205, 217);   //dhcp


IPAddress ip(141, 3, 150, 20);     // ip to send data on
unsigned int port = 6060;          // port to send data on
unsigned int localPort = 9876;     // local port need for udp connection

unsigned int difference = 0;       // 
unsigned int refreshTime = 50;    // scan time in ms

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;
float sensorValue;
float oldSensorValue;

char buffer[1024];


// the setup routine runs once when you press reset:
void setup() {
  // start the Ethernet and UDP:
  //Ethernet.begin(mac, boardIp);   //fix ip
  Ethernet.begin(mac);              //dhcp 
  Udp.begin(localPort);
  
  sensorValue = 0;
}


void loop() {
  // read the input on analog pin 0:
  oldSensorValue = sensorValue;
  sensorValue = ((analogRead(A0) - 49) / 5.1333333) - 90;

  dtostrf(sensorValue, 10, 2, buffer);
  
  // send the value you read:
  if (abs(sensorValue - oldSensorValue) > difference) {
    Udp.beginPacket(ip, port);
    Udp.write(buffer, 1024);
    Udp.endPacket();
  }
  delay(refreshTime);        // delay in between reads
}









