
int KEY1 = 36;
int KEY2 = 39;
int KEY3 = 34;
int KEY4 = 35;
int BEEP = 32;
int LED  = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(KEY1,INPUT);
  pinMode(KEY2,INPUT);
  pinMode(KEY3,INPUT);
  pinMode(KEY4,INPUT);
  pinMode(BEEP,OUTPUT);
  pinMode(LED ,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(KEY1) == 0 || digitalRead(KEY2) == 0 || digitalRead(KEY3) == 0 || digitalRead(KEY4) == 0)
  {
    digitalWrite(BEEP,HIGH);
    digitalWrite(LED ,HIGH);
    delay(10);
    digitalWrite(BEEP,LOW);
    digitalWrite(LED ,LOW);
    delay(10);
  }else{
    digitalWrite(BEEP,LOW);
    digitalWrite(LED ,HIGH);
  }

}
