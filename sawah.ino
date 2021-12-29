#define triggerPin 2
#define echoPin 3
#define SensorPin 0
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


LiquidCrystal_I2C lcd(0x27,16,2);
Servo servo;

void setup() {
  Serial.begin (9600);

  lcd.init();
  lcd.setBacklight(100);
  lcd.clear();
  lcd.setCursor(0,0);
  
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(4, OUTPUT);
  
  servo.attach(8);
  servo.write(0);
  delay (10);
  
}
void loop() {
  
  long duration, jarak;
  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2); 
  
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
 
  digitalWrite(triggerPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  jarak = 0.034*(duration)/2;
  
  lcd.setCursor(0,1);
  lcd.print(jarak);
  lcd.println(" cm");
  
  Serial.print("jarak :");
  Serial.print(jarak);
  Serial.println(" cm");

  //SENSOR KELEMBABAN
  
  digitalWrite(4, HIGH);
  delay(10);
  
  float Kelembaban = analogRead(SensorPin);
  Serial.print("Kelembaban :");
  Serial.print(Kelembaban);
  Serial.println(" %");
  delay(10);
  digitalWrite(4, LOW);
  delay(10);
  
  delay(1000);

  if (jarak >= 2 && jarak <=4 || Kelembaban >= 0 && Kelembaban <= 500) {
    Serial.println("Gerbang Terbuka ");
    lcd.setCursor(0,0);
    lcd.println("Gerbang Terbuka ");
    servo.write(110);
    delay(1000);
  }

  else if (jarak > 4 && jarak <= 5 || Kelembaban >= 500 && Kelembaban <= 800  ){
    Serial.println("Gerbang Terbuka Penuh");
    lcd.setCursor(0,0);
    lcd.println("Gerbang Terbuka Penuh");
    servo.write(30);
    delay(1000);
  }
  else if ( isnan(jarak) || isnan(Kelembaban)){
    Serial.println(" Sensor Tidak Membaca " );
    lcd.setCursor(0,0);
    lcd.print("Sensor Eror");
    delay(1000);
  }
  
  else {
    Serial.println("Gerbang Tertutup");
    lcd.setCursor(0,0);  
    lcd.println("Gerbang Tertutup");
    servo.write(130);
    delay(1000);
  }

}
