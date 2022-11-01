#include <Wire.h>                                               // I2C 라이브러리

const int MPU_addr = 0x68;
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ; // 계산된 각도값
float roll, pitch, yaw;                                         // 계산된 roll, pitch, yaw
float elapsedTime, currentTime, previousTime;

void setup() {
  Serial.begin(9600);                                           // 시리얼 통신 시작
  
  Wire.begin();                                                 // I2C 통신 시작
  Wire.beginTransmission(MPU_addr);                             // MPU6050 address로 통신 시작(0x68)
  Wire.write(0x6B);                                             // 통신 시작 레지스터(PWM_MGMT_1)
  Wire.write(0x00);                                             // 0입력, MPU6050 초기화
  Wire.endTransmission(true);                                   // 통신 종료
  
  delay(200);
}

void loop() {
  // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ[[가속도 센서]]ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
  // [가속도 센서값 읽기]
  Wire.beginTransmission(MPU_addr);                             // MPU6050 address로 통신 시작(0x68)
  Wire.write(0x3B);                                             // 가속도 센서 데이터 레지스터(ACCEL_XOUT_H)
  Wire.endTransmission(false);                                  // 통신 종료 하지 않기
  Wire.requestFrom(MPU_addr, 6, true);                          // 레지스터값 6개 읽기(각 축은 2개의 레지스터에서 읽기)

  // [가속도 센서값 전처리]
  // +-2g 범위 값 변환 : datasheet 참조. raw / 16384.0
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0;            // AccX value
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0;            // AccY value
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0;            // AccZ value

  // 가속도raw 값 -> degree 계산
  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ,2))) * 180 / PI);
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ,2))) * 180 / PI);

  previousTime = currentTime;                                   // 이전 loop에서의 시간
  currentTime = millis();                                       // 현재 시간을 mills 단위로 계산
  elapsedTime = (currentTime - previousTime) / 1000;            // 지난 시간을 mills 단위로 계산

  // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ[[자이로 센서]]ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
  // [자이로 센서값 읽기]
  Wire.beginTransmission(MPU_addr);                             // MPU6050 address로 통신 시작(0x60)
  Wire.write(0x43);                                             // 자이로 센서 데이터 레지스터
  Wire.endTransmission(false);                                  // 통신 종료 하지 않기
  Wire.requestFrom(MPU_addr, 6, true);                          // 레지스터값 6개 읽기(각 축은 2개의 레지스터에서 읽기)

  // [자이로 센서값 전처리]
  // +-250deg/s 범위 값 반환 : datasheet 참조. raw / 131.0
  GyroX = (Wire.read() << 8 | Wire.read()) / 131.0;             // AccX value
  GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;             // AccY value
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;             // AccZ value

  // 자이로raw 값 -> degree 계산
  gyroAngleX = gyroAngleX + GyroX * elapsedTime;
  gyroAngleY = gyroAngleY + GyroY * elapsedTime;
  yaw = yaw + GyroZ * elapsedTime;
//  Serial.print("accX: ");
//  Serial.print(AccX);
//  Serial.print(",accY: ");
//  Serial.print(AccY);
//  Serial.print(",accZ: ");
//  Serial.println(AccZ);
  
//  Serial.print("accAngleX: ");
//  Serial.print(accAngleX);
//  Serial.print(",accAngleY: ");
//  Serial.println(accAngleY);
//  Serial.print(",gyroAngleX: ");
//  Serial.println(gyroAngleX);

//  Serial.print(accAngleX);
//  Serial.print(", ");rfggt  de     
//  Serial.println(accAngleY);

  Serial.print(GyroX);
  Serial.print(GyroY);
  Serial.print(GyroZ);
}
