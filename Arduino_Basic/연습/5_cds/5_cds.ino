int cds=9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // 컴퓨터와 아두이노 보드 간의 통신
  pinMode(cds,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int save_cds=digitalRead(cds); // 들어오는 신호를 0과 1로 받아들임
  Serial.println(save_cds); // 시리얼 모니터창에 프린트, ln는 자동엔터
  delay(300);
}
