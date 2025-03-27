//Zadanie 3
// Napisz program, w którym dioda świeci jasno, jeśli wartość potencjometru
// przekroczy 700, świeci słabo, gdy wartość jest między 300 a 700, i gaśnie, gdy
// wartość spadnie poniżej 300.

//Funkcjonalność:
//Program odczytuje wartość potencjometru
//Program zmienia jasność diody w zależności od wartości potencjometru

int potencjometr = A0;    // Pin - potencjometru
int led = 9;     // Pin diody LED

void setup() {
  // Ustawienie pinu diody jako wyjście
  pinMode(led, OUTPUT);

  //inicjalizacja komunikacji szeregowej 9600 buts per second
  Serial.begin(9600);
}

void loop() {
  // Odczytanie:
  int pot_value = analogRead(potencjometr);

  // Wyświetlenie wartości w monitorze szeregowym (opcjonalnie)
  //Serial.println(pot_value);

  if (pot_value > 700) {
    analogWrite(led, 255);
  } else if (pot_value >= 300 && pot_value <= 700) {
    analogWrite(led, 127); 
  } else {
    analogWrite(led, 0); 
  }

  delay(30);
}