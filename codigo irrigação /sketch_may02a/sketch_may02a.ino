int umidade;
  
void setup()
{
 Serial.begin(9600);
 pinMode(13, OUTPUT);
}
void loop()
{
 umidade = analogRead(A0);
 int Porcento = map(umidade, 1023, 0, 0, 100);
 Serial.println(Porcento);
 if(Porcento <=70)
 {
 Serial.println("Irrigando...");
 digitalWrite(13, LOW);
 }
  
 else
 {
 digitalWrite(13, HIGH);
 }
 delay(1000);
}
