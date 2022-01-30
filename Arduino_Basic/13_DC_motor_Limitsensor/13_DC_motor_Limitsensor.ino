int limit=7;
int relay=8;

void setup() {
pinMode(limit,INPUT);
pinMode(relay,OUTPUT);
Serial.begin(9600);

}

void loop() {
int save_limit=digitalRead(limit);
Serial.println(save_limit);

if(save_limit==0){
  digitalWrite(relay,HIGH);
  delay(5000);
  digitalWrite(relay,LOW);}
  
  else {
  digitalWrite(relay,LOW); }
  
 delay(500);
 }
  

