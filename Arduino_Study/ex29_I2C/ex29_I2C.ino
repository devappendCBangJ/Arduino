// I2C 통신 공부 : https://m.blog.naver.com/yuyyulee/220325361752

// ● I2C Communication
  // 1. 
    // 0) I2C 헤더파일 불러오기 : #include <Wire.h>
    
    // 1) 마스터 모드 I2C 시작 : Wire.begin()
    // 1) 슬레이브 모드 I2C 시작 : Wire.begin(address)
      // - address : 슬레이브 모드 주소값. 주소값은 7비트 데이터이므로 0~127

    // 2) I2C byte 보내기
      // (1) 마스터에서 전송하기 위한 슬레이브 주소값 지정 : Wire.beginTransmission(address)
        // - 슬레이브 주소값을 버퍼에 저장하여 전송 준비
        // - address : 슬레이브 주소값. 주소값은 7비트 데이터이므로 0~127
      // (2) 마스터에서 전송하기 위한 byte형 데이터 저장 in 버퍼 : Wire.write(Value)
        // - Value : byte형 데이터 (int형과 long형도 가능하지만, byte형으로 변환되므로 데이터 손실 주의)
      // (2) 마스터에서 전송하기 위한 string형 데이터 저장 in 버퍼 : Wire.write(String)
        // - String : String형 데이터. String길이만큼 버퍼에 저장
      // (2) 마스터에서 전송하기 위한 byte형 배열 데이터 저장 in 버퍼 : Wire.write(dataArray, Length)
        // - dataArray : byte형 배열 데이터. Length값 길이만큼 버퍼에 저장
        // - Length : dataArray 배열의 길이 or 전송할 바이트 수 지정
      // (3) 마스터에서 슬레이브에 데이터 버퍼에 저장된 데이터 전송 (마스터 모드에서만 사용): Wire.endTransmission()
      // (3) 마스터에서 슬레이브에 데이터 버퍼에 저장된 데이터 전송 + 정지 신호 생성 : Wire.endTransmission(stop)
        // - stop : TRUE - 정지 신호 생성 / FALSE - 정지 신호 생성x. 연속으로 데이터 전송
        // - 전송값 : 시작 신호 + 슬레이브 주소 + 데이터 + (정지 신호)
        // - 반환값 : 전송 성공 여부 반환 / byte형 반환
          // 0 : 전송 성공
          // 1 : 데이터 버퍼의 길이가 허용 범위 초과
          // 2 : 주소 전송 단계에서 NACK 응답 발생 = 해당 주소 값을 가진 슬레이브 기기 없음
          // 3 : 데이터 전송 단계에서 NACK 응답 발생 = 데이터 전송 실패
          // 4 : 그 외 오류 발생

    // 3) I2C byte 읽기
      // (1) 마스터에서 슬레이브로 데이터 요청 : Wire.requestFrom(address, quantity)
      // (1) 마스터에서 슬레이브로 데이터 요청 + 정지 신호 생성 : Wire.requestFrom(address, quantity, stop)
        // - address : 데이터를 요청할 슬레이브 주소값
        // - quantity : 요청할 데이터의 바이트 수
        // - stop : TRUE - 정지 신호 생성 / FALSE - 정지 신호 생성x. 연속으로 데이터 전송
        // - 반환값 : 요청 후 수신된 바이트 수 / byte형 반환
      // (2) I2C 통신 수신된 데이터 확인 : Wire.available()
        // - 반환값 : 수신된 데이터 중 아직 읽지 않은 데이터 바이트 수 / int형으로 반환
      // (3) I2C byte읽기 : Wire.read()
        // - 반환값 : 수신된 버퍼 데이터를 순서대로 하나씩 저장 + 읽기 / byte형으로 반환

    // 4) 마스터로부터 데이터 수신 시 자동 실행 함수 when 슬레이브 모드 : Wire.onReceive(handler);
      // - handler : 마스터로부터 데이터 수신 시, 호출될 int형 매개변수를 가지는 이벤트 처리 함수
      // - int형 매개변수를 가지는 handler 함수를 사전에 정의해야함
    // 4) 마스터로부터 데이터 요청 받을 시(데이터 제공 시) 자동 실행 함수 when 슬레이브 모드 : Wire.onRequest(handler);
      // - handler : 마스터로부터 데이터 요청 받을 시(데이터 제공 시), 호출될 매개변수 없는 이벤트 처리 함수
      // - 매개변수를 가지지 않는

//// 1_Wire.onReceive(handler) 예제
//
//#include <Wire.h>
//
//byte address = 100;
//byte recvDataBuf[128];
//
//void setup() {
//  Wire.begin(address);
//  Wire.onReceive(receiveHandler);
//}
//
//void loop() {
//}
//
//void receiveHandler(int nByteNum){
//  for (int i = 0; i < nByteNum; i++){
//    recvDataBuf[i] = Wire.read();
//  }
//}


// 2_Wire.onRequest(handler) 예제

#include <Wire.h>

byte address = 100;

void setup(){
  Wire.begin(address);
  Wire.onRequest(requestHandler);
}

void loop(){
}

void requestHandler(){
  byte data = 10;
  Wire.write(data);
}
