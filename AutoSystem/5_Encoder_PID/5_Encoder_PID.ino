// 타이머 변수
uint16_t MCU_TIMER_start;
#define MCU_CONTROL_RATE 10

void timer_loop(unsigned int mcu_ms)
{
  while((uint16_t)millis()-MCU_TIMER_start <=mcu_ms);
  MCU_TIMER_start = (uint16_t)millis();
}

// 핀 변수
const int motorPWMPin = 6;
const int motorDirPin1 = 8;
const int motorDirPin2 = 9;

const int encoderPinA = 2;
const int encoderPinB = 3;

// 엔코더 변수
int encoderPos=0;
const float ratio= 360./10./12.;

// PID 변수
float Kp=1;
float Ki=0;
float Kd=0;
float Ltime = 0.01;
float P_control, I_control, D_control;
float control;
float targetDeg;
float motorDeg;
float error;
float error_previous;

// 엔코더 읽기
int flag=0; 
void doEncoderA() { encoderPos +=(digitalRead(encoderPinA)==digitalRead(encoderPinB))?1:-1;}
void doEncoderB() { encoderPos +=(digitalRead(encoderPinA)==digitalRead(encoderPinB))?-1:1;}

String gainData;
float Target;

// PWM to MOTOR
void doMotor(bool dir, int vel){
  digitalWrite(motorDirPin1, !(dir));
  digitalWrite(motorDirPin2, dir);
  analogWrite(motorPWMPin, min(vel,255));
}

void setup(){
  // 핀모드 + 인터럽트
  pinMode(encoderPinA, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA, CHANGE);
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(1, doEncoderB, CHANGE);
  pinMode(motorDirPin1, OUTPUT);
  pinMode(motorDirPin2, OUTPUT);
  Serial.begin(115200);
}

void loop(){
  // 제어 주기 고정
  timer_loop(MCU_CONTROL_RATE);

  // 통신
  if(Serial.available()){
    // 통신값 읽기
    gainData = Serial.readStringUntil('\r');

    // 통신값 슬라이싱
    unsigned int gainDataLength = gainData.length();
    unsigned int index[3];
    String temp;

    index[0] = gainData.indexOf("*");
    index[1] = gainData.indexOf(",");

    temp = gainData.substring(index[0]+1, index[1]);
    flag = temp.toInt();
    temp = gainData.substring(index[1]+1, gainDataLength);
    Target = temp.toFloat();

    // target PID 설정
    switch(flag) {
      case 1: Kp = Target; encoderPos = 0; break;
      case 2: Ki = Target; encoderPos = 0; break;
      case 3: Kd = Target; encoderPos = 0; break;
      case 4: targetDeg = Target; encoderPos = 0; break;
      default: Target = 0; break;
    }
  }

  // PID 적용
  motorDeg= float(encoderPos)*ratio;
  error = targetDeg-motorDeg;
  P_control = (Kp*error);
  I_control += (Ki*error*Ltime);
  D_control = Kd*(error-error_previous)/(Ltime);
  control = P_control+I_control+D_control;
  error_previous = error;

  // 모터 PWM 작동
  doMotor( (control>=0)?HIGH:LOW, min(abs(control),255));

  // 시리얼 출력
  Serial.print("encoderPos : ");
  Serial.print(encoderPos);
  Serial.print("    motorDeg : ");
  Serial.print(float(encoderPos)*ratio);
  Serial.print("    error : ");
  Serial.print(error);
  Serial.print("    contorl : ");
  Serial.print(control);
  Serial.print("    motorVel : ");
  Serial.print(min(abs(control), 255));
  Serial.print(" Kp : ");
  Serial.print(Kp);
  Serial.print(" Ki : ");
  Serial.print(Ki);
  Serial.print(" Kd : ");
  Serial.println(Kd);
}
