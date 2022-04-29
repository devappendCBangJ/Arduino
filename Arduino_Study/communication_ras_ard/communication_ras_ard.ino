// 라이브러리 불러오기
#include <Servo.h>

// 서보 객체 생성
Servo myServo;
int servo_angle;

void setup(){
  Serial.begin(115200);                 // Serial통신 속도(아두이노-컴퓨터 통신용)
  Serial1.begin(115200);                // Serial1통신 속도(라즈베리파이-아두이노 통신용)
  myServo.attach(8);                    // 서보 제어핀 할당
  myServo.write(0);                     // 서보 0도 초기화
}

void loop(){
  if(Serial1.available()>0){
    while(Serial1.available()>0){
      servo_angle = Serial1.parseInt(); // Serial1 통신값 숫자 변환
    }

    myServo.write(servo_angle);           // Serial1 통신값에 의해 서보 회전
  
    Serial.print("set to ");              // Serial포트로 메시지 작성(컴퓨터에서 확인용)
    Serial.println(servo_angle);          // Serial포트로 각도값 작성(컴퓨터에서 확인용)
    delay(5);
  }

  delay(100);
}
