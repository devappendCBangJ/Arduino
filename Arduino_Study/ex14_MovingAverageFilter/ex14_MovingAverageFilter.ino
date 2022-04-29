// PSD AverageFilter 예제 : https://www.youtube.com/watch?v=J-UGRCmYXYY
// 시리털 플로터 활용

#define num 20
float sensorValues[num];
float filteredValue = 0;

void setup() {
  // 초기 설정
  Serial.begin(9600);
}

void loop() {
  // 배열을 한칸씩 앞으로 당김
  for (int i = 0; i < num - 1; i++){
    sensorValues[i] = sensorValues[i + 1];
  }

  // 값 읽기 + 배열 마지막에 새로운값 대입
  sensorValues[num - 1] = analogRead(A0);

  // MovingAverageFilter 연산
  filteredValue = 0;
  for (int i = 0; i < num; i++){
    filteredValue += sensorValues[i];
  }
  filteredValue /= num;
  delay(10);

  // MovingAverageFilter값 출력
  Serial.print(sensorValues[num - 1]);
  Serial.print(",");
  Serial.println(filteredValue);
}
