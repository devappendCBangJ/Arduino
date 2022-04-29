// Serial 통신 공부 : https://blog.naver.com/yuyyulee/220301424499

//// 1_Serial Multi
//
//void setup() {
//  Serial.begin(9600);
//  Serial1.begin(9600);
//}
//
//void loop() {
//  if(Serial1.available()){
//    int inByte = Serial1.read();
//    Serial.write(inByte);
//  }
//
//  if(Serial.available()){
//    int inByte = Serial.read();
//    Serial1.write(inByte);
//  }
//}

// 2_SerialEvent Multi

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop(){
}

void serialEvent(){
  int inByte = Serial.read();
  Serial1.write(inByte);
}

void serialEvent1(){
  int inByte = Serial1.read();
  Serial.write(inByte);
}
