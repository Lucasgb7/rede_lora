#include <SPI.h>     // Serial ARDUINO
#include <RH_RF95.h> // LoRa
#include <LowPower.h>
#define ID 14

RH_RF95 rf95; // Arduino UNO + RF96
float frequency = 915.0; //Frequência em Mhz

void setup()
{ // Configura os parâmetros LoRa
  // Configura os pinos como saida
  Serial.begin(9600); // Inicia comunicação com serial COMX
  delay(1000); // Serial leva um tempo para iniciar

  // Inicializa o LoRa com os parâmetros padrões
  if (!rf95.init())
  {
    Serial.println("LoRa Status: FAIL!");
    while (1); // Caso de erro, limita o usuário a essa tela
  }
  rf95.setFrequency(frequency);
  rf95.setSettingID(ID);
}

void loop()
{
  char frase[256] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus vulputate dui commodo, consectetur quam eu, feugiat ex. Quisque efficitur sem in viverra vehicula. Proin gravida ante ac scelerisque ultrices. Nullam lobortis tellus lectus. Ut in posuere.";
  //char radiopacket[20] = "";
  //dtostrf(t, 5, 2, radiopacket);
  String fraseString = (String)frase;
  int tam = fraseString.length();
  char pacote[tam];
  fraseString.toCharArray(pacote, tam);
  Serial.print("Sending: ");
  Serial.println(String(pacote));

  rf95.send((uint8_t *)pacote, tam);
  rf95.waitPacketSent();

  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}