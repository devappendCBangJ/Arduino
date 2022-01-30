int BLUE= 5;  // Digital input
int RED= 6;  // Digital input
int GREEN= 7;  // Digital input


void setup ()
{
  pinMode (RED, OUTPUT);
  pinMode (GREEN, OUTPUT);
  pinMode (BLUE, OUTPUT);
}
void loop ()
{
  digitalWrite (RED, HIGH);
  digitalWrite (GREEN, LOW);
  digitalWrite (BLUE, LOW);
  delay(1000);
  digitalWrite (RED, LOW);
  digitalWrite (GREEN, HIGH);
  digitalWrite (BLUE, LOW);
  delay(1000);
  digitalWrite (RED, LOW);
  digitalWrite (GREEN, LOW);
  digitalWrite (BLUE, HIGH);
  delay(1000);
  digitalWrite (RED, HIGH);
  digitalWrite (GREEN, HIGH);
  digitalWrite (BLUE, HIGH);
  delay(1000);
} 
