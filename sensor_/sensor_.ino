

int sensorPin = A1;     // select the input pin for the potentiometer
int ledPin = 4;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int valorConvertido = 0;
void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);  
  Serial.begin(9600);
}

void loop() {      
      sensorValue = analogRead(sensorPin); 
      valorConvertido=map(sensorValue,0,1023,0,255);
 
       Serial.println(valorConvertido ); 
       

        tone(ledPin, valorConvertido);  

    delay(100);
}
