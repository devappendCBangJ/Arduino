int in1 = 7;  //in1 7번 포트로 제어 (OUT1)
int in2 = 5;  //in2 5번 포트로 제어 (OUT2)

void setup() {
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); //각 포트 출력으로 사용
  Serial.begin(9600);  //시리얼모니터 사용
}

void loop() {
  if(Serial.available())  //시리얼모니터에서 데이터가 들어오면
  {
    char in_data;         // 입력된 데이터 저장을 위한 변수
    in_data = Serial.read();  //입력된 데이터 in_data에 저장
    if(in_data == '1')    //입력된 데이터가 '1'이라면
    {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);   //앞으로 회전
    }
    else if(in_data == '2') //입력된 데이터가 '2'라면
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);  //뒤로 회전 (어떤 방향으로 꽂았느냐에 따라서 방향 반대)
    }
    else  // 그 이외의 값에서는
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);  //회전 정지
    }
  }
}
