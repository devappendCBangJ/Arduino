int led[4]={8,9,10,11};
int brightness = 0, increment = 1;

void setup()
{
  for(int i=0; i<4; i++)
    pinMode(led[i], OUTPUT); // 디폴트는 입력
}

void loop()
{
  if(brightness > 255)
    increment = -1; // 255에 도달하면 감소 방향
  else if(brightness < 1)
    increment = 1; // 0으로 떨어지면 증가방향

  brightness += increment; // 밝기 변화
  for(int i=0; i<4; i++)
    analogWrite(led[i], brightness); // 밝기 출력
  delay(5);
}
