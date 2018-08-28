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
commit:8194ac
Iniciando a Sketch
