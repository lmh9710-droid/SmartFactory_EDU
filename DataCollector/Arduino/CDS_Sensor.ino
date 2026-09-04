int pinGnd = A2;
int pinVcc = A1; 
int pinCds = A0;

void setup(){
   Serial.begin(115200);

    pinMode(pinGnd, OUTPUT);
    pinMode(pinVcc, OUTPUT);
    pinMode(pinCds, INPUT);
    digitalWrite(pinGnd, LOW);
    digitalWrite(pinVcc, HIGH); 
}

void loop(){
   delay(5000);
  int adcData = analogRead(pinCds);
  Serial.println(adcData);

}