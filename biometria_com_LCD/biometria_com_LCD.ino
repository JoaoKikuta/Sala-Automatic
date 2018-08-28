// Programa para teste de funcionamento do Leitor Biometrico
// Traduzido e adaptado por Usinainfo

#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <TFT.h>
#define SD_CS  10
#define LCD_CS 7
#define DC    9
#define RESET    8

int getFingerprintIDez();
int getFingerprintIDez();
int op;
PImage image;

uint8_t id;
uint8_t getFingerprintEnroll();

SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
TFT myScreen = TFT(LCD_CS, DC, RESET);


void setup()  {
  Serial.begin(9600);
  Serial.println("Iniciando Leitor Biometrico");

  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Leitor Biometrico Encontrado");
  } else {
    Serial.println("Leitor Biometrico nao encontrada");
    while (1);
  }

  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("failed!");
    return;
  }
  Serial.println("OK!");


  
}




uint8_t readnumber(void) {
  uint8_t num = 0;
  boolean validnum = false;
  while (1) {
    while (! Serial.available());
    char c = Serial.read();
    if (isdigit(c)) {
      num *= 10;
      num += c - '0';
      validnum = true;
    } else if (validnum) {
      return num;
    }
  }
}
   void loop()   {
     Serial.println("Digite 1 para cadastrar e 2 para validar");
  while (! Serial.available());
  op = Serial.read();
   if(op == '1'){
    //cadastrar();
   }
   if(op == '2'){
   // validar();
   }

}

uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Esperando digital para inscrever #");
  Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Imagem Capturada");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.println(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Erro ao se Comunicar");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Erro ao Capturar Imagem");
        break;
      default:
        Serial.println("Erro Desconhecido");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagem convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Imagem muito Confusa");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Erro ao se Comunicar");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Impossivel encontrar caracteristicas da digital");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Impossível encontrar características da digital");
      return p;
    default:
      Serial.println("Erro Desconhecido");
      return p;
  }

  Serial.println("Retire o dedo");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID ");
  Serial.println(id);
  p = -1;
  Serial.println("Coloque o mesmo dedo novamente");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Imagem Capturada");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Erro ao se Comunicar");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Erro ao Capturar Imagem");
        break;
      default:
        Serial.println("Erro Desconhecido");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagem Convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Imagem muito Confusa");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Erro ao se comunicar");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Nao foi possível encontrar características da impressao digital");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Nao foi possível encontrar características da impressao digital");
      return p;
    default:
      Serial.println("Erro Desconhecido");
      return p;
  }

  // OK converted!
  Serial.print("Criando cadastro para #");
  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Digital Combinada");
  }
  else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Erro ao se Comunicar");
    return p;
  }
  else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Digital nao corresponde");
    return p;
  }
  else {
    Serial.println("Erro Desconhecido");
    return p;
  }

  Serial.print("ID ");
  Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Armazenado!");
  }
  else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Erro ao se Comunicar");
    return p;
  }
  else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Impossível Armazenar Dados");
    return p;
  }
  else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Erro ao salvar na memoria");
    return p;
  }
  else {
    Serial.println("Erro Desconhecido");
    return p;
  }
}
void cadastrar(){

   Serial.println("Pronto para Cadastrar Dados! Indique o ID# o qual deve ser salvo");
  id = readnumber();
  Serial.print("Inscrever ID#");
  Serial.println(id);

  while (!  getFingerprintEnroll() );

}
void validar(){
  Serial.println("Esperando Dedo para Verificar");
  delay(1000);
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
  image = myScreen.loadImage("imagem2.bmp");
  myScreen.setRotation(1);
 myScreen.image(image, 0, 0);
 
}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  delay(1000);
  digitalWrite(11, LOW);
  delay(1000);
  digitalWrite(12, HIGH);
  Serial.print("ID # Encontrado");
  Serial.print(finger.fingerID);
  Serial.print(" com precisao de ");
  Serial.println(finger.confidence);
  return finger.fingerID;
}
