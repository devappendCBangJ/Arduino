int BLUE= 6;  // Digital input
int RED= 4;  // Digital input
int GREEN= 5;  // Digital input
int trig=7;
int echo=8;

void setup ()
{
  pinMode (RED, OUTPUT);
  pinMode (GREEN, OUTPUT);
  pinMode (BLUE, OUTPUT);
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
  
if(distance <=10){
  digitalWrite(RED,HIGH);
  delay(2000);
  digitalWrite(RED,LOW);
  }
 else if(11<distance && distance<20){
  digitalWrite(GREEN,HIGH);
  delay(2000);
  digitalWrite(GREEN,LOW);
  }
else if(distance >=21){
  digitalWrite(BLUE,HIGH);
  delay(2000);
  digitalWrite(BLUE,LOW);
  }

   delay(1000); // 1초에 한번씩 측정
}
