#include <Wire.h>

const int MPU_addr = 0x68;
float AccX, AccY, AccZ, GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY;
float roll, pitch;
float elapsedTime, currentTime, previousTime;
float alpha = 1/(1 + 0.04);
float angleFix, angleFiy;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x68);
  Wire.write(0x00);
  Wire.endTransmission(true);
  delay(200);
}

void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 6, true);
  
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0;
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0;
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0;

  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ,2))) * 180 / PI);
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ,2))) * 180 / PI);

  previousTime = currentTime;
  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000;
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 6, true);

  GyroX = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
//  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;

  
  double angleTmpX = angleFix + GyroX * elapsedTime;
  double angleTmpY = angleFiy + GyroY * elapsedTime;
  
  //  yaw = yaw+GyroZ * elapsedTime;

  //상보
  angleFix = alpha * angleTmpX + (1.000 - alpha) * accAngleX;
  angleFiy = alpha * angleTmpY + (1.000 - alpha) * accAngleY;
  
  Serial.print(angleTmpX);
  Serial.print(" ");
  Serial.print(accAngleX);
  Serial.print(" ");
  Serial.println(angleFix);
}
