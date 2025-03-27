//Zadanie 2
//Napisz program, który pozwala użytkownikowi zmieniać częstotliwość migania
//diody, wpisując wartość (w milisekundach) do monitora szeregowego.

//Funkcjonalność:
//Użytkownik wprowadza wartość (w milisekundach) do monitora szeregowego
//Wartość ta jest przypisywana do zmiennej 'czestotliwosc'
//Dioda migocze z zadaną częstotliwością

int led = 13;	//pin PWM
int brightness = 500;	//janość diody
int czestotliwosc = 1000;

int ostatniaczestotliwosc = czestotliwosc;


void setup()
{
  //inicjalizacja komunikacji szeregowej 9600 buts per second
  Serial.begin(9600);
  
  Serial.println("Wpisz nowa czestotliwosc (w milisekundach):");	
	
  //inicjalizacja pinu cyfrowego jako wyjścia
  pinMode(led, OUTPUT);
  //ustawienie jasności pinu 13
  analogWrite(led, brightness);
  
}

void loop()	//pętla wykonująca się w nieskończenie
{
  /*
  int nowaCzestotliwosc = Serial.parseInt();
  if(ostatniaczestotliwosc != nowaCzestotliwosc){
    Serial.println("Wprowadzona nowa eartosc");
    czestotliwosc = nowaCzestotliwosc;
  }
  */
  
  if (Serial.available() > 0) {
    // Odczytanie danych z monitora szeregowego
    int nowaCzestotliwosc = Serial.parseInt();

    // Sprawdzenie, czy wprowadzona wartość jest większa od 0
    if (nowaCzestotliwosc > 0) {
      czestotliwosc = nowaCzestotliwosc;
      Serial.print("Wprowadzona nowa eartosc - ");
      Serial.print(czestotliwosc);
      Serial.println(" ms");
    } else {
      Serial.println("Nieprawidlowa wartosc!!!");
    }

    // Wyczyszczenie bufora monitora szeregowego
    /*
    while (Serial.available() > 0) {
      Serial.read();
    }
    */
  }
  digitalWrite(led, HIGH);
  delay(czestotliwosc);
  digitalWrite(led, LOW);
  delay(czestotliwosc); 
}