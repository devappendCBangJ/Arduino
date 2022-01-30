int trig=7;
int echo=8;

void setup() {
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);
Serial.begin(9600);
}

void loop() {

  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

int distance = pulseIn(echo, HIGH)*340/2/10000;

  Serial.print("distance : ");
  Serial.print(distance);
  Serial.println("cm");

  delay(1000); // 1초에 한번씩 측정
}
