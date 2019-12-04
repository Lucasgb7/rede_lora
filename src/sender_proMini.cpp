#include <SPI.h>
#include <RH_RF95.h>
#include <LowPower.h>
#define ID 3

RH_RF95 rf95;
float frequency = 915.0; //Frequência em Mhz

void setup()
{
    pinMode(A2, OUTPUT); // pin TXEN
    pinMode(A3, OUTPUT); // pin RXEN
    digitalWrite(A3, LOW);
    Serial.begin(9600);  // comunicacao serial
    delay(1000);

    if (!rf95.init()) // inicializa o LoRa com os parâmetros padroes
    {
        Serial.println("LoRa Status: FAIL!");
        while (1); // caso de erro, limita o usuario a essa tela
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

    digitalWrite(A2, HIGH);
    rf95.send((uint8_t *)pacote, tam);
    rf95.waitPacketSent();
    digitalWrite(A2, LOW);
    
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}