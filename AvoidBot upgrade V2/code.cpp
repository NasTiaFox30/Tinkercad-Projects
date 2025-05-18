//Zadanie 4
// Zadanie numer 4 dotyczy zdalnie sterowanego robota mobilnego. Robot ma być
// wyposażony w 4 silniki, każdy silnik napędza inne koło. Robot ma posiadać czujniki
// ostrzegające użytkownika przed kolizją. Czyli w momencie zbliżania się do przeszkody
// czujniki mają ostrzegać o dystansie od przeszkody. Jeżeli odległość zmniejszy się do 2cm,
// ma zostać wykonany awaryjny stop robota wraz z wyświetleniem komunikatu o zadziałaniu
// układu. Robot ma być sterowany za pomocą joysticka. Wszystkie komunikaty, prędkość
// czy też kierunek jazdy mają się znajdować na ekranie LCD. Ponadto należy wyposażyć
// robota w czujnik wilgotności. Jeżeli zostanie wykryte wilgotne podłoże, ma pojawić się
// komunikat o tym oraz ostrzeżenie. Czujnik temperatury ma służyć do sprawdzania
// temperatury powietrza. W przypadku ujemnej temperatury ma zostać wyświetlone
// ostrzeżenie o możliwym oblodzeniu nawierzchni.


//Funkcjonalność:
// robot porusza się we wszystkich kierunkach za pomocą joysticka
// ^ - przód
// ~ - tył
// < - lewo
// > - prawo
// - - stop

// Komunikaty na LCD:
// - prędkość robota
// - odległość od przeszkody
// - odległość w calach
// - komunikaty o przeszkodzie
// - komunikaty o wilgotności
// - komunikaty o temperaturze
// robot robie awaryjne hamowanie, gdy wykryje przeszkodę

#include <LiquidCrystal.h>
LiquidCrystal LCD(12, 11, 5, 4, 3, 2);

//DC1 & DC2
int ptVal_1 = 0;
int PinDC_1 = 6;
int kierunekPinDC_1 = 7;
long ledVal_1;

//DC3 & DC4
int ptVal_2 = 0;
int PinDC_2 = 9;
int kierunekPinDC_2 = 8;
long ledVal_2;

int prendkosc = 50;

//Joystick
int PinJoyY = A0; // joystick Y-axis (potentiometer)
int PinJoyLeft = A1; // joystick X-axis (left)
int PinJoyRight = A2; // joystick X-axis (right)
long PinJoyY_val = 0; 

//LED
int PinRedLED = 10;

//Czujnik PING
int PinPING = A5;
int distanceThreshold = 0;
int cm = 0;
int inches = 0;
long readUltrasonicDistance(int triggerPin, int echoPin)
{
 pinMode(triggerPin, OUTPUT); // Clear the trigger
 digitalWrite(triggerPin, LOW);
 delayMicroseconds(2);
 // Sets the trigger pin to HIGH state for 10 microseconds
 digitalWrite(triggerPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(triggerPin, LOW);
 pinMode(echoPin, INPUT);
 // Reads the echo pin, and returns the sound wave travel time in microseconds
 return pulseIn(echoPin, HIGH);
}

//Czujnik Wilgotnosci
int pinSMSsensor = A3;
int pinSMSpowwer = 13;
int sensor = 0;
int dry = 200;

//Czujnik Temperatury
int pinTemp = A4;
int celsius = 0;
int cold = 0;



void setup()
{
  Serial.begin(9600);
  LCD.begin(16, 2);
  
 //DC silniki:
  //DC1 & DC2
  pinMode(PinDC_1, OUTPUT);
  pinMode(kierunekPinDC_1, OUTPUT);
  //DC3 & DC4
  pinMode(kierunekPinDC_2, OUTPUT);
  pinMode(PinDC_2, OUTPUT);

  //Joystick (prędkość i kierunek)
  pinMode(PinJoyY, INPUT);
  pinMode(PinJoyLeft, INPUT_PULLUP);
  pinMode(PinJoyRight, INPUT_PULLUP);
  
 //LED
  pinMode(PinRedLED, OUTPUT);
  
  //Czujnik Wilgotnosci
  pinMode(pinSMSpowwer,OUTPUT);
  pinMode(pinSMSsensor, INPUT);

  //Czujnik Temperatury
  pinMode(pinTemp, INPUT);
  
}

void loop()
{ 
// threshold - dystancja dla stopowania pojazdu
 distanceThreshold = 350;
 cm = 0.01723 * readUltrasonicDistance(PinPING, PinPING);
// konwersja inches
 inches = (cm / 2.54);

 //prendkosc (potensjometr)
 PinJoyY_val = analogRead(PinJoyY); 
  prendkosc = 0.2485 * PinJoyY_val;
  Serial.println(prendkosc);
  

//Stan pojazdu:  
 if (cm <= distanceThreshold - 250 && cm > distanceThreshold - 340) { //Jesli mniej niż 100cm
   stanJoystick(prendkosc);
   stanWilgotnosci();
   stanTemper();
  analogWrite(PinRedLED, 50);
  
    //Komunikaty na LCD:
    LCD.setCursor(8, 0);
    LCD.print("Uwaga!");
 }
 else if (cm <= distanceThreshold - 340) { //Jesli mniej niż 10cm (bo 2 cm nie działa)
  // Awaryjny STOP
  analogWrite(PinRedLED, 255);
   stopRobot(); 
  }
  else if(stanTemper() || stanWilgotnosci()){
    analogWrite(PinRedLED, 50);
  }
  else{
    stanJoystick(prendkosc);
    stanWilgotnosci();
    stanTemper();
    analogWrite(PinRedLED, 0);
  }
  
delay(50);
}


//Pojazd
void jezdzProsto(int prendkosc){
  Serial.println("prosto");
  LCD.setCursor(15, 0);
  LCD.print("^");

  analogWrite(PinDC_1, prendkosc);
  analogWrite(PinDC_2, prendkosc);
  //jazda wprost
  digitalWrite(kierunekPinDC_1, HIGH);
  digitalWrite(kierunekPinDC_2, LOW);
}
void jezdzDoTylu(int prendkosc){
  Serial.println("do tylu");
  LCD.setCursor(15, 0);
  LCD.print("~");

  analogWrite(PinDC_1, prendkosc);
  analogWrite(PinDC_2, prendkosc);
  //jazda do tylu
  digitalWrite(kierunekPinDC_1, LOW);
  digitalWrite(kierunekPinDC_2, HIGH);
}
void stopRobot(){
  Serial.println("STOP");
 
  analogWrite(PinDC_1, 0);
  analogWrite(PinDC_2, 0);
  digitalWrite(kierunekPinDC_1, LOW);
  digitalWrite(kierunekPinDC_2, LOW);
  
  //zatrzymanie LCD
  LCD.setCursor(0, 0);
  LCD.print("                ");
  LCD.setCursor(0, 1);
  LCD.print("STOP!         ");
}

void skrecWlewo(){
  Serial.println("lewo");
  LCD.setCursor(15, 0);
  LCD.print("<");
  
  //obrót o 90 stopni wlewo
  prendkosc = 10;
  analogWrite(PinDC_1, prendkosc);
  analogWrite(PinDC_2, prendkosc);
  digitalWrite(kierunekPinDC_1, HIGH);
  digitalWrite(kierunekPinDC_2, HIGH);
}
void skrecWPrawo(){
  Serial.println("prawo");
  LCD.setCursor(15, 0);
  LCD.print(">");
  
  //obrót o 90 stopni wprawo
  prendkosc = 10;
  analogWrite(PinDC_1, prendkosc);
  analogWrite(PinDC_2, prendkosc);
  digitalWrite(kierunekPinDC_1, LOW);
  digitalWrite(kierunekPinDC_2, LOW);
}

void stanJoystick(int prendkosc){
  //odczyt predkosci (potencjometru)
  int val = prendkosc;
  // Serial.println(val);

  //odczyt screniencia
  int buttonStateLeft = digitalRead(PinJoyLeft);
  int buttonStateRight = digitalRead(PinJoyRight);

  if (buttonStateLeft == HIGH || buttonStateRight == HIGH) //manewrowanie
  {
    if(buttonStateLeft == HIGH && buttonStateRight == LOW){
      skrecWlewo();
    }
    else if(buttonStateRight == HIGH && buttonStateLeft == LOW){
      skrecWPrawo();
    }
  }
  else{ //jazda Wprost i do Tylu
    if (val > 160) {
      LCD.setCursor(0, 0);
      LCD.print(prendkosc);
      LCD.print("m/s        ");
  
      jezdzProsto(prendkosc);
  
      //komunikaty na LCD: 
      czyszenieLCD();
      LCD.setCursor(0, 1);
       LCD.print(cm);
       LCD.print("cm | ");
       LCD.print(inches);
       LCD.println("in      ");
    }
    else if (val < 80) {
      LCD.setCursor(0, 0);
      LCD.print(prendkosc);
      LCD.print("m/s        ");
  
      jezdzDoTylu(prendkosc);
  
      //komunikaty na LCD:
      czyszenieLCD();
      LCD.setCursor(0, 1);
      LCD.print("                ");
    }
    else if(val <= 180 && val >= 80){ 
      stopRobot();
    }
  }
}

bool stanWilgotnosci(){
  //odczyt wilgotnosci
  digitalWrite(pinSMSpowwer, HIGH);
  sensor = analogRead(pinSMSsensor);
  digitalWrite(pinSMSpowwer,LOW);

  // Serial.println(sensor);

  if(sensor>dry){
    // Serial.println("WILGOTNE");
    LCD.setCursor(0, 0);
    LCD.print("Wilgotne       !");
    LCD.setCursor(0, 1);
    LCD.print("podloze        ");

    return true;
  }
  else if(sensor<dry){
    // Serial.println("SUCHE");
    analogWrite(PinRedLED, 0);

    return false;
  }
}

bool stanTemper(){
  //odczyt temperatury
  celsius = map(((analogRead(pinTemp) - 20) * 3.04), 0, 1023, -40, 125);

  // Serial.print("temperatura - ");
  // Serial.println(celsius);

  if(celsius<cold){
    // Serial.println("ZIMNO");
    LCD.setCursor(0, 0);
    LCD.print("Oblodzenie     !");
    LCD.setCursor(0, 1);
    LCD.print("nawierzchni     ");

    return true;
  }
  else if(celsius>=cold){
    // Serial.println("CIEPLO");
    analogWrite(PinRedLED, 0);

    return false;
  }
}

//dodatkowe metowy:

void czyszenieLCD(){
  //czyszczenie LCD
  if(prendkosc < 10){
    LCD.setCursor(1, 0);
    LCD.print("m/s   ");
  }
  else if(prendkosc < 100){
    LCD.setCursor(2, 0);
    LCD.print("m/s   ");
  }
  else if(prendkosc < 1000){
    LCD.setCursor(3, 0);
    LCD.print("m/s   ");
  }
}
