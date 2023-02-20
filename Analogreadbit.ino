

int analogpin = A0;   
int samplingPeriod;     
unsigned long prevtime ,currtime,elapsedtime;
byte val;
byte pins[]={4,5,6,7};

void setup() {
  samplingPeriod = 1;
  prevtime = 0;
  val = 0;
}

void loop() {
  currtime = millis();
  elapsedtime = currtime- prevtime;
  if (elapsedtime >= samplingPeriod){
    val = analogRead(analogpin)>>2;
    for (byte i=0; i<4; i++){
      byte state = bitRead(val,i+4);
      digitalWrite(pins[i],state);
    }
    prevtime = currtime;
  }
}
