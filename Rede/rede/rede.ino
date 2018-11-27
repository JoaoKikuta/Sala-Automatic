#include <SPI.h>
#include <Ethernet.h>
#include <ip_arp_udp_tcp.h>
#include <net.h>
#include <enc28j60.h>
#include <EtherShield.h>
#include <ETHER_28J60.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
 
//Define o MAC da placa de rede. Nao eh necessario alterar
static uint8_t mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};
//Define o endereco IP da sua placa
static uint8_t ip[4] = {192, 168, 0, 107};
 
static uint16_t port = 80; 
 
ETHER_28J60 e;
 
int pin = 0; // Pino analogico para ligacao do LM35
int tempc = 0; // Variavel que armazena a temperatura em Celsius
// Variáveis para temperatura máxima e mínima
int maxtemp = -100,mintemp = 100; 
int i;
 
void setup()
{ 
  Serial.begin(9600);
  //Inicializa a placa com as configuracoes fornecidas
  e.setup(mac, ip, port);
  Serial.println("Connectando");
}
 
void loop()
{
  Serial.println(analogRead(pin));
  //Calcula o valor da temperatura
  tempc = (float(analogRead(pin))*5/(1023))/0.01;
 
  //Armazena a temperatura máxima na variavel maxtemp
  if(tempc > maxtemp) {maxtemp = tempc;} 
  //Armazena a temperatura máxima na variavel mintemp
  if(tempc < mintemp) {mintemp = tempc;} 
 
  if (e.serviceRequest())
  {
    e.print("<H1>FILIPEFLOP - Teste ENC28J60</H1><br/>");
    e.print("Valor temperatura : ");
    e.print(tempc);
    e.print("&deg<br/><br/>");
    e.print("Temperatura minima : ");
    e.print(mintemp);
    e.print("&deg<br/>");
    e.print("Temperatura maxima : ");
    e.print(maxtemp);
    e.print("&deg<b/>");
    e.respond();
    
  }
  delay(100);
}
