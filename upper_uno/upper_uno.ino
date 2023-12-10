//조도센서, 압력센서, LED, 진동모듈 3개
int pin_LED = 2;
int value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pin_LED, OUTPUT);         //LED는 2번핀
       //압력센서는 A1핀으로
}

void loop() {
  int light = analogRead(A0);      //조도센서는 A0핀으로

  //압력센서
  int FSRsensor = analogRead(A1);     //압력센서는 A1핀으로
  
  value = map(FSRsensor, 0, 1023, 0, 255);
  if (value >= 1) {
    Serial.print("Sensor On\n");
    
    if (light <= 200) {
      digitalWrite(pin_LED, HIGH);
      Serial.print("Turn on the light for pedestrian\n");
    }
    else {
      digitalWrite(pin_LED, LOW);
      Serial.print("Turn off the light\n");
    }
    delay(1000);
  }
  else {
    Serial.print("Sensor Off\n");
    digitalWrite(pin_LED, LOW);
    delay(1000);
   }
}