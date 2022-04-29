// PSD AverageFilter 예제 : https://www.youtube.com/watch?v=J-UGRCmYXYY
// 시리털 플로터 활용

#define num 20
float sensorValues[num];
float filteredValue = 0;
int j = 0;
int temp;

void setup() {
  // 초기 설정
  Serial.begin(9600);
  for (int i = 0; i < num -1; i++){
    sensorValues[i] = analogRead(A0);
    filteredValue += sensorValues[i];
  }
  filteredValue /= num;
}

void loop() {
  // 값 읽기 + 가장 오래된 값에 새로운값 대입
  temp = sensorValues[j];
  sensorValues[j] = analogRead(A0);

  // MovingAverageFilter 연산
  filteredValue = (filteredValue * num) - temp + sensorValues[j];
  filteredValue /= num;
  delay(10);

  // MovingAverageFilter값 출력
  Serial.print(sensorValues[j]);
  Serial.print(",");
  Serial.println(filteredValue);

  j++;
  if (j == 20){
    j = 0;
  }
}
