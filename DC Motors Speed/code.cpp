//Zadanie 1
//Zbudować układ oparty na dwóch silnikach DC, dołożyć wyświetlanie na ekranie
// LCD prędkości każdego z nich.

#include <LiquidCrystal.h>
LiquidCrystal LCD(12, 11, 5, 4, 3, 2);

//DC1
int ptVal_1 = 0;
int PinDC_1 = 6;
int ptMeter_1 = A0;
long ledVal_1;

//
int ptVal_2 = 0;
int PinDC_2 = 9;
int ptMeter_2 = A1;
long ledVal_2;


void setup()
{
  LCD.begin(16, 2);
  
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop()
{
LCD.setCursor(0, 0);
LCD.print("DC1 - ");
LCD.setCursor(0, 1);
LCD.print("DC2 - ");
  
//DC1
ptVal_1 = analogRead(A0);
ledVal_1 = 0.2485 * ptVal_1;
  
analogWrite(PinDC_1, ledVal_1);
LCD.setCursor(6, 0);
LCD.print(ledVal_1);
  
//DC2
ptVal_2 = analogRead(A1); 
ledVal_2 = 0.2485 * ptVal_2;
  
analogWrite(PinDC_2, ledVal_2);
LCD.setCursor(6, 1);
LCD.print(ledVal_2);
  
 
//czyszczenie LCD
  if(ledVal_1 < 10){
    LCD.setCursor(7, 0);
    LCD.print("  ");
  }
  else if(ledVal_1 < 100){
    LCD.setCursor(8, 0);
    LCD.print("  ");
  }
  
  if(ledVal_2 < 10){
    LCD.setCursor(7, 1);
    LCD.print("  ");
  }
  else if(ledVal_2 < 100){
    LCD.setCursor(8, 1);
    LCD.print("  ");
  }
}

