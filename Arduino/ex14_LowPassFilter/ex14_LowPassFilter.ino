// PSD LowPassFilter 예제 : https://www.youtube.com/watch?v=JezOJN1yhTA
// 시리얼 플로터 활용

float sensorValue;
float filteredValue;
float weight = 0.15;

void setup() {
  // 초기 설정
  Serial.begin(9600);
  sensorValue = analogRead(A0);
  filteredValue = sensorValue;
}

void loop() {
  // 값 읽기 + LowPassFilter 연산
  sensorValue = analogRead(A0);
  filteredValue = filteredValue * (1-weight) + sensorValue * weight;
  delay(10);

  // LowPassFilter값 출력
  Serial.print(sensorValue);
  Serial.print(",");
  Serial.println(filteredValue);
}
