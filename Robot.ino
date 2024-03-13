#include <Servo.h>    
#include <VL53L0X.h>  
Servo servoPoziom;
Servo servoPion;
#define ECHOPIN 3
#define TRIGPIN 2


const int IN1 = 4;
const int IN2 = 5;
const int IN3 = 6;
const int IN4 = 7;
long duration, distance;
int Lewo;
int Prawo;
int L = 0;
int P = 0;

int ultrasonic() {
  digitalWrite(TRIGPIN, LOW);  
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  float distance = pulseIn(ECHOPIN, HIGH);  /
  distance = distance / 58;
  Serial.print(distance);
  Serial.println(" cm ");
}

  

int patrzLewo() {
  servoPoziom.write(100);
  delay(800);
  Lewo = ultrasonic();
  return Lewo;
}

int patrzPrawo() {
  servoPoziom.write(180);
  delay(800);
  Prawo = ultrasonic();
  return Prawo;
}






void setup() {
  Serial.begin(9600);
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  servoPoziom.attach(11);
  servoPion.attach(9);
  servoPoziom.write(90);  
  servoPion.write(90);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  digitalWrite(TRIGPIN, LOW);  
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);

  float distance = pulseIn(ECHOPIN, HIGH);  
  distance = distance / 58;
  Serial.print(distance);
  Serial.println(" cm ");

  delay(200);

  if (distance < 10) {  // intrukcja warunkowa,
    //czujnik ma zmieniać pozycje gdy odległość
    //jest mniejsza niż 10 cm
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(2000);

    P = patrzPrawo();
    servoPoziom.write(150);
    delay(200);
    L = patrzLewo();
    delay(500);

    servoPion.write(180);
    delay(200);
    servoPion.write(90);
    delay(200);
    servoPion.write(-180);
    delay(200);
    servoPion.write(90);
    delay(200);
    if (P > L) {
      digitalWrite(IN2, HIGH);
      digitalWrite(IN4, LOW);
      digitalWrite(IN1, LOW);
      digitalWrite(IN3, LOW);
      delay(700);
    } else if (L > P) {
      digitalWrite(IN2, HIGH);
      digitalWrite(IN4, HIGH);
      digitalWrite(IN1, LOW);
      digitalWrite(IN3, LOW);
      delay(700);
    }

    digitalWrite(IN2, HIGH);
    digitalWrite(IN4, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN3, LOW);
    delay(700);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN4, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN3, LOW);
  }
  if (distance >= 10) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN4, LOW);
  }
}