const char cCR=13, cLF=10; // cariage return, line feed 아스키 코드
int btnPin[4]={2,3,4,5}, ledPin[4]={8,9,10,11};
int btnStatePrev[4] = {1,1,1,1}, ledState[4] = {0,0,0,0};
String gBuff;

void setup() {
  for(int i=0; i<4; i++)
  {
    pinMode(ledPin[i], OUTPUT);
    pinMode(btnPin[i], INPUT_PULLUP); // pull-up
  }
  Serial.begin(9600);
  Serial.setTimeout(0);
}

void loop() {

  //------------------------------------
  //  버튼 상태가 ON->OFF로 변했으면 송신
  //------------------------------------

  // Off -> On 인지 검사
  int btnState[4], btnOn2Off[4];
  for(int i=0; i<4; i++) btnState[i] = digitalRead(btnPin[i]);
  for(int i=0; i<4; i++) btnOn2Off[i] = btnStatePrev[i] && !btnState[i]; // 버튼 누를 때만 반전시키기 위함

  // Off -> On 으로 상태가 바뀌었으면 글자 송신
  if(btnOn2Off[0]) Serial.print("1" + String(cCR) + String(cLF)); // 캐리지리턴, 라인피드는 printable char가 아니기 때문에 ""가 아닌 string으로 바꿔서 사용
  if(btnOn2Off[1]) Serial.print("2" + String(cCR) + String(cLF)); // 총 3바이트
  if(btnOn2Off[2]) Serial.print("3" + String(cCR) + String(cLF));
  if(btnOn2Off[3]) Serial.print("4" + String(cCR) + String(cLF));

  // 이전 상태 기억
  for(int i=0; i<4; i++) btnStatePrev[i] = btnState[i];

  //------------------------------------
  //  1, 2, 3, 4 수신에 따라 led 반전
  //------------------------------------
  
  // 데이터 없으면 리턴
  if(Serial.available() <= 0) return;

  // 데이터 있으면 리턴x
  // 수신내용 버퍼에 추가
  gBuff += Serial.readString();
  
  // 최초 한글자 얻기
  String st = gBuff.substring(0, 1);

  // gBuff 업데이트
  gBuff = gBuff.substring(1);

  // LED 반전
  if(st =="1") ledState[0] = !ledState[0];
  if(st =="2") ledState[1] = !ledState[1];
  if(st =="3") ledState[2] = !ledState[2];
  if(st =="4") ledState[3] = !ledState[3];
  digitalWrite(ledPin[0], ledState[0] & 0x1 ? HIGH : LOW);
  digitalWrite(ledPin[1], ledState[1] & 0x1 ? HIGH : LOW);
  digitalWrite(ledPin[2], ledState[2] & 0x1 ? HIGH : LOW);
  digitalWrite(ledPin[3], ledState[3] & 0x1 ? HIGH : LOW);
}
