#include "LedControl.h"
#define DISP 8
LedControl lc = LedControl(DISP, DISP + 2, DISP + 1, 1);
 
int secondes_pour_P1;
int secondes_pour_P2;
int  minutes_pour_P1=5;
int  increment_P1=0;
int  minutes_pour_P2=5;
int  increment_P2=0;
int etat_bouton_P1 = LOW;
int etat_bouton_P2 = LOW;
int etat_bouton3 = LOW;
int bouton_P1 = 6;
int bouton_P2 = 7;
int bouton3 = 13;
bool gameover = false;
float temps_P1 = 0;
float temps_P2 = 0;
bool est_le_tour_de_P1 = false;
bool est_le_tour_de_P2 = false;
float derniere_comp_P1 = millis();
float derniere_comp_P2 = millis();
int fin_partie=0;
bool whiteleft = true;
int minuteP1H = minutes_pour_P1 / 10;
int minuteP1L = minutes_pour_P1 - minuteP1H * 10;
int minuteP2H = minutes_pour_P2 / 10;
int minuteP2L = minutes_pour_P2 - minuteP2H * 10;
int secondP1H = secondes_pour_P1 / 10;
int secondP1L = secondes_pour_P1 - 10 * secondP1H;
int secondP2H = secondes_pour_P2 / 10;
int secondP2L = secondes_pour_P2 - 10 * secondP2H;
int buzzer = A1;  //A1
int compteur = -1;
bool pair = false;
 
void setup() {
 
   Serial.begin(9600);
  pinMode(bouton_P1, INPUT);
  pinMode(bouton_P2, INPUT);
  pinMode(bouton3, INPUT);
  pinMode(buzzer, OUTPUT);
 
  digitalWrite(bouton_P1, LOW);
  digitalWrite(bouton_P2, LOW);
  digitalWrite(bouton3, LOW);
 
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
 
 if (digitalRead(bouton_P2) == HIGH) {
    minutes_pour_P1++;
  }
 
   if (digitalRead(bouton_P1) == HIGH) {
    minutes_pour_P1--;
  }
 
if (minutes_pour_P1 <= 0) {
    temps_P1 = 30000;
    minutes_pour_P1 = 0;
    secondes_pour_P1 = 30;
  }
 
  else { secondes_pour_P1 = 0;}
 
  if (digitalRead(bouton3) == HIGH) {
    lc.clearDisplay(0);
    delay(150);
   
    configure_incP1();}
   
    else {loop();}
 
}
  
 void configure_incP1() {
  affichage_increment_P1();
 
delay(150);
 
if (digitalRead(bouton_P1) == HIGH && digitalRead(bouton_P2) == HIGH) {
 
    loop();
  }
 
  if (digitalRead(bouton_P2) == HIGH) {
    increment_P1++;
  }
 
 if (digitalRead(bouton_P1) == HIGH) {
   increment_P1--;
  }
 
  if (increment_P1 < 0) {
    increment_P1 = 0;
  }
 
    if (digitalRead(bouton3) == HIGH) {
    lc.clearDisplay(0);
    delay(150);
   
    configure_minP2();}
   
    else { configure_incP1();}
 }
 
 
void configure_minP2() {
  affichage_increment_P2();
 delay(150);
 
 if (digitalRead(bouton_P1) == HIGH && digitalRead(bouton_P2) == HIGH) {
 
    configure_incP1();
  }
 
  if (digitalRead(bouton_P2) == HIGH) {
    minutes_pour_P2++;
  }
 
 if (digitalRead(bouton_P1) == HIGH) {
    minutes_pour_P2--;
  }
 
    if (minutes_pour_P2 <= 0) {
    temps_P2 = 30000;
        minutes_pour_P2 = 0;
    secondes_pour_P2 = 30;
  }
  else { secondes_pour_P2 = 0;}
 
   if (digitalRead(bouton3) == HIGH) {
    lc.clearDisplay(0);
    delay(150);
   
    configure_incP2();}
   
    else {configure_minP2();}
   
    }
 
 
  void configure_incP2() {
    affichage_increment_P2();
 
delay(150);
 
if (digitalRead(bouton_P1) == HIGH && digitalRead(bouton_P2) == HIGH) {
 
    configure_minP2();
  }
 
if (digitalRead(bouton_P2) == HIGH) {
    increment_P2++;
  }
 
 if (digitalRead(bouton_P1) == HIGH) {
   increment_P2--;
  }
 
  if (increment_P2 < 0) {
    increment_P2 = 0;
  }
 
  if (digitalRead(bouton3) == HIGH) {
    lc.clearDisplay(0);
    delay(150);
   
    temps_P1 = (minutes_pour_P1 * 60000);
    temps_P2 = (minutes_pour_P2 * 60000);
if (temps_P1 == 0) {
  temps_P1 = 30000;
}
if (temps_P2 == 0) {
  temps_P2 = 30000;
}
   
    increment_P1 = increment_P1 * 1000;
    increment_P2 = increment_P2 * 1000;
 
    digitalWrite(bouton3, LOW);
    delay(50);
    game();
  }
 
  else { configure_incP2();}
  }
 
 
void game() {
 
fin_partie = 0;
  etat_bouton_P1 = digitalRead(bouton_P1);
etat_bouton_P2 = digitalRead(bouton_P2);
etat_bouton3 = digitalRead(bouton3);
 
minutes_pour_P1 = floor(temps_P1 / 60000);
secondes_pour_P1 = floor(temps_P1 / 1000) - minutes_pour_P1 * 60;
 
minutes_pour_P2 = floor(temps_P2 / 60000);
secondes_pour_P2 = floor(temps_P2 / 1000) - minutes_pour_P2 * 60;
 
if (!est_le_tour_de_P1 && !est_le_tour_de_P2 && etat_bouton_P1 == LOW && etat_bouton_P2 == LOW) {
 
affichagelc();
   
  }

if (etat_bouton_P1 == HIGH && etat_bouton_P2 == LOW) {
 
digitalWrite(buzzer, HIGH);
 
 increment_joueur_1();}
 
if (etat_bouton_P2 == HIGH && etat_bouton_P1 == LOW) {
 
digitalWrite(buzzer, HIGH);
 
increment_joueur_2();
}
 
if (etat_bouton3 == HIGH && est_le_tour_de_P1) {
 
  pauseP1();
}
 
 
if (etat_bouton3 == HIGH && est_le_tour_de_P2) {
 
  pauseP2();
}
 
if (est_le_tour_de_P1) {
 
  Update_temps_P1();
 
}
else if (!(!est_le_tour_de_P1 && !est_le_tour_de_P2)) {
  Update_temps_P2();
}
 
else {
delay(150);
game();  
 }
 
}
 
 void Update_temps_P1() {
 
  temps_P1 -= ((millis() - derniere_comp_P1));
  derniere_comp_P1 = millis();
 
 
if (temps_P1 <= 0) {
  gameover = true;
 
  gameOver();
}
 
affichagelc();
 
game();
 
}
 
void Update_temps_P2() {
 
  temps_P2 -= ((millis() - derniere_comp_P2));
  derniere_comp_P2 = millis();
 
 if (temps_P2 <= 0) {
  gameover = true;
 gameOver();
}
 
affichagelc();
game();
}
 
 
void Au_tour_de_P1() {
  digitalWrite(buzzer, LOW);
if (est_le_tour_de_P1) {
 return;
}
 
est_le_tour_de_P2 = false;
est_le_tour_de_P1 = true;
compteur++;
pair = !pair;
derniere_comp_P1 = millis();
 game();
}
 
 
void Au_tour_de_P2() {
  digitalWrite(buzzer, LOW);
if (est_le_tour_de_P2) {
  return;
}
 
est_le_tour_de_P1 = false;
est_le_tour_de_P2 = true;
compteur++;
pair=!pair;
derniere_comp_P2 = millis();
  game();
}
 
void gameOver() {
 
  etat_bouton_P1 = digitalRead(bouton_P1);
etat_bouton_P2 = digitalRead(bouton_P2);
etat_bouton3 = digitalRead(bouton3);
 
if (etat_bouton3 == HIGH) {
  compteur = -1;
  pair=false;
temps_P1 = 0;
temps_P2 = 0;
est_le_tour_de_P1 = false;
est_le_tour_de_P2 = false;
secondes_pour_P1 = 0;
secondes_pour_P2 = 0;
 minutes_pour_P1=5;
increment_P1=0;
minutes_pour_P2=5;
increment_P2=0;
 
  delay(150);
loop();
}
 
 
if (temps_P1 <= 0 && etat_bouton3 == LOW) {
 
 
  digitalWrite(buzzer, HIGH);
  delay(100);
   
    digitalWrite(buzzer, LOW);
  delay(100);
 
 
gameOver(); }
 
if (temps_P2 <= 0 && etat_bouton3 == LOW) {
 
  digitalWrite(buzzer, HIGH);
  delay(100);
   
    digitalWrite(buzzer, LOW);
  delay(100);
 
 
gameOver();
}
 
}
 
 
void increment_joueur_1() {
 
 
if (est_le_tour_de_P1) {
  temps_P1 = temps_P1 + (increment_P1);
 
  Au_tour_de_P2();
}
 
else {
 
  Au_tour_de_P2();}
 
}
  
void increment_joueur_2() {
  if (est_le_tour_de_P2) {
 
temps_P2 = temps_P2 + (increment_P2);
 
 
  Au_tour_de_P1();}
 
  else {
 
    Au_tour_de_P1();}}

void affichagelc() {
minuteP1H = minutes_pour_P1 / 10;
minuteP1L = minutes_pour_P1 - minuteP1H * 10;
minuteP2H = minutes_pour_P2 / 10;
minuteP2L = minutes_pour_P2 - minuteP2H * 10;
secondP1H = secondes_pour_P1 / 10;
secondP1L = secondes_pour_P1 - 10 * secondP1H;
secondP2H = secondes_pour_P2 / 10;
secondP2L = secondes_pour_P2 - 10 * secondP2H;
 
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
  int estpauseP1 = 1;
 
etat_bouton_P1 = digitalRead(bouton_P1);
etat_bouton_P2 = digitalRead(bouton_P2);
etat_bouton3 = digitalRead(bouton3);

est_le_tour_de_P1 = false;
est_le_tour_de_P2 = false;
 
 
if (etat_bouton3 == HIGH && estpauseP1 == 1) {
 
delay(250);
derniere_comp_P1 = millis();
est_le_tour_de_P1 = true;
  game();
}
 
if (etat_bouton3 == LOW && etat_bouton_P1 == HIGH && etat_bouton_P2 == HIGH) {
  softReset();
 
fin_partie = 1;
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
  int estpauseP2 = 1;
 
etat_bouton_P1 = digitalRead(bouton_P1);
etat_bouton_P2 = digitalRead(bouton_P2);
etat_bouton3 = digitalRead(bouton3);
 
est_le_tour_de_P1 = false;
est_le_tour_de_P2 = false;
 
 
if (etat_bouton3 == HIGH && estpauseP2 == 1) {
 
delay(250);
derniere_comp_P2 = millis();
est_le_tour_de_P2 = true;
  game();
}
 
if (etat_bouton3 == LOW && etat_bouton_P1 == HIGH && etat_bouton_P2 == HIGH) {
  softReset();
  fin_partie = 1;
 
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
  if (minutes_pour_P1 <= 9) {
   
  lc.setDigit(0, 4, '0', false);
  lc.setDigit(0, 3, minutes_pour_P1, false);
  }
   if (minutes_pour_P1 >= 10) {
  lc.setDigit(0, 4, minutes_pour_P1 / 10, false);
  lc.setDigit(0, 3, minutes_pour_P1 - (minutes_pour_P1 / 10) *10, false);
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
  if (minutes_pour_P2 <= 9) {
  lc.setDigit(0, 4, '0', false);
  lc.setDigit(0, 3, minutes_pour_P2, false);
  }
   if (minutes_pour_P2 >= 10) {
  lc.setDigit(0, 4, minutes_pour_P2 / 10, false);
  lc.setDigit(0, 3, minutes_pour_P2 - (minutes_pour_P2 / 10) *10, false);
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
