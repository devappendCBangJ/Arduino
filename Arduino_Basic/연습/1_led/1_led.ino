int led1=8;
int led2=9;
int led3=10;

void setup() {
  pinMode(led1,OUTPUT); // 몇 번 핀을 전기 출력으로 사용  pinMode(숫자,용도)
}

void loop() {
  digitalWrite(led1,HIGH); // 몇 번 핀을 ON  digitalWrite(숫자, 용도)
  delay(100);
  digitalWrite(led1,LOW); // 몇 번 핀을 OFF  digitalWrite(숫자, 용도)
  delay(100);
  digitalWrite(led2,HIGH); // 몇 번 핀을 ON  digitalWrite(숫자, 용도)
  delay(100);
  digitalWrite(led2,LOW); // 몇 번 핀을 OFF  digitalWrite(숫자, 용도)
  delay(100);
  digitalWrite(led3,HIGH); // 몇 번 핀을 ON  digitalWrite(숫자, 용도)
  delay(100);
  digitalWrite(led3,LOW); // 몇 번 핀을 OFF  digitalWrite(숫자, 용도)
  delay(100);
}
