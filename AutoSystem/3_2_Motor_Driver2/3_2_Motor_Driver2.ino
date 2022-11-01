#include <Arduino.h>

///MCU TIMER///
uint16_t MCU_TIMER_start;
#define MCU_CONTROL_RATE 10

void timer_loop(unsigned int mcu_ms)
{
  while((uint16_t)millis()-MCU_TIMER_start <=mcu_ms);
  MCU_TIMER_start = (uint16_t)millis();
}

const int motor_PWMpin = 6; // L298 Input ENA
const int motor_Dirpin1 = 8; // L298 Input 1
const int motor_Dirpin2 = 9; // L298 Input 2

const int encoderPinA = 2;
const int encoderPinB = 3;

int encoderPos = 0;

float motorDeg;
const float ratio = 360./10./12.; // 실제 각도 = 360도 / 기어비 / 틱

String PWM_data = "";
int PWM_value = 0;

void doEncoderA() { encoderPos +=(digitalRead(encoderPinA)==digitalRead(encoderPinB))?1:-1;}
void doEncoderB() { encoderPos +=(digitalRead(encoderPinA)==digitalRead(encoderPinB))?-1:1;}

void doMotor(bool dir, uint16_t vel)
{
  digitalWrite(motor_Dirpin1, !(dir));
  digitalWrite(motor_Dirpin2, dir);
  analogWrite(motor_PWMpin, min(vel,255));
}
void setup() {
  pinMode(encoderPinA, INPUT);
  attachInterrupt(0, doEncoderA, CHANGE); // 1개 : 6틱
  pinMode(encoderPinB, INPUT);
  attachInterrupt(1, doEncoderB, CHANGE); // 2개 : 12틱
  pinMode(motor_Dirpin1, OUTPUT);
  pinMode(motor_Dirpin2, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  timer_loop(MCU_CONTROL_RATE);
  if(Serial.available()){
    PWM_data = Serial.readStringUntil('\n');
    PWM_value = PWM_data.toInt();
  }
  
  motorDeg= float(encoderPos)*ratio;
  if(motorDeg>=3600) PWM_value = 0;
  
  doMotor((PWM_value >=0) ? HIGH : LOW, min(abs(PWM_value),255));
  Serial.print("PWM : ");
  Serial.print(PWM_value);
  Serial.print("  encoderPos : ");
  Serial.print(encoderPos);
  Serial.print("  rev_count : ");
  Serial.println(motorDeg/360.);
}
