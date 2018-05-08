#include <TFT.h> // Hardware-specific library
#include <SPI.h>

#define CS   10
#define DC   9
#define RESET  8  

int botao = 2;
// pin definition for the Leonardo
// #define CS   7
// #define DC   0
// #define RESET  1

TFT myScreen = TFT(CS, DC, RESET);

// variable to keep track of the elapsed time
int counter = 0;
// char array to print time
char printout[4];

void setup(){
  pinMode(botao,INPUT);
  myScreen.begin();  
 myScreen.setRotation(1);
  myScreen.setTextSize(2);
  myScreen.background(0,0,0); // clear the screen
  myScreen.stroke(255,255,255);
  // static text
  myScreen.text("Atualizando",15,45);  
  // increase font size for text in loop()
  
}
void loop(){
  estadoBotao = digitalRead(botao);
  if(botao == 1){
    myScreen.background(0,0,0); // clear the screen
    myScreen.stroke(255,255,255);
    myScreen.text("aprovado",15,45);  
  }
  /*  // get elapsed time
    counter = millis();
    // convert to a string
    String elapsedTime = String(counter/1000);
    // add to an array
    elapsedTime.toCharArray(printout,4);
    // print out and erase
    myScreen.stroke(255,255,255);
    myScreen.text(printout,0,10);
    delay(1000);
    myScreen.stroke(0,0,0);
    myScreen.text(printout,0,10);*/
}

