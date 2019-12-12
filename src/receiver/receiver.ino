#define BAUDRATE 115200
#include <Console.h>
#include <SPI.h>
#include <RH_RF95.h>
#define ID 7

// Singleton instance of the radio driver
RH_RF95 rf95;
int ledCoracao = A2;
float frequency = 915.0;  

void pisca_coracao()
{ // Função para "bater o coração"
  digitalWrite(ledCoracao, HIGH);
  delay(100);
  digitalWrite(ledCoracao, LOW);
  delay(500);
  digitalWrite(ledCoracao, HIGH);
  delay(100);
  digitalWrite(ledCoracao, LOW);
}

void setup(){
  pinMode(ledCoracao, OUTPUT);     
  Bridge.begin(BAUDRATE);
  Console.begin();
  while (!Console) ; // Wait for console port to be available
  Console.println("Start Sketch");
  if (!rf95.init())
    Console.println("init failed");
    
  // Setup LoRa Parameters
  rf95.setFrequency(frequency);
  rf95.setSettingID(ID);
  
  Console.print("Listening on frequency: ");
  Console.println(frequency);
}

void loop()
{
  if (rf95.available())
  {
    // Should be a message for us now   
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len))
    {
      digitalWrite(ledCoracao, HIGH);
      RH_RF95::printBuffer("request: ", buf, len);
      Console.print("Got: ");
      Console.println((char*)buf);
      Console.print("RSSI: ");
      Console.println(rf95.lastRssi(), DEC);
      
//      // Send a reply
//      uint8_t data[] = "Okay";
//      rf95.send(data, sizeof(data));
//      rf95.waitPacketSent();
//      Console.println("Sent a reply");
      pisca_coracao();
    }
    else
    {
      Console.println("Receive failed");
    }
  }
}
