// Programa : NRF24L01 Receptor - Servo motor
// Autor : Arduino e Cia

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <Servo.h> 

// Armazena os dados recebidos
char recebidos[3];

// Inicializa o NRF24L01 nos pinos 9 (CE) e 53 (CS) do Arduino Mega
RF24 radio(9,53);

Servo myservo;

// Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xE13CBAF433LL;

// Define o pino do led
int i;
String valor;

void setup()
{
  // Servo conectado ao pino 4
  // Define o pino do led como saida

  // Inicializa a serial
  Serial.begin(57600);
  // Inicializa a comunicacao do NRF24L01
  radio.begin();
  // Entra em modo de recepcao
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  // Mensagem inicial
}

void loop()
{
  for(i =0; i<valor.length();i++){
    unsigned char valor2 = valor.charAt(i);
    radio.write( &valor2 ,sizeof(char));
    
  }
  radio.write('\0', sizeof(char));
 
}
