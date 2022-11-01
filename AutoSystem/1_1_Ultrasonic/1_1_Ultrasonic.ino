#define echo 2
#define trig 4

int read_ultrasonic(){
  float duration, distance;
  
  // 10us 동안 trig핀 high로 설정
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  duration = pulseIn(echo, HIGH); // echo 시간 측정
  distance = duration * 0.034 / 2;
  return distance;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  // 측정 거리 출력
  Serial.print("Ultrasonic value : ");
  Serial.println(read_ultrasonic());
  delay(100);
}
