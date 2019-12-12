#include <SPI.h>     // Serial ARDUINO
#include <RH_RF95.h> // LoRa
#include "LowPower.h" 
#define ID 7

RH_RF95 rf95; // Arduino UNO + RFM96
float frequency = 915.0;
int i = 0;

void pisca(int led){
  digitalWrite(led, HIGH);
  delay(250);
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(250);
  digitalWrite(led, LOW);
}

void setup()
{
  Serial.begin(9600); // Comunicacao Serial COMX
  delay(1000); // Tempo p/ iniciar o Serial
  pinMode(13, OUTPUT); // LED

  // Inicializa o LoRa com os parametros padroes
  if (!rf95.init())
  {
    Serial.println("LoRa Status: FAIL!");
    while (1); // Caso de erro, limita o usuario a essa tela
  }
  rf95.setFrequency(frequency);
  rf95.setSettingID(ID); // Configura os parametros LoRa
}

void loop()
{
  char frase[210] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus vulputate dui commodo, consectetur quam eu, feugiat ex.Quisque efficitur sem in viverra vehicula. Proin gravida ante ac scelerisque ultrices.";// Nullam lobortis tellus lectus";
  //char radiopacket[20] = "";
  //dtostrf(t, 5, 2, radiopacket);
  String fraseString = (String)i+"--"+(String)frase;
  i++;
  int tam = fraseString.length();
  char pacote[tam];
  fraseString.toCharArray(pacote, tam);
  Serial.print("Sending: ");
  Serial.println(String(pacote));

  rf95.send((uint8_t *)pacote, tam);
  rf95.waitPacketSent();
  pisca(13);

  LowPower.idle(SLEEP_4S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
  //LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
}