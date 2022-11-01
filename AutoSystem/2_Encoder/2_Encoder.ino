#define encoderPinA 2
#define encoderPinB 3
long encoderPos = 0;

void DoEncoderA(){
  encoderPos +=(digitalRead(encoderPinA) == digitalRead(encoderPinB))? 1:-1;
}
void DoEncoderB(){
  encoderPos +=(digitalRead(encoderPinA) == digitalRead(encoderPinB))? -1:1;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinA, INPUT);
  
  attachInterrupt(0, DoEncoderA, CHANGE); // 6틱
  attachInterrupt(0, DoEncoderB, CHANGE); // 1로 변경하면 12틱

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("encoderPos : ");
  Serial.println(encoderPos);
}
