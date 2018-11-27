


#include <UIPEthernet.h> // Used for Ethernet
#include <SoftwareSerial.h>
#include <Adafruit_Fingerprint.h>


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };                                      
EthernetClient client;
char server[] = "192.168.0.102"; // IP Adres 
int  interval = 5000; 


SoftwareSerial mySerial(6, 7);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int idPego;


void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac);
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Leitor Biometrico Encontrado");
  } else {
    Serial.println("Leitor Biometrico nao encontrada");
    while (1);
  }


  
  Serial.print("IP Address        : ");
  Serial.println(Ethernet.localIP());
  Serial.print("Subnet Mask       : ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Default Gateway IP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("DNS Server IP     : ");
  Serial.println(Ethernet.dnsServerIP());
  
  if (client.connect(server, 80)) {
    Serial.println("-> Connected");
  }
  else {
    Serial.println("--> connection failed/n");
  }
  
}

void loop() {
  
   getFingerprintIDez();
 
}



uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagem Capturada");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("Dedo nao Localizado");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Erro ao se comunicar");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Erro ao Capturar");
      return p;
    default:
      Serial.println("Erro desconhecido");
      return p;
  }

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagem Convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Imagem muito confusa");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Erro ao se comunicar");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Impossivel localizar Digital");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Impossivel Localizar Digital");
      return p;
    default:
      Serial.println("Erro Desconhecido");
      return p;
  }
  
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Digital Encontrada");
    
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Erro ao se comunicar");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Digital Desconhecida");
    return p;
  } else {
    Serial.println("Erro Desconhecido");
    return p;
  }   
  
  Serial.print("ID # Encontrado"); 
  Serial.print(finger.fingerID); 
  Serial.print(" com precisao de "); 
  Serial.println(finger.confidence); 
  
}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK){ return -1;}


  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) {return -1;}

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK){ return -1;}


  
  Serial.print("ID # Encontrado"); 
  idPego = finger.fingerID;
  
  
  if (client.connect(server, 80)) {
    Serial.println("-> Connected");
    // Make a HTTP request:
    client.print( "GET /teste/add_data.php?");
    client.print("nome=");
    client.print( "arduino1" );
    client.print("&&");
    client.print("id=");
    client.print(idPego);
    client.println( " HTTP/1.1");
    client.print( "Host: " );
    client.println(server);
    client.println( "Connection: close" );
    client.println();
    client.println();
    client.stop();
  }
  else {
    // you didn't get a connection to the server:
    Serial.println("--> connection failed/n");
  }
  
  
  return finger.fingerID; 

}
