#include "LedControl.h"
#define DISP 8
LedControl lc = LedControl(DISP, DISP + 2, DISP + 1, 1);
 
int seconds_for_P1;
int seconds_for_P2;
int  minutes_for_P1=5;
int  increment_P1=0;
int  minutes_for_P2=5;
int  increment_P2=0;
int button_state_P1 = LOW;
int button_state_P2 = LOW;
int middle_button_state = LOW;
int button_P1 = 6;
int button_P2 = 7;
int middle_button = 13;
bool gameover = false;
float time_P1 = 0;
float time_P2 = 0;
bool is_P1s_turn = false;
bool is_P2s_turn = false;
float last_time_comparison_P1 = millis();
float last_time_comparison_P2 = millis();
int end_of_game=0;
bool whiteleft = true;
int minuteP1H = minutes_for_P1 / 10;
int minuteP1L = minutes_for_P1 - minuteP1H * 10;
int minuteP2H = minutes_for_P2 / 10;
int minuteP2L = minutes_for_P2 - minuteP2H * 10;
int secondP1H = seconds_for_P1 / 10;
int secondP1L = seconds_for_P1 - 10 * secondP1H;
int secondP2H = seconds_for_P2 / 10;
int secondP2L = seconds_for_P2 - 10 * secondP2H;
int buzzer = A1;  //A1
int countdown = -1;
bool pair = false;
 
void setup() {
 
   Serial.begin(9600);
  pinMode(button_P1, INPUT);
  pinMode(button_P2, INPUT);
  pinMode(middle_button, INPUT);
  pinMode(buzzer, OUTPUT);
 
  digitalWrite(button_P1, LOW);
  digitalWrite(button_P2, LOW);
  digitalWrite(middle_button, LOW);
 
  pinMode(DISP, OUTPUT);
  pinMode(DISP + 1, OUTPUT);
  pinMode(DISP + 2, OUTPUT);
 
    lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
 
}
 
void loop() {
 
affichage_increment_P1();
 
delay(150);
 
 if (digitalRead(button_P2) == HIGH) {
    minutes_for_P1++;
  }
 
   if (digitalRead(button_P1) == HIGH) {
    minutes_for_P1--;
  }
 
if (minutes_for_P1 <= 0) {
    time_P1 = 30000;
    minutes_for_P1 = 0;
    seconds_for_P1 = 30;
  }
 
  else { seconds_for_P1 = 0;}
 
  if (digitalRead(middle_button) == HIGH) {
    lc.clearDisplay(0);
    delay(150);
   
    configure_incP1();}
   
    else {loop();}
 
}
  
 void configure_incP1() {
  affichage_increment_P1();
 
delay(150);
 
if (digitalRead(button_P1) == HIGH && digitalRead(button_P2) == HIGH) {
 
    loop();
  }
 
  if (digitalRead(button_P2) == HIGH) {
    increment_P1++;
  }
 
 if (digitalRead(button_P1) == HIGH) {
   increment_P1--;
  }
 
  if (increment_P1 < 0) {
    increment_P1 = 0;
  }
 
    if (digitalRead(middle_button) == HIGH) {
    lc.clearDisplay(0);
    delay(150);
   
    configure_minP2();}
   
    else { configure_incP1();}
 }
 
 
void configure_minP2() {
  affichage_increment_P2();
 delay(150);
 
 if (digitalRead(button_P1) == HIGH && digitalRead(button_P2) == HIGH) {
 
    configure_incP1();
  }
 
  if (digitalRead(button_P2) == HIGH) {
    minutes_for_P2++;
  }
 
 if (digitalRead(button_P1) == HIGH) {
    minutes_for_P2--;
  }
 
    if (minutes_for_P2 <= 0) {
    time_P2 = 30000;
        minutes_for_P2 = 0;
    seconds_for_P2 = 30;
  }
  else { seconds_for_P2 = 0;}
 
   if (digitalRead(middle_button) == HIGH) {
    lc.clearDisplay(0);
    delay(150);
   
    configure_incP2();}
   
    else {configure_minP2();}
   
    }
 
 
  void configure_incP2() {
    affichage_increment_P2();
 
delay(150);
 
if (digitalRead(button_P1) == HIGH && digitalRead(button_P2) == HIGH) {
 
    configure_minP2();
  }
 
if (digitalRead(button_P2) == HIGH) {
    increment_P2++;
  }
 
 if (digitalRead(button_P1) == HIGH) {
   increment_P2--;
  }
 
  if (increment_P2 < 0) {
    increment_P2 = 0;
  }
 
  if (digitalRead(middle_button) == HIGH) {
    lc.clearDisplay(0);
    delay(150);
   
    time_P1 = (minutes_for_P1 * 60000);
    time_P2 = (minutes_for_P2 * 60000);
if (time_P1 == 0) {
  time_P1 = 30000;
}
if (time_P2 == 0) {
  time_P2 = 30000;
}
   
    increment_P1 = increment_P1 * 1000;
    increment_P2 = increment_P2 * 1000;
 
    digitalWrite(middle_button, LOW);
    delay(50);
    game();
  }
 
  else { configure_incP2();}
  }
 
 
void game() {
 
end_of_game = 0;
  button_state_P1 = digitalRead(button_P1);
button_state_P2 = digitalRead(button_P2);
middle_button_state = digitalRead(middle_button);
 
minutes_for_P1 = floor(time_P1 / 60000);
seconds_for_P1 = floor(time_P1 / 1000) - minutes_for_P1 * 60;
 
minutes_for_P2 = floor(time_P2 / 60000);
seconds_for_P2 = floor(time_P2 / 1000) - minutes_for_P2 * 60;
 
if (!is_P1s_turn && !is_P2s_turn && button_state_P1 == LOW && button_state_P2 == LOW) {
 
affichagelc();
   
  }

if (button_state_P1 == HIGH && button_state_P2 == LOW) {
 
digitalWrite(buzzer, HIGH);
 
 increment_player_1();}
 
if (button_state_P2 == HIGH && button_state_P1 == LOW) {
 
digitalWrite(buzzer, HIGH);
 
increment_player_2();
}
 
if (middle_button_state == HIGH && is_P1s_turn) {
 
  pauseP1();
}
 
 
if (middle_button_state == HIGH && is_P2s_turn) {
 
  pauseP2();
}
 
if (is_P1s_turn) {
 
  Update_time_P1();
 
}
else if (!(!is_P1s_turn && !is_P2s_turn)) {
  Update_time_P2();
}
 
else {
delay(150);
game();  
 }
 
}
 
 void Update_time_P1() {
 
  time_P1 -= ((millis() - last_time_comparison_P1));
  last_time_comparison_P1 = millis();
 
 
if (time_P1 <= 0) {
  gameover = true;
 
  gameOver();
}
 
affichagelc();
 
game();
 
}
 
void Update_time_P2() {
 
  time_P2 -= ((millis() - last_time_comparison_P2));
  last_time_comparison_P2 = millis();
 
 if (time_P2 <= 0) {
  gameover = true;
 gameOver();
}
 
affichagelc();
game();
}
 
 
void P1_turn() {
  digitalWrite(buzzer, LOW);
if (is_P1s_turn) {
 return;
}
 
is_P2s_turn = false;
is_P1s_turn = true;
countdown++;
pair = !pair;
last_time_comparison_P1 = millis();
 game();
}
 
 
void P2_turn() {
  digitalWrite(buzzer, LOW);
if (is_P2s_turn) {
  return;
}
 
is_P1s_turn = false;
is_P2s_turn = true;
countdown++;
pair=!pair;
last_time_comparison_P2 = millis();
  game();
}
 
void gameOver() {
 
  button_state_P1 = digitalRead(button_P1);
button_state_P2 = digitalRead(button_P2);
middle_button_state = digitalRead(middle_button);
 
if (middle_button_state == HIGH) {
  countdown = -1;
  pair=false;
time_P1 = 0;
time_P2 = 0;
is_P1s_turn = false;
is_P2s_turn = false;
seconds_for_P1 = 0;
seconds_for_P2 = 0;
 minutes_for_P1=5;
increment_P1=0;
minutes_for_P2=5;
increment_P2=0;
 
  delay(150);
loop();
}
 
 
if (time_P1 <= 0 && middle_button_state == LOW) {
 
 
  digitalWrite(buzzer, HIGH);
  delay(100);
   
    digitalWrite(buzzer, LOW);
  delay(100);
 
 
gameOver(); }
 
if (time_P2 <= 0 && middle_button_state == LOW) {
 
  digitalWrite(buzzer, HIGH);
  delay(100);
   
    digitalWrite(buzzer, LOW);
  delay(100);
 
 
gameOver();
}
 
}
 
 
void increment_player_1() {
 
 
if (is_P1s_turn) {
  time_P1 = time_P1 + (increment_P1);
 
  P2_turn();
}
 
else {
 
  P2_turn();}
 
}
  
void increment_player_2() {
  if (is_P2s_turn) {
 
time_P2 = time_P2 + (increment_P2);
 
 
  P1_turn();}
 
  else {
 
    P1_turn();}}

void affichagelc() {
minuteP1H = minutes_for_P1 / 10;
minuteP1L = minutes_for_P1 - minuteP1H * 10;
minuteP2H = minutes_for_P2 / 10;
minuteP2L = minutes_for_P2 - minuteP2H * 10;
secondP1H = seconds_for_P1 / 10;
secondP1L = seconds_for_P1 - 10 * secondP1H;
secondP2H = seconds_for_P2 / 10;
secondP2L = seconds_for_P2 - 10 * secondP2H;
 
if (minuteP1H == 0) {
         
        lc.setChar(0, 7, ' ', false);
}
 else {lc.setDigit(0, 7, minuteP1H, false);}
 
    lc.setDigit(0, 5, secondP1H, false);
if (minuteP2H == 0) {
         
        lc.setChar(0, 3, ' ', false);
}
 else {lc.setDigit(0, 3, minuteP2H, false);}
 lc.setDigit(0, 4, secondP1L, false);
    lc.setDigit(0, 1, secondP2H, false);
    lc.setDigit(0, 0, secondP2L, false);
 
  switch (minuteP1L) {
      case 0: lc.setRow(0, 6, B11111110);
        break;
      case 1: lc.setRow(0, 6, B10110000);
        break;
      case 2: lc.setRow(0, 6, B11101101);
        break;
      case 3: lc.setRow(0, 6, B11111001);
        break;
      case 4: lc.setRow(0, 6, B10110011);
        break;
      case 5: lc.setRow(0, 6, B11011011);
        break;
      case 6: lc.setRow(0, 6, B11011111);
        break;
      case 7: lc.setRow(0, 6, B11110000);
        break;
      case 8: lc.setRow(0, 6, B11111111);
        break;
      case 9: lc.setRow(0, 6, B11111011);
        break;
    }
   
  switch (minuteP2L) {
      case 0: lc.setRow(0, 2, B11111110);
        break;
      case 1: lc.setRow(0, 2, B10110000);
        break;
      case 2: lc.setRow(0, 2, B11101101);
        break;
      case 3: lc.setRow(0, 2, B11111001);
        break;
      case 4: lc.setRow(0, 2, B10110011);
        break;
      case 5: lc.setRow(0, 2, B11011011);
        break;
      case 6: lc.setRow(0, 2, B11011111);
        break;
      case 7: lc.setRow(0, 2, B11110000);
        break;
      case 8: lc.setRow(0, 2, B11111111);
        break;
      case 9: lc.setRow(0, 2, B11111011);
        break;
    }}
  
void pauseP1() {
 
        lc.clearDisplay(0);
        lc.setChar(0, 7, 'P', false);
        lc.setChar(0, 6, '1', false);
        lc.setChar(0, 4, '5', false);
        lc.setRow(0, 3, B00001111);
        lc.setDigit(0, 2, 0, false);
        lc.setChar(0, 1, 'P', false);
 
  delay(300);
  int paused_by_P1 = 1;
 
button_state_P1 = digitalRead(button_P1);
button_state_P2 = digitalRead(button_P2);
middle_button_state = digitalRead(middle_button);

is_P1s_turn = false;
is_P2s_turn = false;
 
 
if (middle_button_state == HIGH && paused_by_P1 == 1) {
 
delay(250);
last_time_comparison_P1 = millis();
is_P1s_turn = true;
  game();
}
 
if (middle_button_state == LOW && button_state_P1 == HIGH && button_state_P2 == HIGH) {
  softReset();
 
end_of_game = 1;
delay(250);
loop();
}
 
 
else {
 
  pauseP1();
 
}
}
 
 
void pauseP2() {
 
          lc.clearDisplay(0);
        lc.setChar(0, 7, 'P', false);
        lc.setChar(0, 6, '2', false);
        lc.setChar(0, 4, '5', false);
        lc.setRow(0, 3, B00001111);
        lc.setDigit(0, 2, 0, false);
        lc.setChar(0, 1, 'P', false);
  delay(300);
  int paused_by_P2 = 1;
 
button_state_P1 = digitalRead(button_P1);
button_state_P2 = digitalRead(button_P2);
middle_button_state = digitalRead(middle_button);
 
is_P1s_turn = false;
is_P2s_turn = false;
 
 
if (middle_button_state == HIGH && paused_by_P2 == 1) {
 
delay(250);
last_time_comparison_P2 = millis();
is_P2s_turn = true;
  game();
}
 
if (middle_button_state == LOW && button_state_P1 == HIGH && button_state_P2 == HIGH) {
  softReset();
  end_of_game = 1;
 
delay(250);
loop();
}
 
else {
 
  pauseP2();
 
}
}
 
 
void softReset(){
asm volatile ("  jmp 0");
}
 
 
void affichage_increment_P1() {
 
 
  lc.setChar(0, 7, 'P', false);
  lc.setChar(0, 6, '1', false);
  lc.setChar(0, 5, ' ', false);
  lc.setChar(0, 4, '0', false);
  if (minutes_for_P1 <= 9) {
   
  lc.setDigit(0, 4, '0', false);
  lc.setDigit(0, 3, minutes_for_P1, false);
  }
   if (minutes_for_P1 >= 10) {
  lc.setDigit(0, 4, minutes_for_P1 / 10, false);
  lc.setDigit(0, 3, minutes_for_P1 - (minutes_for_P1 / 10) *10, false);
  }
 
  lc.setRow(0, 2, B00000001);
 
  if (increment_P1 <=9){
          lc.setChar(0, 1, ' ', false);
        lc.setDigit(0, 0, increment_P1, false);
  }
if (increment_P1 >= 10){
          lc.setDigit(0, 1, increment_P1 / 10, false);
        lc.setDigit(0, 0, increment_P1 - (increment_P1 / 10) * 10, false);
  }
  
}
 
void affichage_increment_P2() {
 
  lc.setChar(0, 7, 'P', false);
  lc.setChar(0, 6, '2', false);
  lc.setChar(0, 5, ' ', false);
  lc.setChar(0, 4, '0', false);
  if (minutes_for_P2 <= 9) {
  lc.setDigit(0, 4, '0', false);
  lc.setDigit(0, 3, minutes_for_P2, false);
  }
   if (minutes_for_P2 >= 10) {
  lc.setDigit(0, 4, minutes_for_P2 / 10, false);
  lc.setDigit(0, 3, minutes_for_P2 - (minutes_for_P2 / 10) *10, false);
  }
 
  lc.setRow(0, 2, B00000001);
 
  if (increment_P2 <=9){
          lc.setChar(0, 1, ' ', false);
        lc.setDigit(0, 0, increment_P2, false);
  }
if (increment_P2 >= 10){
          lc.setDigit(0, 1, increment_P2 / 10, false);
        lc.setDigit(0, 0, increment_P2 - (increment_P2 / 10) * 10, false);
  }
 
 
}
