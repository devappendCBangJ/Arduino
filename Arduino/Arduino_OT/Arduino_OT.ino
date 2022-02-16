void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // 시리얼 모니터 : 문자, 숫자 출력
    // 시리얼 시작 : Serial.begin(BaudRate)
    // 시리얼 시작 : Serial.begin(BaudRate, config)
      // - BaudRate : bps(초당 전송 비트 수)
      // - config : 시리얼 통신 환경
        // 기본값 : SERIAL_8N1 (8비트 데이터 길이, 패리티 비트 사용x, 1개 정지 비트 사용o)
        // 커스터마이징 값 : SERIAL_xxx
          // 데이터 길이 : 비트 수
            // 8 : 8비트 데이터
            // 7 : 7비트 데이터
            // 6 : 6비트 데이터
            // 5 : 5비트 데이터
          // 패리티 비트 : 데이터 오류 판별 비트
            // N : 패리티 비트 사용x
            // E : Even(짝수) 패리티 비트 사용o
            // O : Odd(홀수) 패리티 비트 사용o
          // 정지 비트
            // 1 : 1개의 정지 비트 사용o
            // 2 : 2개의 정지 비트 사용o
    // 시리얼 통신 가능? : Serial.available()
    
    // 시리얼 출력 후 Enter : Serial.println(변수)
    // 시리얼 출력 : Serial.print(변수)
    
    // 시리얼 char입력 : Serial.read()
    // 시리얼 string입력 : Serial.readString()
  // 시리얼 플로터 : 변수 값 그래프 출력
  
  // 핀 설정 : pinMode(pin_number, pin_mode)
    // - pin_number : ex. A0
    // - pin_mode : INPUT(입력) or OUTPUT(출력)



  // 디지털
    // 디지털 출력 : digitalWrite(pin_number, bool)
      // - 출력 bool : HIGH(1) or LOW(0)
    // 디지털 입력 : digitalRead(pin_number)
      // - 입력 : HIGH(1) or LOW(0)
      
  // 아날로그
    // 아날로그 출력 : analogWrite(pin_number, 출력)
      // - 출력 : 8bit = 0~255
      // - 특징 : PWM 펄스폭 변조
        // [1] 서보모터 각도 등 정보전달
        // [2] 전압 근사화
      // - DAC : Digital to Analog Converter. Digital신호를 Analog신호로 바꿔주는 기기
        // 아두이노는 DAC가 없으므로 Analog신호 출력 불가
        // 뉴클레오는 DAC가 있으므로 Analog신호 출력 가능
    // 아날로그 입력 : analogRead(pin_number)
      // - 입력 : 분해능 10bit = 0~1023
      // - ADC : Analog to Digital Converter. Analog신호를 Digital신호로 바꿔주는 기기 

  // ms 딜레이 : delayMicroseconds(time);

  // 통신
    // 직렬 통신 : 1비트씩 전송
      // 단위 : bps (통신 속도 1초당 전송되는 비트 수)
      
      // 시작비트 : 시작 표시 비트
      // 패리티 비트 : 데이터 오류 판별 비트
      // 정지비트 : 종료 표시 비트

      // 무선 : 블루투스, RF통신, NFC
      // 유선 : UART, I2C, SPI
      
      // 단방향 : RF통신
      // 양방향 : 블루투스, NFC, UART, I2C, SPI

    // 병렬 통신
    
  // 회로
    // PULL_DOWN 회로 : PULL_UP 회로와 반대
    // PULL_UP 회로 : PULL_UP 회로와 반대

  // 모터
    // DC모터 : 직류 전압 인가
      // - 속도조절 : PWM or 파워서플라이
      // DC모터 : brush 있는 모터
      // BLDC모터 : brush 없는 모터
      // SERVO모터 : 위치제어 용이 모터
      // STEP모터 : 위치제어 용이 모터
    // AC모터 : 교류 전압 인가

  // 모터 드라이버
    // - 방향 조절 : H-bridge
    // - 트랜지스터 : 스위치 역할
    // - 전압, 전류 : Peak 전류가 아닌, 연속 전류에 맞춰 구매
    // - 성능 : 채널... 제어 가능 모터수
    // - 역기전력 방지 회로

  // 보드
    // - 전압, 전류 : Peak 전류가 아닌, 연속 전류에 맞춰 구매
    // - 성능
    // - 통신 핀 개수
    // - 입출력 핀 개수

  // 센서
    // - 전압, 전류 : Peak 전류가 아닌, 연속 전류에 맞춰 구매

  // 배터리
    // - 전압, 전류 : 부품 전체 전류, 전압 계산

  // 기타
    // chattering 현상 : 버튼이 눌릴 때 진동에 의해 짧은 시간에 on/off 되는 현상
    // floating 현상 : 0과 1사이의 애매한 상태

}
