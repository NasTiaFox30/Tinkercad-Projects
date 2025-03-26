// Zadanie 2. 
// Stwórz prosty kalkulator, którego wynik będzie podawany na wyświetlaczu LCD.
// Dane podawane przez użytkownika z klawiatury poprzez interfejs szeregowy

//Funkcjonalność:  


#include <LiquidCrystal.h>

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

//L:iczby
int x;
int y;
char znak;
int index_of_step = 0;
bool operation_done = false;


void setup()
{
  //inicjalizacja komunikacji szeregowej 9600 buts per second
  Serial.begin(9600);
  
  lcd_1.begin(16, 2);

    lcd_1.setCursor(0, 0);
    //Wyświetl komunikat na początku programu
    lcd_1.print("Podaj 1 liczbe");
}

void loop()
{
    if(!operation_done){
        //Wyczytuje dane z konsoli
        if (Serial.available() > 0) {
            //konwertuje i przypisuje do tablicy

            switch(index_of_step){
                case 0:
                    x = Serial.parseInt();
                    lcd_1.setCursor(1, 1);
                    // lcd_1.clear();
                    // lcd_1.print(x);
                    index_of_step++;
                    lcd_1.clear();
                    lcd_1.print("Podaj znak +-*/");
                    break;
                case 1:
                    znak = Serial.read();
                    lcd_1.setCursor(1, 1);
                    // lcd_1.clear();
                    // lcd_1.print(znak);
                    index_of_step++;
                    lcd_1.clear();
                    lcd_1.print("Podaj 2 liczbe");
                    break;
                case 2:
                    y = Serial.parseInt();
                    lcd_1.setCursor(1, 1);
                    // lcd_1.clear();
                    // lcd_1.print(y);
                    index_of_step++;
                    break;
            }

            if(index_of_step >= 3){
                index_of_step = 0;
                lcd_1.clear();
                lcd_1.setCursor(1, 0);
                lcd_1.print(x);
                lcd_1.print(znak);
                lcd_1.print(y);
                lcd_1.print("=");

                lcd_1.setCursor(1, 1);
                Wynik_operacji();

                //zatrzyma zczytywanie konsoli
                Serial.end();
                //zakoczenie operacji po 10 sekundach
                delay(10000);
                operation_done = true;
            }
        }
    }
    else{
        lcd_1.clear(); 
        Serial.begin(9600);
        lcd_1.print("Podaj 1 liczbe");
        operation_done = false;
    }
} 

void Wynik_operacji() {
    switch(znak){
        case '+':
            lcd_1.print(x + y);
        break;
        case '-':
            lcd_1.print(x - y);
        break;
        case '*':
            lcd_1.print(x * y);
        break;
        case '/':
            //sprawdzenie dzielenia przez 0
            if(y == 0){
                lcd_1.clear();
                lcd_1.setCursor(0, 0);
                lcd_1.print("Error");
                index_of_step = 0;
            }
            else{
                lcd_1.print((float)x / (float)y);
            }            
        break;
        default:
            lcd_1.clear();
            lcd_1.setCursor(0, 0);
            lcd_1.print("Error");
            lcd_1.setCursor(1, 1);
            lcd_1.print("Niewiadomy znak!");
    }  
}
