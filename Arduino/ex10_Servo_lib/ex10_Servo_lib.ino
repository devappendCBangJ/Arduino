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

#include <Servo.h> // ●Servo 라이브러리 추가
Servo myservo; // ●Servo 객체 생성
int pos = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(9, 600, 2400); // ●Servo 핀 설정
}

void loop() {
  for(pos = 0; pos <= 180; pos += 1){
    myservo.write(pos); // ●서보 움직임 by degree
    delay(15);
  }
  for(pos = 180; pos >= 0; pos -= 1){
    myservo.write(pos);
    delay(15);
  }
}
