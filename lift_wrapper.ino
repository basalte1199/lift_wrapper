int PUL=7; //define Pulse pin
int DIR=6; //define Direction pin
int ENA=5; //define Enable Pin
int DIN=10;

int liftcount = 0;
void setup() {
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  pinMode (ENA, OUTPUT);

  pinMode (DIN, INPUT);

  int value = digitalRead(DIN);
  Serial.begin(9600);
  Serial.println("start calibration");
  Serial.println(value);

  while(value == 1){
    digitalWrite(DIR,LOW);
    digitalWrite(ENA,HIGH);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(50);
    digitalWrite(PUL,LOW);
    delayMicroseconds(50);
    value = digitalRead(DIN);
  }


}


void loop() {

  if (Serial.available() > 0){
    int data = Serial.parseInt();
    //mm単位のプラマイ
    liftcount = liftcount + data;
    if (liftcount < 0 or liftcount > 180){
      Serial.println("error");
      liftcount = liftcount - data;
      return;
    }
    long absdata = abs(data);
    long step = absdata *1600; // /4*6400
    Serial.println(data);
    Serial.println(absdata);
    Serial.println(step);
    if (data > 0){
      for (long i=0; i<step; i++)    //Forward 5000 steps
      {
        digitalWrite(DIR,HIGH);
        digitalWrite(ENA,HIGH);
        digitalWrite(PUL,HIGH);
        delayMicroseconds(100);
        digitalWrite(PUL,LOW);
        delayMicroseconds(100);
      } 
    }else{
      for (long i=0; i<step; i++)    //Forward 5000 steps
      {
        digitalWrite(DIR,LOW);
        digitalWrite(ENA,HIGH);
        digitalWrite(PUL,HIGH);
        delayMicroseconds(100);
        digitalWrite(PUL,LOW);
        delayMicroseconds(100);
      } 
    }

  }
}