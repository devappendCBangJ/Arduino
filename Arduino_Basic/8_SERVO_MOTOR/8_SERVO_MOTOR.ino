#include <Servo.h> //서보관련 라이브러리를 사용하기 위해

Servo myservo;  // 서보 변수 선언
int servoPin = 9; // 서보 핀

void setup() {
  myservo.attach(servoPin); //서보로 9핀 사용하겠다고 설정 
}

void loop() {
  myservo.write(0);  //0도로 이동             
  delay(1000);       //1초 대기                 
  myservo.write(90); //90도로 이동            
  delay(1000);       //1초 대기
  myservo.write(180);//180도로 이동             
  delay(1000);       //1초 대기 다시 처음으로 돌아감                
}
