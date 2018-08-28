#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <TFT.h>


//pinos SD
#define SD_CS  10


//pinos display
#define LCD_CS 7
#define DC    8
#define RESET    9


// variavel
int op = 0;

//Display
TFT tela = TFT(LCD_CS, DC, RESET);
PImage image;

//biometrico
uint8_t id;
uint8_t cadastrarDedo();
SoftwareSerial mySerial(5,6);
Adafruit_Fingerprint dedo = Adafruit_Fingerprint(&mySerial);



void setup()  {
  Serial.begin(9600);
  
  
  Serial.available();
 //iniciar o LCD
 tela.begin();
 tela.background(0, 0, 0);
  
  
  // inicializa o cartao
  Serial.print("Inicializando SD card......................");
  if (!SD.begin(SD_CS)) {
    Serial.println("failed!");
   return;
  }
  Serial.println("OK!");
  
  //iniciar leitor
  Serial.print("Inicializando Leitor biometrico............");
  if(dedo.verifyPassword()){
    Serial.println("OK!");
    return;
  }else{
  Serial.println("failed!");
  }
  
  //logo
    image = tela.loadImage("ifms.bmp");
    tela.setRotation(0);
    tela.image(image,0,0);
    
  opcao();
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


void opcao(){
  Serial.println("Digite a opçao(1 para cadastrar e 2 para validar)");
  op = Serial.read();
  Serial.available();
  if(op == '1'){
    cadastrarDedo();
  }
  if(op == '2'){
     validar();
  }else{
  Serial.println("Digite uma opçao valida");
  }

}

 uint8_t cadastrarDedo(){
  
  int p = -1;
  Serial.print("Esperando digital para inscrever #");
  Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = dedo.getImage();
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

  p = dedo.image2Tz(1);
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
    p = dedo.getImage();
  }
  Serial.print("ID ");
  Serial.println(id);
  p = -1;
  Serial.println("Coloque o mesmo dedo novamente");
  while (p != FINGERPRINT_OK) {
    p = dedo.getImage();
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

  p = dedo.image2Tz(2);
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

  p = dedo.createModel();
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
  p = dedo.storeModel(id);
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
void validar(){



}




void loop(){}



