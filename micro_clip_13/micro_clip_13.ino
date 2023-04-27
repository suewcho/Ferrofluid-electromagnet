int read_previous, read_current, use =0;
unsigned long time_previous, time_current, first_beat_time;
bool data_effect=true;
int counter = 0;
unsigned long sub;
unsigned int heart_rate;
#include "Keyboard.h"

const int max_heartpluse_duty = 2000; //2초동안 다음 맥박 없으면 입력 중지로 간주

void setup() {
  // put your setup code here, to run once:
  time_previous = millis();
  pinMode(14, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(21, INPUT);
  Serial.begin(9600);
  Keyboard.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  read_current = digitalRead(21);
 

  if (counter>7){
    digitalWrite(14,read_current);
    digitalWrite(16,read_current);
    digitalWrite(10,read_current);
    digitalWrite(9,read_current);
    digitalWrite(8,read_current);
  }else if(counter>6){
    digitalWrite(14,read_current);
    digitalWrite(16,read_current);
    digitalWrite(10,read_current);
    digitalWrite(9,read_current);
    digitalWrite(8,0);
  }else if(counter>5){
    digitalWrite(14,read_current);
    digitalWrite(16,read_current);
    digitalWrite(10,read_current);
    digitalWrite(9,0);
    digitalWrite(8,0);
  }else if(counter>3){
    digitalWrite(14,read_current);
    digitalWrite(16,read_current);
    digitalWrite(10,0);
    digitalWrite(9,0);
    digitalWrite(8,0);
  }else{
    digitalWrite(14,read_current);
    digitalWrite(16,0);
    digitalWrite(10,0);
    digitalWrite(9,0);
    digitalWrite(8,0);
  }
  
  if (counter>=2 && read_current ==1){
    Keyboard.press(' ');
  }
  if(read_previous==1 && read_current ==0)
  {
    Keyboard.release(' ');
  }

  time_current = millis();
  if(read_previous==0 && read_current ==1)
  {
    
    counter += 1;
    if (counter==2){
      first_beat_time = millis();
      //Keyboard.write('1');
      use=1;
    }
    if (counter==8){
      Keyboard.write('1');
      use=1;
    }
    
 
    read_previous=read_current;
    heart_rate=60000/(time_current-time_previous);
    Serial.println(heart_rate);
    time_previous=time_current;
    
  } else if(time_current - time_previous >= max_heartpluse_duty)
  {
    counter = 0;
    
    if (use==1){
      Keyboard.write('0');
      use=0;

    }
    digitalWrite(16,LOW);
    digitalWrite(10,LOW);
    digitalWrite(9,LOW);
    digitalWrite(8,LOW);

    read_previous=read_current;
  } else
  {
    read_previous=read_current;
  }  
  digitalWrite(13,LOW);

}

void sum()
{
  if(data_effect)
    {
      heart_rate=600000/(time_current-time_previous);//60*20*1000/20_total_time 
    }
    data_effect=1;//sign bit
}
