int led=7;
int sw=8;

void setup() {
pinMode(sw,INPUT);
pinMode(led,OUTPUT);
Serial.begin(9600);
}

void loop() {
 int button=digitalRead(sw);
 Serial.println(button);
 if(button == 1){
  digitalWrite(led,HIGH);
  delay(3000);
  }
 else{
  digitalWrite(led,LOW); }
 delay(200);
  }

