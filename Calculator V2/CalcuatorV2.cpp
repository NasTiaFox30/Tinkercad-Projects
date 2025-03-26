// Zadanie 3. 
// Zadanie 2 przerobić w taki sposób, żeby liczby oraz rodzaj działania były
// podawane z klawiatury 4x4

//Funkcjonalność:  
//Wyswietlanie instrukcji na wyswietlaczu:

//1) Podanie 1-ej liczby

//2) Podanie znaku peracji: 
// A jest '+'
// B jest '-'
// C jest '*'
// D jest '/'

//3) Podanie 2-ej liczby

//Otrzymany wynik widać na wyświetlaczu
//po 10 sekundach - automatyczne resetowanie programu


#include <LiquidCrystal.h>

const int buttonRows = 4;
const int buttonCols = 4;

char buttons[buttonRows][buttonCols] = {
 {'1', '2', '3', '+'},
 {'4', '5', '6', '-'},
 {'7', '8', '9', '*'},
 {' ', '0', '#', '/'}
};

int buttonPins[buttonRows] = {9, 8, 7, 6};
int buttonColsPins[buttonCols] = {5, 4, 3, 2};




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
    lcd_1.print("Wpisz z klawiatury");
}

void loop()
{

    char keypressed = getKeyFromButtons();
    
 
    if(!operation_done){
        //Wyczytuje dane z klawiatury
        if (keypressed != ' ') {
        Serial.print(keypressed);

        // if(keypressed == '#'){
        //     //zatrzyma zczytywanie konsoli
        //     Serial.end();
        //     //nagłe zakoczenie operacji
        //     operation_done = true;
        // }
    
            //konwertuje i przypisuje do tablicy

            switch(index_of_step){
                case 0: //1 liczba
                    // x = Serial.parseInt();
                    x = keypressed - '0';   //konwertacja jako liczba
                    lcd_1.setCursor(1, 1);
                    index_of_step++;
                    lcd_1.clear();
                    // lcd_1.print("Podaj znak +-*/");
                    Serial.print(x);
                    lcd_1.print(x);
                    break;
                case 1: //2 liczba
                    // znak = Serial.read();
                    znak = keypressed;
                    lcd_1.setCursor(1, 1);
                    index_of_step++;
                    lcd_1.clear();
                    // lcd_1.print("Podaj 2 liczbe");
                    Serial.print(znak);
                    lcd_1.print(znak);
                    break;
                case 2: //znak operacji
                    // y = Serial.parseInt();
                    y = keypressed - '0';
                    lcd_1.setCursor(1, 1);
                    index_of_step++;
                    Serial.print(y);
                    lcd_1.print(y);
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
        lcd_1.print("Wpisz z klawiatury");
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

char getKeyFromButtons() {
 for (int row = 0; row < buttonRows; ++row) {
 pinMode(buttonPins[row], OUTPUT);
 digitalWrite(buttonPins[row], LOW);
   for (int col = 0; col < buttonCols; ++col) {
     pinMode(buttonColsPins[col], INPUT_PULLUP);
     if (digitalRead(buttonColsPins[col]) == LOW) {
     delay(200); // Debounce delay

     while (digitalRead(buttonColsPins[col]) == LOW); // Чекаємо, поки кнопку не відпустять
     
     return buttons[row][col];
     }
   }
   digitalWrite(buttonPins[row], HIGH);
   pinMode(buttonPins[row], INPUT);
   }
   return ' ';
}