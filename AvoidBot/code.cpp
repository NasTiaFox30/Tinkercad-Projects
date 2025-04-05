//Zadanie 3
//Połączyć układ z dwoma silnikami DC oraz czujnikiem odległości. Zasymulować
//zachowanie robota, który dociera do przeszkody. Robot ma ominąć przeszkodę
//(sposób dowolny).

//Silniki ułożone jak w hoverboard'u!

//Funkcjonalność:
// robot porusza się do przodu, gdy nie ma przeszkody
// robot zatrzymuje się, gdy wykryje przeszkodę
// robot omija przeszkodę wykonując skręt w lewo, następnie jazda do przodu i skręt w prawo

#include <LiquidCrystal.h>
LiquidCrystal LCD(12, 11, 5, 4, 3, 2);

//DC1
int ptVal_1 = 0;
int PinDC_1 = 6;
int kierunekPinDC_1 = 7;
long ledVal_1;

//DC2
int ptVal_2 = 0;
int PinDC_2 = 9;
int kierunekPinDC_2 = 8;
long ledVal_2;

int prendkosc = 50;


//LED
int PinLED = 13;

//Czujnik PING
int PinPING = 10;
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

//Tryby:
bool stanPojazdu = true;
bool stanObjazdu = false;
bool skrecenieWprawo = false;
bool skrecenieWlewo = false;


void setup()
{
  Serial.begin(9600);
  LCD.begin(16, 2);
  
 //DC silniki:
  //DC1
  pinMode(PinDC_1, OUTPUT);
  pinMode(kierunekPinDC_1, OUTPUT);
  //DC2
  pinMode(kierunekPinDC_2, OUTPUT);
  pinMode(PinDC_2, OUTPUT);
  
 //LED
  pinMode(PinLED, OUTPUT);
  
}

void loop()
{ 
// threshold - dystancja dla stopowania pojazdu
 distanceThreshold = 350;
 cm = 0.01723 * readUltrasonicDistance(PinPING, PinPING);
// konwersja inches
 inches = (cm / 2.54);
  
//Tryb pojazdu:
  
  if(stanPojazdu){		//START
    //Serial.println("prosto");
    LCD.setCursor(15, 0);
    LCD.print("^");
      
    prendkosc = 50;
    analogWrite(PinDC_1, prendkosc);
    analogWrite(PinDC_2, prendkosc);
    //jazda wprost
    digitalWrite(kierunekPinDC_1, HIGH);
    digitalWrite(kierunekPinDC_2, LOW);
      
      //komunikaty na LCD: 
    LCD.setCursor(0, 1);
     LCD.print(cm);
     LCD.print("cm | ");
     LCD.print(inches);
     LCD.println("in      ");
  }
  else{		//STOP
    //Serial.println("STOP");
    LCD.setCursor(15, 0);
    LCD.print("-");
    
    prendkosc = 0;
    analogWrite(PinDC_1, prendkosc );
    analogWrite(PinDC_2, prendkosc );
    
    LCD.setCursor(0, 1);
    LCD.print("Przeszkoda!    ");
  }
  LCD.setCursor(0, 0);
  LCD.print(prendkosc);
  LCD.print("m/s");
  
  
//Tryb objazdu przy napotykania obiektu:
  //Jesli mniej niż 100cm
 if (cm <= distanceThreshold - 250) {
 	digitalWrite(PinLED, HIGH);
   	czyszenieLCD();
   
   //włączenie trybu objazdu obiektu
	obujazdPojazdu();
 }
 else{
   digitalWrite(PinLED, LOW);
   czyszenieLCD();
   
   stanPojazdu = true;
  }
  
delay(50);
}


void obujazdPojazdu(){
  //Serial.println("OBJAZD");
  LCD.setCursor(15, 0);
    LCD.print("*");
  
  stanPojazdu = false;
  stanObjazdu = true;
  //1 Najpierw odjaz o drobinkę do tylu 
  //2 obracanie o 90 stopni w lewo
  //3 jazda prosto 
  //4 obracanie o 90 stopni w prawo
  // Jazda wprost jeśli niema przeszkody
  
  //1.
  //trwa 2 sekundy
  if(stanObjazdu && !skrecenieWlewo && !skrecenieWprawo){
    //Serial.println("do tylu");
    LCD.setCursor(15, 0);
    LCD.print("~");
    
    prendkosc = 5;
    analogWrite(PinDC_1, prendkosc);
    analogWrite(PinDC_2, prendkosc);
    //jazda do tylu
    digitalWrite(kierunekPinDC_1, LOW);
    digitalWrite(kierunekPinDC_2, HIGH);
    czyszenieLCD();
    
    delay(3000);
    skrecenieWlewo = true;
    stanObjazdu = false;
  }
  
  //2.
  //skręcenie 2 sekundy
  if(skrecenieWlewo && !skrecenieWprawo){
    //Serial.println("lewo");
    LCD.setCursor(15, 0);
    LCD.print("<");
    
    //obrót o 90 stopni wlewo
    prendkosc = 20;
    analogWrite(PinDC_1, prendkosc);
    analogWrite(PinDC_2, prendkosc);
    digitalWrite(kierunekPinDC_1, HIGH);
    digitalWrite(kierunekPinDC_2, HIGH);
    delay(2000);  
    
    skrecenieWlewo = false;
    
    //3.
    jezdzWprost(3000);		//3000 milikekund nawprost
  }
  
  //4.
  if(skrecenieWprawo && !skrecenieWlewo){
    //Serial.println("prawo");
    LCD.setCursor(15, 0);
    LCD.print(">");
    
    //obrót o 90 stopni wprawo
    prendkosc = 20;
    analogWrite(PinDC_1, prendkosc);
    analogWrite(PinDC_2, prendkosc);
    digitalWrite(kierunekPinDC_1, LOW);
    digitalWrite(kierunekPinDC_2, LOW);
    delay(2000);
    
    skrecenieWprawo = false;
    stanPojazdu = true; 
  }  
  
}

void jezdzWprost(int milisekund){
  //Serial.println("3 sek. prosto");
  LCD.setCursor(15, 0);
  LCD.print("^");
  
  //ruszamy wprost
  stanPojazdu = true;
  delay(milisekund);
 
  skrecenieWprawo = true;	//trwa 2000 milisekund
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

