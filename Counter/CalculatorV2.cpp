//Zadanie 1
//Stwórz licznik, który będzie zliczać w dół lub w górę (w zależności od stanu  
//przycisku). Zliczanie ma być wyświetlane na wyświetlaczu 7-segmentowym.

//Funkcjonalność:  
//Przy naciśniętym przycisku (utrzymując) - licznik zlicza w górę  
//Przy opuszczonym przycisku (kiedy odpuszczamy lub nic nie robimy) - licznik zlicza w dół  

unsigned const int A = 13;
unsigned const int B = 12;
unsigned const int C = 11;
unsigned const int D = 10;
unsigned const int E = 9;
unsigned const int F = 8;
unsigned const int G = 7;
unsigned const int H = 6;

int stanPrzycisku = 2;  //pin 2
const int DELAY = 500;

//Stworzyłam dodatkową klasę dla wygodnej pracy z metodami
class Liczba {
public:
    void zero(void) {
        digitalWrite(A, LOW);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        digitalWrite(H, LOW);
    }
    void one(void) {
        digitalWrite(A, LOW);
        digitalWrite(B, LOW);
        digitalWrite(C, LOW);
        digitalWrite(D, HIGH);
        digitalWrite(E, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, HIGH);
        digitalWrite(H, LOW);
    }
    void two(void) {
        digitalWrite(A, HIGH);
        digitalWrite(B, LOW);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, LOW);
        digitalWrite(H, LOW);
    }
    void three(void) {
        digitalWrite(A, HIGH);
        digitalWrite(B, LOW);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, LOW);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        digitalWrite(H, LOW);
    }
    void four(void) {
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, LOW);
        digitalWrite(D, HIGH);
        digitalWrite(E, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, HIGH);
        digitalWrite(H, LOW);
    }
    void five(void) {
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, LOW);
        digitalWrite(E, LOW);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        digitalWrite(H, LOW);
    }
    void six(void) {
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, LOW);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        digitalWrite(H, LOW);
    }
    void seven(void) {
        digitalWrite(A, LOW);
        digitalWrite(B, LOW);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, HIGH);
        digitalWrite(H, LOW);
    }
    void eight(void) {
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        digitalWrite(H, LOW);
    }
    void nine(void) {
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, LOW);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        digitalWrite(H, LOW);
    }
};

//tworzę nowy obiekt tej klasy Liczba 
Liczba liczby;


void setup(void)
{
    Serial.begin(9600);
    pinMode(stanPrzycisku, INPUT);
    
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(D, OUTPUT);
    pinMode(E, OUTPUT);
    pinMode(F, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(H, OUTPUT);
}

void loop(void)
{
    int buttonState = digitalRead(stanPrzycisku);
    
    if (buttonState == HIGH) {
        Serial.println("Przycisk +");
        // od 0 do 9
        for (int i = 0; i < 10; ++i) {
            wyswietlLiczbe(i);
            delay(DELAY);
            //sprawdzam, czy przycisl nie był czasem odpuszczony
            if (digitalRead(stanPrzycisku) != HIGH) break;
        }
    } 
    else if (buttonState == LOW) {
        Serial.println("Przycisk -");
        // od 9 do 0
        for (int i = 9; i >= 0; --i) {
            wyswietlLiczbe(i);
            delay(DELAY);
            //sprawdzam, czy przycisl nie był czasem naciśnięty
            if (digitalRead(stanPrzycisku) != LOW) break;
        }
    }
}


//Dodatkowa metowa dla wyświetlania każdej liczby
void wyswietlLiczbe(int liczba) {
    //Można było zrobić przez 'if else' - ale nie jest wygodne
    // dlatego stosuję 'switch'

    switch (liczba) {
        case 0: 
        liczby.zero(); 
        break;
        case 1: 
        liczby.one();
        break;
        case 2:
         liczby.two();
          break;
        case 3: 
        liczby.three(); 
        break;
        case 4: 
        liczby.four(); 
        break;
        case 5: 
        liczby.five(); 
        break;
        case 6: 
        liczby.six(); 
        break;
        case 7:
         liczby.seven();
          break;
        case 8: 
        liczby.eight();
         break;
        case 9:
         liczby.nine(); 
         break;
    }
}