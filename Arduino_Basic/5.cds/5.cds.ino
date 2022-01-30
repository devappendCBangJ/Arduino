int cds=8;

void setup(){
  Serial.begin(9600); // 컴퓨터와 아두이노 보드 간의 통신
  pinMode(cds,INPUT);
}

void loop(){
int save_cds=digitalRead(cds);
Serial.println(save_cds);
delay(1000);
}
