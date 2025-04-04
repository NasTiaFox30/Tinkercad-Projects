//Zadanie 2
// Układ oparty na serwomechanizmie. Kierunek oraz kąt obrotu mają być ustalane
// przez użytkownika poprzez konsolę. Jeżeli użytkownik będzie chciał obrócić się o -
// 90°, należy najpierw ustawić serwo w pozycji 180°. Ruch serwomechanizmu
// odbywa się w zakresie (0,180°). Wyświetlanie na wyświetlaczu LCD informacji na
// temat aktualnej prędkości, aktualnego i zadanego kąta obrotu.

//Funkcjonalność: 
// 1) Użytkownik podaje kąt obrotu serwomechanizmu (0-180°)
// 2) Użytkownik podaje prędkość obrotu serwomechanizmu (1-200ms)

// Wyświetlanie na wyświetlaczu LCD informacji na
// temat aktualnej prędkości, aktualnego i zadanego kąta obrotu.


#include <Servo.h>
Servo servoBase;//przypisanie serwo

#include <LiquidCrystal.h>
LiquidCrystal LCD(12, 11, 5, 4, 3, 2);

int kat = 0;
int input_kat = 0;
int prendkosc = 20;
bool operation_done1 = false;
bool operation_done2 = false;


void setup() {
 Serial.begin(9600);
 LCD.begin(16, 2);
  
 servoBase.attach(A1);//pin sterujacy
 servoBase.write(0); //masa dla serwa
 
 Serial.println("Podaj kat:");
  
}
void loop() {
  zadajWartosci();
  
  LCD.setCursor(0, 0);
  LCD.print("Kat:");
  LCD.setCursor(0, 1);
  LCD.print("Prendk:");
 

 servoBase.write(kat);
 LCD.setCursor(4, 0);
 LCD.print(kat);
  LCD.setCursor(7, 1);
 LCD.print(prendkosc);
  LCD.print("ms");
   
}

void zadajWartosci(){
  if (Serial.available() > 0) {
    if(!operation_done1){
      
      input_kat = Serial.parseInt();
      Serial.println("podano kat - ");
      Serial.println(input_kat);
      
  		Serial.println("Podaj predkosc (1-200):");
      czyszenieLCDKat();
      operation_done1 = true;
    }
    else if(operation_done1 && !operation_done2){
      prendkosc = Serial.parseInt();
      Serial.println("podano predkosc - ");
      Serial.println(prendkosc);
      
      czyszenieLCDPrendk();
      servoRotate();
  		Serial.println("Podaj kat (0-180 stopni):"); 
      operation_done1 = false;
    }
   
  }
}


void servoRotate(){
  int kierunek = (input_kat > kat) ? 1 : -1;

  while (kat != input_kat) {
    kat += kierunek;
    servoBase.write(kat);
    czyszenieLCDKat();
    delay(prendkosc);
  } 
}
  

void czyszenieLCDKat() {
  LCD.setCursor(0, 0);
  LCD.print("Kat:");
  LCD.print(kat);
  LCD.print("|");
  LCD.print(input_kat);
  LCD.print("st.");
  
  //czyszczenie
  if(input_kat < 10){
    LCD.setCursor(9, 0);
    LCD.print("st.  ");
    
    if(kat < 10){
    LCD.setCursor(7, 0);
    LCD.print("st.  ");
    }
    else if(kat < 100){
      LCD.setCursor(8, 0);
      LCD.print("st.  ");
    }
    
  }
  else if(input_kat < 100){
    LCD.setCursor(10, 0);
    LCD.print("st.  ");
    
   
    if(kat < 10){
    LCD.setCursor(8, 0);
    LCD.print("st.  ");
    }
    else if(kat < 100){
      LCD.setCursor(9, 0);
      LCD.print("st.  ");
    }
  }
 
 }

void czyszenieLCDPrendk(){
  LCD.setCursor(0, 1);
  LCD.print("               ");
  LCD.setCursor(0, 1);
  LCD.print("Prendk:");
  LCD.print(prendkosc);
  LCD.print("ms");
}