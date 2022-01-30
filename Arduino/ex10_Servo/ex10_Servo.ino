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

#include<Servo.h> // ●Servo 라이브러리를 추가
Servo servo;      // ●Servo 클래스로 servo객체 생성
int value = 0;    // ●각도를 조절할 변수 value

void setup() {
  servo.attach(7);     // ●맴버함수인 attach : 핀 설정
  Serial.begin(9600); // 시리얼 모니터 사용 고고
}

void loop() {
  if(Serial.available())      // 시리얼 모니터에 데이터가 입력되면
  {
    char in_data;             // 입력된 데이터를 담을 변수 in_data
    in_data = Serial.read(); // 시리얼 모니터로 입력된 데이터 in_data로 저장
    Serial.println(in_data);
    if(in_data == '1')        // 입력된 데이터가 1이라면
    {
      value += 30;            // 각도를 30도 증가시킨다.
      if(value == 210)        // 각도가 210도가 되면 (180도보다 커지면)
        value = 0;            // 각도를 0으로 초기화
      Serial.println(value);
    }

    else if(in_data != 1 && in_data != '\n')   // 그외의 데이터가 입력되면
      value = 0;              // 각도를 0으로 초기화
      
    servo.write(value); // ●value값의 각도로 회전. ex) value가 90이라면 90도 회전
  }
}
