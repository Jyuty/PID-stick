#include <GyverPID.h>
#include <Servo.h>
#define point 80
#define sonarTrigPIN 2
#define sonarEchoPIN 3
#define servoPIN 4
Servo serv;
GyverPID regul(0.3,0.2,0.15);
float dist,fdist;
int i = 0,angle;
float dist3[3] = {0,0,0};
void setup() {
  Serial.begin(9600);
  pinMode(sonarTrigPIN,OUTPUT);
  pinMode(sonarEchoPIN,INPUT);
  regul.setDirection(NORMAL);
  regul.setLimits(-58,58);
  regul.setpoint = point;
  serv.attach(servoPIN);
}

void loop() {
  
  fdist = sonarDist(sonarTrigPIN,sonarEchoPIN);
  regul.input = fdist;
  angle = regul.getResultTimer();
  serv.write(60 + angle);
  Serial.print(point);
  Serial.print(',');
  Serial.print(angle);
  Serial.print(',');
  Serial.println(fdist);
  
}


float sonarDist(int Trig,int Echo){
  float dist;
  unsigned long duration;
  if(i > 1) i = 0;
  else i++;
  digitalWrite(Trig, LOW); 
  delayMicroseconds(2); 
  digitalWrite(Trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(Trig, LOW); 
  duration = pulseIn(Echo,HIGH);
  dist = (float)duration / 5.75; 
  if (dist > 260) dist = 260; //ограничиваем макс расстояние до длинны жёлоба
  dist3[i] = dist;
  return middle_of_3(dist3[0],dist3[1],dist3[2]);
}


float middle_of_3(float a, float b, float c) {
  float middle = 0; 
  if ((a <= b) && (a <= c)) {
    middle = (b <= c) ? b : c;
  }
  else {
    if ((b <= a) && (b <= c)) {
      middle = (a <= c) ? a : c;
    }
    else {
      middle = (a <= b) ? a : b;
    }
  }
  return middle;
}
