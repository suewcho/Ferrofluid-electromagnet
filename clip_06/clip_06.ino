int read_previous, read_current =0;
unsigned long time_previous, time_current, first_beat_time;
bool data_effect=true;
int counter = 0;
unsigned long sub;
unsigned int heart_rate;

const int max_heartpluse_duty = 2000; //2초동안 다음 맥박 없으면 입력 중지로 간주

void setup() {
  // put your setup code here, to run once:
  time_previous = millis();
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  read_current = digitalRead(2);
  if (time_current-first_beat_time>10000){
    digitalWrite(13,read_current);
  }
  digitalWrite(12,read_current);
  //Serial.println(read_current);
  //Serial.println(counter);
  time_current = millis();
  if(read_previous==0 && read_current ==1)
  {
    
    //Serial.println(read_current);
    counter += 1;
    if (counter==1){
      first_beat_time = millis();
    }
    read_previous=read_current;
    heart_rate=60000/(time_current-time_previous);
    Serial.println(heart_rate);
    time_previous=time_current;
    
  } else if(time_current - time_previous >= max_heartpluse_duty)
  {
    counter = 0;
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
