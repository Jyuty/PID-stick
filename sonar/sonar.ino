#define sonarTrigPIN 2
#define sonarEchoPIN 3

unsigned long duration;
float dist;
void setup() {
  Serial.begin(9600);
  pinMode(sonarTrigPIN,OUTPUT);
  pinMode(sonarEchoPIN,INPUT);

}

void loop() {
  digitalWrite(sonarTrigPIN, LOW); 
  delayMicroseconds(2); 
  digitalWrite(sonarTrigPIN, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(sonarTrigPIN, LOW); 
  duration = pulseIn(sonarEchoPIN,HIGH);
  dist = (float)duration / 5.75;
  //выводит в мм
  Serial.println(dist);
  delay(100);
  
}
