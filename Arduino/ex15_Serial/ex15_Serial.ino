// ● Serial Communication
  // 1. 시리얼 모니터 : 문자, 숫자 출력 but 데이터를 무조건 문자로 인식
    // 0) 통신 팁
      // - 통신 : ASCII 코드 -> 시리얼 모니터 : 문자열을 자료형에 맞게 출력
      // - ASCII 코드 표, PinMap 확인
      // - Serial 통신 핀이 여러 개인 보드 : 명령어 사용 시 Serial.~~ 대신 Serial1, Serial2, ... 사용
        // void serialEvent() 대신 void serialEvent1(), void serialEvent2... 사용
      // - Serial 통신 핀이 한 개인 보드 : 명령어 사용 시 Serial.~~ 그대로 사용
      // ex. float형 65 : '6' '5' '.' '0' '0'
    // 1) 시리얼 시작 : Serial.begin(BaudRate)
    // 1) 시리얼 시작 : Serial.begin(BaudRate, config)
      // - BaudRate : bps(초당 전송 비트 수)
      // - config : 시리얼 통신 환경
        // (1) 기본값 : SERIAL_8N1 (8비트 데이터 길이, 패리티 비트 사용x, 1개 정지 비트 사용o)
        // (2) 커스터마이징 값 : SERIAL_xxx
          // 1] 데이터 길이 : 비트 수
            // 8 : 8비트 데이터
            // 7 : 7비트 데이터
            // 6 : 6비트 데이터
            // 5 : 5비트 데이터
          // 2] 패리티 비트 : 데이터 오류 판별 비트
            // N : 패리티 비트 사용x
            // E : Even(짝수) 패리티 비트 사용o
            // O : Odd(홀수) 패리티 비트 사용o
          // 3] 정지 비트
            // 1 : 1개의 정지 비트 사용o
            // 2 : 2개의 정지 비트 사용o
    // 2) 시리얼 통신 가능? : value = Serial.available()
      // - 반환값 : 수신된 데이터 중 아직 읽지 않은 데이터 개수 / int형으로 반환
    
    // 3) 시리얼 출력 + Enter : Serial.println(Value)
    // 3) 시리얼 출력 : Serial.print(Value)
    // 3) 시리얼 출력 : Serial.write(Value)
      // - Value : byte형 데이터 or 문자열
      // - 문자가 아닌 Raw 데이터 값을 지정해서 보내야하는 경우 사용 ex. 블루투스, 지그비 모듈과의 통신
    // 3) 시리얼 출력 : Serial.write(Buffer, Length)
      // - Buffer : byte형 배열
      // - Length : 전송할 배열의 길이, 전송할 데이터의 개수
      // - 문자가 아닌 Raw 데이터 값을 지정해서 보내야하는 경우 사용 ex. 블루투스, 지그비 모듈과의 통신
    
    // 4) 시리얼 char입력 : Serial.read()
      // - 반환값 : 수신된 데이터를 순서대로 하나씩 저장 + 읽기 / char형으로 반환
    // 4) 시리얼 string입력 : Serial.readString()
    
    // 4) 시리얼 char입력 + 지정한 개수만큼 읽어서 버퍼에 저장 + 개수 반환 : Serial.readBytes(Buffer, Length)
      // - Buffer : char형 배열
      // - Length : 읽어올 데이터 개수
      // - 반환값 : byte형 데이터(읽어온 데이터 개수)
      // - 지정된 개수만큼 데이터가 수신되지 않을 경우, 수신된 개수만큼만 저장 + 그 개수 반환
    // 4) 시리얼 지정한 문자가 수신될 때까지 데이터 읽어옴 + 지정한 개수만큼 읽어서 버퍼에 저장 + 개수 반환 : Serial.readBytesUntil(Character, Buffer, Length)
      // - Character : 수신 종료를 의미할 문자. 이 값은 버퍼에 저장되지 않는다
      // - Buffer : 데이터 저장할 char형 배열
      // - Length : 읽어올 데이터 최대 개수
      // - 반환값 : 읽어온 데이터 개수
    // 4) 시리얼 지정된 길이만큼 데이터 수신되지 않았을 때, 수신을 기다리는 최대 시간 : Serial.setTimeout(Timeout_ms)
      // - Serial.readBytes(), Serial.readBytesUnitl() 함수에 사용되는 타임아웃 시간 설정
      // - Timeout : 설정할 타임아웃 시간. unsigned long 자료형. ms 단위
      // - 타임아웃 기본값 = 1000ms

    // 5) 시리얼 통신 시 자동 실행 함수 : void serialEvent() {원하는 명령어들}
      // - 시리얼 통신을 통한 데이터 수신시, 자동으로 serialEvent()함수 호출

    // 6) 자료형 변환
      // (1) char형 숫자 -> long형 숫자 변환 : Serial.parseInt()
        // - 반환값 : 변환된 long형 숫자값 반환. 숫자가 아닌 문자가 들어오면 0 반환
        // ex. '1' '0' '0' -> 100
      // (2) char형 숫자 -> float형 숫자 변환 : Serial.parseFloat()
        // - 반환값 : 변환된 float형 숫자값 반환. 숫자가 아닌 문자가 들어오면 0 반환
        
    // 7) 시리얼 종료 : Serial.end()
      // - 시리얼 통신 종료 + 사용하던 시리얼 핀을 일반 디지털 IO핀으로 전환
      // - 시리얼 통신 종료 후 사용하던 디지털 IO핀을 다시 시리얼 핀으로 전환하려면 Serial.begin() 함수 사용
  // 2. 시리얼 플로터 : 변수 값 그래프 출력

void setup() {
  Serial.begin(9600);
}

void loop() {
//  Serial.println("ㅡㅡㅡㅡㅡㅡ테스트1ㅡㅡㅡㅡㅡㅡ");
//  
//  int i = 65;
//  float f = 65;
//  char c = 65;
//
//  Serial.println(i);
//  Serial.println(f);
//  Serial.println(c);
//
//  if(Serial.available() > 0) {
//    Serial.println("ㅡㅡㅡㅡㅡㅡ테스트2ㅡㅡㅡㅡㅡㅡ");
//    
//    char c = Serial.read();
//    Serial.print("rx : ");
//    Serial.println(c);
//    break;
//  }
//
//
//
//  if(Serial.available() > 0) {
//    Serial.println("ㅡㅡㅡㅡㅡㅡ테스트3ㅡㅡㅡㅡㅡㅡ");
//    
//    long readValue1 = Serial.parseInt();
//    long readValue2 = Serial.parseInt();
//
//    Serial.print(readValue1);
//    Serial.print(" ");
//    Serial.println(readValue2);
//    break;
//  }
}

//void serialEvent(){
//  Serial.println("ㅡㅡㅡㅡㅡㅡ테스트4ㅡㅡㅡㅡㅡㅡ");
//  
//  char c = Serial.read();
//  Serial.print("rx : ");
//  Serial.println(c);
//}
