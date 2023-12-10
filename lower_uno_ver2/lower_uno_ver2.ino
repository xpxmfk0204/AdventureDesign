#define TRIG A3
#define ECHO 7
const byte s0_pin = 2;
const byte s1_pin = 4;
const byte s2_pin = 5;
const byte s3_pin = 6;      // 색감지 센서 핀
const byte out_pin = 3;
int melody[] = {523, 2093, 1397};
int speaker = 12;   //피에조 부저는 12번 핀에
int vibe1 = A0;
int vibe2 = A1;
int vibe3 = A2;

void setup(){
  Serial.begin(9600);
  pinMode(A3, OUTPUT);          // 1번 초음파센서 출력
  pinMode(7, INPUT);            // 1번 초음파센서 입력
  pinMode(A4, OUTPUT);          // 2번 초음파센서 출력
  pinMode(8, INPUT);           // 2번 초음파센서 입력
  pinMode(A5, OUTPUT);          // 3번 초음파센서 출력
  pinMode(10, INPUT);            // 3번 초음파센서 입력
  pinMode(9, OUTPUT);           // 4번 초음파센서 출력
  pinMode(11, INPUT);           // 4번 초음파센서 입력

  pinMode(vibe1, OUTPUT);
  pinMode(vibe2, OUTPUT);
  pinMode(vibe3, OUTPUT);
  
  pinMode(s0_pin, OUTPUT);
  pinMode(s1_pin, OUTPUT);
  pinMode(s2_pin, OUTPUT);
  pinMode(s3_pin, OUTPUT);
  
  pinMode(out_pin, INPUT);
  
  digitalWrite(s0_pin,HIGH);
  digitalWrite(s1_pin,LOW);
}

void loop(){
  long duration_1, distance_1, duration_2, distance_2, duration_3, distance_3, duration_4, distance_4;

  //Serial 통신
  if(Serial.available()>0) {
    String Data = Serial.readStringUntil('\n');
    if(Data == "Sensor On") {
      digitalWrite(A3, LOW);
      delayMicroseconds(2);
      digitalWrite(A3, HIGH);
      delayMicroseconds(10);
      digitalWrite(A3, LOW);

      duration_1 = pulseIn(7, HIGH); //물체에 반사되어 돌아온 초음파의 시간을 변수에 저장
      distance_1 = duration_1 * 17 / 1000;             // 초음파센서1의 거리측정

      if(distance_1 < 100) {
        analogWrite(vibe1, 130);
        Serial.print("Object detected from left side\n");
        delay(100);
      }
      else {
        analogWrite(vibe1, 0);
    
      }                                           // 초음파센서1의 거리에 따른 장애물 알림
      delay(500);
  
      digitalWrite(A4, LOW);
      delayMicroseconds(2);
      digitalWrite(A4, HIGH);
      delayMicroseconds(10);
      digitalWrite(A4, LOW);
  
      duration_2 = pulseIn(8, HIGH);
      distance_2 = duration_2 * 17 / 1000;          // 초음파센서2의 거리측정
  
      if(distance_2 < 100) {
        analogWrite(vibe2, 130);
        Serial.print("Object detected from center\n");
        delay(100);
      }
      else {
        analogWrite(vibe2, 0);                         // 초음파센서2의 거리에 따른 장애물 알림
      }
      delay(500);

      digitalWrite(A5, LOW);
      delayMicroseconds(2);
      digitalWrite(A5, HIGH);
      delayMicroseconds(10);
      digitalWrite(A5, LOW);

      duration_3 = pulseIn(10, HIGH); //물체에 반사되어 돌아온 초음파의 시간을 변수에 저장
      distance_3 = duration_3 * 17 / 1000;             // 초음파센서3의 거리측정

      if(distance_3 < 100) {
        analogWrite(vibe3, 130);
        Serial.print("Object detected from right side\n");
        delay(100);
      }
      else {
        analogWrite(vibe3, 0);
    
      }
      delay(500);

      digitalWrite(9, LOW);
      delayMicroseconds(2);
      digitalWrite(9, HIGH);
      delayMicroseconds(10);
      digitalWrite(9, LOW);

      duration_4 = pulseIn(11, HIGH); //물체에 반사되어 돌아온 초음파의 시간을 변수에 저장
      distance_4 = duration_4 * 17 / 1000;             // 초음파센서4의 거리측정

      if(distance_4 < 100) {
        Serial.print("Floating object detected\n");
        for (int i = 0; i < 5; i++) {
          tone(speaker, melody[2], 20);
          delay(20);
          noTone(speaker);
          delay(10);
        }
      }
      else {
        noTone(speaker);
    
      }

      digitalWrite(s2_pin,LOW);
      digitalWrite(s3_pin,LOW);
      int red_color = pulseIn(out_pin, LOW);
      red_color = map(red_color, 25,72,255,0);
      red_color = constrain(red_color, 0, 255);
      delay(50);                                      // 색감지센서 빨간색 감지

      digitalWrite(s2_pin,HIGH);
      digitalWrite(s3_pin,HIGH);
      int green_color = pulseIn(out_pin, LOW);
      green_color = map(green_color, 30,90,255,0);
      green_color = constrain(green_color, 0, 255);
      delay(50);                                      // 색감지센서 초록색 감지

      digitalWrite(s2_pin,LOW);
      digitalWrite(s3_pin,HIGH);
      int blue_color = pulseIn(out_pin, LOW);
      blue_color = map(blue_color, 25,70,255,0);
      blue_color = constrain(blue_color, 0, 255);
      delay(50);                                      // 색감지센서 파란색 감지, 파란색 감지를 통해 초록, 빨강을 제외한 색을 default 처리 예정

      if(red_color > green_color && red_color > blue_color) {
        Serial.print("This is RED");
        tone(speaker, melody[1], 500);
        delay(20);
        noTone(speaker);                              // 빨간색 감지 시 높은 소리를 반복해 경고
      }
      else if(green_color > red_color && green_color > blue_color) {
        Serial.print("This is green");
        tone(speaker, melody[0], 500);
        delay(20);
        noTone(speaker);                              // 초록색 감지 시 낮은 소리로 안내
      }
      else {
        Serial.print("None\n");
        noTone(speaker);                              // 빨강, 초록을 제외한 색은 부저 작동 중지
      }

      delay(100);
    }
    else if(Data == "Sensor Off"){
      analogWrite(vibe1, 0);
      analogWrite(vibe2, 0);
      analogWrite(vibe3, 0);
      noTone(speaker);
      delay(500);
    }
  }
}
