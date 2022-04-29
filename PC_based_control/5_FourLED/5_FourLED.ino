int btn[4]={2,3,4,5}, led[4]={8,9,10,11};

void setup()
{
  for(int i=0; i<4; i++)
  {
    pinMode(led[i], OUTPUT); // 디폴트는 입력
    pinMode(btn[i], INPUT_PULLUP); // pull-up
  }
}

void loop()
{
  for(int i=0; i<4; i++)
  {
    int push = digitalRead(btn[i]);
    digitalWrite(led[i], !push);
  }
}
