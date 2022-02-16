// PSD AverageFilter 예제 : https://www.youtube.com/watch?v=J-UGRCmYXYY
// 시리털 플로터 활용

void setup() {
  // 초기 설정
  Serial.begin(9600);
}

void loop() {
  // 값 읽기 + AverageFilter 연산
  int sensorValue = analogRead(A0);
  float filteredValue = 0;
  for(int i=0 ; i<100 ; i++){
    filteredValue += analogRead(A0);
    delayMicroseconds(10);
  }
  filteredValue /= 100;

  // AverageFilter값 출력
  Serial.print(sensorValue);
  Serial.print(",");
  Serial.println(filteredValue);
}
