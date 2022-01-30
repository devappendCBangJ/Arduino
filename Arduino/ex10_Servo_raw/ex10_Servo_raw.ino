// 서보모터 예제 : https://codingrun.com/110 # 완료
// 서보모터 예제 : https://m.blog.naver.com/yuyyulee/220345769854 # 완료
// 서보모터 예제 : https://m.blog.naver.com/yuyyulee/220345802387 # 완료

// 1. 서보모터 사용 순서
 // 1) 모듈 불러오기 : #include<Servo.h>
 // 2) 서보 객체 생성 : Servo servo_name;
 // 3) 서보 핀 설정 : servo_name.attach(pin_name, min_pulse_width, max_pulse_width);
  // min_pulse_width 기본값 : 544마이크로초
  // max_pulse_width 기본값 : 2400마이크로초
 // 4) 서보 움직임 by degree : servo_name.write(degree);
 // 4) 서보 움직임 by microsecond : servo_name.writeMicroseconds(us);
 // 4) 무한회전 서보 움직임 : servo_name.write(n);
  // - n
    // 0 : 정방향 회전 최고속도
    // 0 ~ 90 : 정방향 회전
    // 90 : 정지
    // 90 ~ 180 : 역방향 회전
    // 180 : 역방향 회전 최고속도
  // 5) 서보 객체 해제 : servo_name.detach();

int servoPin = 6; // ●핀 번호
int freq = 20000; // ●주기 : 20ms, 주파수 : 50Hz
int minPulse = 600; // ●최소 각도 us
int maxPulse = 2400; // ●최대 각도 us

// 초기 설정
void setup() {
 pinMode(servoPin, OUTPUT); // ●핀 설정
 digitalWrite(servoPin, LOW); // ●디지털 출력
}

// 모터 0 ~ 180도 왕복
void loop() {
  for(int i = 0; i <= 180; i++){
    setServo(i);
  }

  for(int i = 180; i >= 0; i--){
    setServo(i);
  }
}

void setServo(int degree){
  int hTime = 0;
  int lTime = 0;

  if(degree < 0) degree = 0;
  if(degree > 180) degree = 180;

  hTime = (int)(minPulse + ((maxPulse-minPulse) / 180.0 * degree)); // ●펄스 ON 지속을 위한 딜레이 초
  lTime = freq - hTime; // ●펄스 OFF 지속을 위한 딜레이 초

  digitalWrite(servoPin, HIGH); // ●펄스 ON
  delayMicroseconds(hTime); // ●펄스 ON 지속을 위한 딜레이
  digitalWrite(servoPin, LOW); // ●펄스 OFF
  delayMicroseconds(lTime); // ●펄스 OFF 지속을 위한 딜레이
}
