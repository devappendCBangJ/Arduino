#include <Servo.h>
#include "PPMReader.h"
#include <Wire.h>
#include <SoftwareSerial.h>
//----------------------------제어주기-----------------------
#define MCU_CONTROL_RATE 8
// ------------------------------motor-----------------------------------------
#define MIN_PULSE_LENGTH 1000
#define MAX_PULSE_LENGTH 2000

Servo motA, motB, motC, motD;
char data;
int motorA, motorB, motorC, motorD;
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡppm엔코더ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ//
byte interruptPin = 2;
byte chAmount = 8;
PPMReader ppm(interruptPin, chAmount);
double ch_array[9];

unsigned long t=0;
int prev_ch_array = 1000;
int throttle;
//-------------MPU----------------------------------------------
const int MPU_ADDR = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
double angleAcX, angleAcY, angleAcZ;
double angleGyX, angleGyY, angleGyZ;
double angleFiX, angleFiY, angleFiZ;
double angvelFiX, angvelFiY, angvelFiZ;

const double RADIAN_TO_DEGREE = 180 / 3.14159;  
const double DEG_PER_SEC = 32767 / 250;    // 1초에 회전하는 각도
const double ALPHA = 0.992;

unsigned long now = 0;   // 현재 시간 저장용 변수
unsigned long past = 0;  // 이전 시간 저장용 변수
unsigned long until = 0;
double dt = 0;           // 한 사이클 동안 걸린 시간 변수 

double now_DT = 0;           // 한 사이클 동안 걸린 시간 변수 
double past_DT = 0;           // 한 사이클 동안 걸린 시간 변수 
double DT = 0;           // 한 사이클 동안 걸린 시간 변수 
double free_dt = 0;

double averAcX, averAcY, averAcZ;
double averGyX, averGyY, averGyZ;
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ이중루프 PIDㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
float roll_target_angle = 0;
float roll_angle_in;
float roll_rate_in;
float roll_stabilize_kp = 3;
float roll_stabilize_ki = 0.01;
float roll_rate_kp = 0.4;
float roll_rate_ki = 1;
float roll_rate_kd = 0.015;
float roll_stabilize_iterm;
float roll_rate_iterm;
float roll_rate_dterm;
float roll_output;

float pitch_target_angle = 0;
float pitch_angle_in;
float pitch_rate_in;  
float pitch_stabilize_kp = 3.5;
float pitch_stabilize_ki = 0;
float pitch_rate_kp = 0.4;
float pitch_rate_ki = 0;
float pitch_rate_kd = 0.0001;
float pitch_stabilize_iterm;
float pitch_rate_iterm;
float pitch_rate_dterm;
float pitch_output;
float pitch_output_prev;

float yaw_target_angle = 0.0;
float yaw_angle_in;
float yaw_rate_in;
float yaw_stabilize_kp = 1;
float yaw_stabilize_ki = 0;
float yaw_rate_kp = 0.4;
float yaw_rate_ki = 0;
float yaw_rate_kd = 0;
float yaw_stabilize_iterm;
float yaw_rate_iterm;
float yaw_rate_dterm;
float yaw_output;

void setup()
{
  Serial.begin(115200);

  initMPUSensor();
  
  motA.attach(3, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  motB.attach(5, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  motC.attach(6, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  motD.attach(9, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  
  motA.writeMicroseconds(MIN_PULSE_LENGTH);
  motB.writeMicroseconds(MIN_PULSE_LENGTH);
  motC.writeMicroseconds(MIN_PULSE_LENGTH);
  motD.writeMicroseconds(MIN_PULSE_LENGTH);

  delay(5000);

  caliSensor();
  past = millis();
}
 

void loop()
{
  past_DT = free_dt;
  
  getangle();

  for (byte ch = 0; ch <= chAmount; ++ch)
  {
    ch_array[ch] = ppm.latestValidChannelValue(ch, 0);
  }

  if (ch_array[4] < 1090) ch_array[4] = 1000;
  ch_array[4] = map(ch_array[4], 1100, 1904, 1000, 2000);
  if (ch_array[4] == 0) ch_array[4] = prev_ch_array;

  ch_array[8] = mapping((double)ch_array[8], 1100.0, 1904.0, 15.0, -15.0);
  ch_array[2] = mapping((double)ch_array[2], 1100.0, 1904.0, 15.5, -14.5);
  ch_array[3] = mapping((double)ch_array[3], 1100.0, 1904.0, -15.0, 15.0);
  
  throttle = ch_array[4];
  pitch_target_angle = ch_array[8];
  roll_target_angle = ch_array[2];
  yaw_target_angle = ch_array[3];
  
  if(throttle < 1050)
  {
    motorA = throttle;
    motorB = throttle;
    motorC = throttle;
    motorD = throttle;
  }
  else if(throttle >= 1050)
  {
    calcYPRtoDualPID();
    
    motorA = throttle - pitch_output;// - roll_output + yaw_output;
    motorB = throttle - pitch_output;// + roll_output - yaw_output;
    motorC = throttle + pitch_output;// - roll_output - yaw_output;
    motorD = throttle + pitch_output;// + roll_output + yaw_output;
  }
  
  motA.writeMicroseconds(motorA);
  motB.writeMicroseconds(motorB);
  motC.writeMicroseconds(motorC);  
  motD.writeMicroseconds(motorD);

  while(free_dt - past_DT < MCU_CONTROL_RATE)
  {
    free_dt = millis();
  }

  dt = (free_dt - past_DT)/1000.0;
  
  Serial.print(pitch_target_angle);
  Serial.print('\t');
  Serial.println(angleFiY);
;
  
}

void initMPUSensor()
{
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);   // I2C 통신용 어드레스(주소)
  Wire.write(0x6B);    // MPU6050과 통신을 시작하기 위해서는 0x6B번지에    
  Wire.write(0);
  Wire.endTransmission(true);

  Wire.write(0x1A);    //   
  Wire.write(0x03);     //  DLPF 10Hz = 0x05, DLPF 260Hz = 0x00 //0x02 42Hz 0x03
  Wire.endTransmission(true);

  Wire.write(0x1C);    //   
  Wire.write(0x10);     //
  Wire.endTransmission(true);  
}

void getangle()
{
  getData();

  double las_angle_gx = angleFiX;
  double las_angle_gy = angleFiY;
  double las_angle_gz = angleFiZ;

  angleAcX = atan(AcY / sqrt(pow(AcX, 2) + pow(AcZ, 2))) * 180 / PI;
  //angleAcX *= RADIAN_TO_DEGREE;
  angleAcY = atan(-AcX / sqrt(pow(AcY, 2) + pow(AcZ, 2))) * 180 / PI;
  //angleAcY *= RADIAN_TO_DEGREE;

  angvelFiX = ((GyX - averGyX) / DEG_PER_SEC);
  angvelFiY = ((GyY - averGyY) / DEG_PER_SEC);
  angvelFiZ = ((GyZ - averGyZ) / DEG_PER_SEC);
  
  double angleTmpX = las_angle_gx + angvelFiX * dt;
  double angleTmpY = las_angle_gy + angvelFiY * dt;
  double angleTmpZ = las_angle_gz + angvelFiZ * dt;

  angleFiX = ALPHA * angleTmpX + (1.0 - ALPHA) * angleAcX;
  angleFiY = ALPHA * angleTmpY + (1.0 - ALPHA) * angleAcY;
  angleFiZ = angleGyZ;

  if(angleFiZ >= 360)
  {
    angleFiZ = angleFiZ - 360;
  }
  else if(angleFiZ <= -360)
  {
    angleFiZ = angleFiZ + 360;
  }
  
}

void getData()
{
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);
  
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();
}

void caliSensor()
{
  double sumAcX = 0 , sumAcY = 0, sumAcZ = 0;
  double sumGyX = 0 , sumGyY = 0, sumGyZ = 0;
  
  getData();
  
  for (int i=0;i<100;i++) {
    getData();
    sumAcX+=AcX;  sumAcY+=AcY;  sumAcZ+=AcZ;
    sumGyX+=GyX;  sumGyY+=GyY;  sumGyZ+=GyZ;
    delay(5);
  }
  
  averAcX=sumAcX/100;  averAcY=sumAcY/100;  averAcZ=sumAcY/100;
  averGyX=sumGyX/100;  averGyY=sumGyY/100;  averGyZ=sumGyZ/100;
}

void dualPID(float target_angle,
             float angle_in,
             float rate_in,
             float stabilize_kp,
             float stabilize_ki,
             float rate_kp,
             float rate_ki,
             float rate_kd,
             float &stabilize_iterm,
             float &rate_iterm,
             float &rate_dterm,
             float &output
             ){
  float angle_error;
  float desired_rate;
  float rate_error;
  float stabilize_pterm, rate_pterm;
  float rate_prev_dterm;
  float prev_rate;
  
  angle_error = target_angle - angle_in;

  stabilize_pterm = stabilize_kp * angle_error;
  stabilize_iterm += stabilize_ki * angle_error * dt; //안정화 적분항//

  desired_rate = stabilize_pterm;

  rate_error = desired_rate - rate_in;
  
  rate_pterm = rate_kp * rate_error; //각속도 비례항//
  rate_iterm += rate_ki * rate_error * dt; //각속도 적분항//
  rate_dterm = -((rate_in - prev_rate)/dt)*rate_kd;

  rate_dterm = rate_prev_dterm*0.9 + rate_dterm*0.1;

  if(stabilize_iterm > 100)
  {
    stabilize_iterm = 100;
  }
  else if(stabilize_iterm < -100)
  {
    stabilize_iterm = -100;
  }

  if(rate_iterm > 50)
  {
    rate_iterm = 50;
  }
  else if(rate_iterm < -50)
  {
    rate_iterm = -50;
  }
  
  output = rate_pterm + rate_iterm + stabilize_iterm + rate_dterm;

  prev_rate = rate_in;
}

void calcYPRtoDualPID(){
  roll_angle_in = angleFiX;
  roll_rate_in = angvelFiX;

  dualPID(roll_target_angle,
          roll_angle_in,
          roll_rate_in,
          roll_stabilize_kp,
          roll_stabilize_ki,
          roll_rate_kp,
          roll_rate_ki,
          roll_rate_kd,
          roll_stabilize_iterm,
          roll_rate_iterm,
          roll_rate_dterm,
          roll_output
  );

  pitch_angle_in = angleFiY;
  pitch_rate_in = angvelFiY;

  dualPID(pitch_target_angle,
          pitch_angle_in,
          pitch_rate_in,
          pitch_stabilize_kp,
          pitch_stabilize_ki,
          pitch_rate_kp,
          pitch_rate_ki,
          pitch_rate_kd,
          pitch_stabilize_iterm,
          pitch_rate_iterm,
          pitch_rate_dterm,
          pitch_output
  );
  
  yaw_angle_in = angleFiZ;
  yaw_rate_in = angvelFiY;

  dualPID(yaw_target_angle,
          yaw_angle_in,
          yaw_rate_in,
          yaw_stabilize_kp,
          yaw_stabilize_ki,
          yaw_rate_kp,
          yaw_rate_ki,
          yaw_rate_kd,
          yaw_stabilize_iterm,
          yaw_rate_iterm,
          yaw_rate_dterm,
          yaw_output
  );
}

double mapping(float x, float b, float c, float d, float e)
{
  double k = ((d-e)/(b-c));
  double result = k*(x-1500)+((d+e)/2);

  return result;
}
