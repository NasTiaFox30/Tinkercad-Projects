//Zadanie 1
//Napisz program, który zlicza liczbę naciśnięć przycisku i wyświetla wynik w
// monitorze szeregowym.

//Funkcjonalność:
//Program zlicza liczbę naciśnięć przycisku
//Program wyświetla wynik w monitorze szeregowym

//deklaracja
int pushButton = 2;
int iloscNacisniec = 0;
bool pressedButton = false;

void setup()
{
  //inicjalizacja komunikacji szeregowej 9600 buts per second
  Serial.begin(9600);
  
  //ustawienie pinu przycisku jako wejścia
  pinMode(pushButton, INPUT);

}

void loop()	
{
  //odczyt pinu
  int buttonState = digitalRead(pushButton);
  
  if (buttonState == HIGH && !pressedButton) {
    /*Serial.println("Button Pressed");*/
    	
  	iloscNacisniec++;
    pressedButton = true;
    Serial.print("Liczba naciśnięć: ");
    Serial.println(iloscNacisniec);
    delay(1);	//opóżnienie
	} 
  if (buttonState == LOW && pressedButton) {
    /*Serial.println("Button Released");*/
    pressedButton = false;
    delay(1);	//opóżnienie
	} 
}