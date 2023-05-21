int read_previous, read_current, use =0;
unsigned long time_previous, time_current, first_beat_time;
bool data_effect=true;
bool changed = false;
int counter = 0;
int previous_score, current_score, lowest;
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
  previous_score = 0;
  current_score = 0;
  lowest = 1;

}

void loop() {
  // put your main code here, to run repeatedly:
  read_current = digitalRead(21);
 

  if (counter>25 && counter<32){
    digitalWrite(14,0);
    digitalWrite(16,0);
    digitalWrite(10,0);
    digitalWrite(9,0);
    digitalWrite(8,read_current);
  }else if(counter>20 && counter<26){
    digitalWrite(14,0);
    digitalWrite(16,0);
    digitalWrite(10,0);
    digitalWrite(9,read_current);
    digitalWrite(8,0);
  }else if(counter>15 && counter<21){
    digitalWrite(14,0);
    digitalWrite(16,0);
    digitalWrite(10,read_current);
    digitalWrite(9,0);
    digitalWrite(8,0);
  }else if(counter>10 && counter<16){
    digitalWrite(14,0);
    digitalWrite(16,read_current);
    digitalWrite(10,0);
    digitalWrite(9,0);
    digitalWrite(8,0);
  }else if(counter>5 && counter<11){
    digitalWrite(14,read_current);
    digitalWrite(16,0);
    digitalWrite(10,0);
    digitalWrite(9,0);
    digitalWrite(8,0);
  }else{
    digitalWrite(14,read_current);
    digitalWrite(16,read_current);
    digitalWrite(10,read_current);
    digitalWrite(9,read_current);
    digitalWrite(8,read_current);
  }

  if (counter>=2 && read_current ==1 && read_previous==0 && heart_rate>40){
    Keyboard.write(' ');
  }
  if(counter>=2 && read_previous==1 && read_current ==0 && heart_rate>40)
  {
    Keyboard.write(' ');
  }
  //Serial.println(read_current);
  //Serial.println(counter);
  time_current = millis();
  if(read_previous==0 && read_current ==1)
  {
    
    //Serial.println(read_current);
    counter += 1;
    if (counter==2){
      first_beat_time = millis();
      use=1;
    }

    read_previous=read_current;
    heart_rate=60000/(time_current-time_previous);

    if (counter>5 && counter<32){
      current_score += heart_rate;
    }
    if(counter==11){
      previous_score = current_score;
      current_score = 0;
    }else if(counter==16){
      if (previous_score>current_score){
        previous_score = current_score;
        lowest = 2;
      }else if(previous_score==current_score && previous_score%2==1){
        previous_score = current_score;
        lowest = 2;
      }
      current_score = 0;
    }else if(counter==21){
      if (previous_score>current_score){
        previous_score = current_score;
        lowest = 3;
      }else if(previous_score==current_score && previous_score%2==1){
        previous_score = current_score;
        lowest = 3;
      }
      current_score = 0;
    }else if(counter==26){
      if (previous_score>current_score){
        previous_score = current_score;
        lowest = 4;
      }else if(previous_score==current_score && previous_score%2==1){
        previous_score = current_score;
        lowest = 4;
      }
      current_score = 0;
    }else if(counter==31){
      if (previous_score>current_score){
        previous_score = current_score;
        lowest = 5;
      }else if(previous_score==current_score && previous_score%2==1){
        previous_score = current_score;
        lowest = 5;
      }
      current_score = 0;
      if(lowest==1){
        Keyboard.write('1');
      }else if(lowest==2){
        Keyboard.write('2');
      }else if(lowest==3){
        Keyboard.write('3');
      }else if(lowest==4){
        Keyboard.write('4');
      }else if(lowest==5){
        Keyboard.write('5');
      }
      Keyboard.write('0');
      changed = true;
    }

    Serial.println(heart_rate);
    time_previous=time_current;
    
    
  } else if(time_current - time_previous >= max_heartpluse_duty && changed && use==1)
  {
    
    if(lowest==1){
      Keyboard.write('1');
    }else if(lowest==2){
      Keyboard.write('2');
    }else if(lowest==3){
      Keyboard.write('3');
    }else if(lowest==4){
      Keyboard.write('4');
    }else if(lowest==5){
      Keyboard.write('5');
    }

    if(changed){
      Keyboard.write('0');
      changed= false;

    }

    
    use=0;
    
    digitalWrite(16,LOW);
    digitalWrite(10,LOW);
    digitalWrite(9,LOW);
    digitalWrite(8,LOW);

    counter = 0;
    lowest = 1;
    previous_score = 0;
    current_score = 0;
    

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
      //Serial.print("Heart_rate_is:\t");
      //Serial.println(heart_rate);
    }
    data_effect=1;//sign bit
}
