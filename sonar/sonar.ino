#define sonarTrigPIN 2
#define sonarEchoPIN 3

//unsigned long duration;
float dist,fdist;
int i = 0;
float dist3[3] = {0,0,0};
void setup() {
  Serial.begin(9600);
  pinMode(sonarTrigPIN,OUTPUT);
  pinMode(sonarEchoPIN,INPUT);

}

void loop() {
  if(i > 1) i = 0;
  else i++;
  
  dist = sonarDist(sonarTrigPIN,sonarEchoPIN);
  if (dist > 260) dist = 260; //ограничиваем макс расстояние до длинны жёлоба
  dist3[i] = dist;
  Serial.print(dist);
  Serial.print(',');
  fdist = middle_of_3(dist3[0],dist3[1],dist3[2]);
  Serial.println(fdist);
  delay(100);
  
}


float sonarDist(int Trig,int Echo){
  unsigned long duration;
  digitalWrite(Trig, LOW); 
  delayMicroseconds(2); 
  digitalWrite(Trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(Trig, LOW); 
  duration = pulseIn(Echo,HIGH);
  return (float)duration / 5.75; 
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
