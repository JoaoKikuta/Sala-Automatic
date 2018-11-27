#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <Ethernet.h>
#include <SPI.h>
 
#define LM35 A0

int leitura;
float leituraconvertida;
char sentenca[128];
char valortemp[10];
 
byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192,168,0,50 };

IPAddress server_addr(192,168,0,102);  
char user[] = "arduino";              
char password[] = "arduino";       
int porta = 3306;   
 
char INSERIR_TEMP[] = "INSERT INTO registrotemp (temperatura) VALUES (%s)";
char BANCODEDADOS[] = "USE banco_arduino";
 
EthernetClient client;
MySQL_Connection conn((Client *)&client);
 
void setup() 
{ 
   Serial.begin(115200);
   //Serial.println("Conectando...");
   while (!Serial); 
   Ethernet.begin(mac_addr,ip);
   Serial.println("Conectando...");
  // Serial.println(server_addr);
   //Serial.println(user);
   //Serial.println(password);
   //Serial.println(porta);
   if (conn.connect(server_addr, porta, user, password)) 
   {
      delay(1000);
      
      MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
      cur_mem->execute(BANCODEDADOS);
      delete cur_mem;
   }
   else
   {
      Serial.println("A conexão falhou");
      conn.close();
   }
}
 
 
void loop() 
{
   Serial.println("Executando sentença");
 
   leitura = analogRead(LM35);
   leituraconvertida = (float(analogRead(LM35))*5/(1023))/0.01;
 
   dtostrf(leituraconvertida, 4, 1, valortemp);
   sprintf(sentenca, INSERIR_TEMP, valortemp);
   
   MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
   cur_mem->execute(sentenca);
   delete cur_mem;
 
   delay(2000);
}
