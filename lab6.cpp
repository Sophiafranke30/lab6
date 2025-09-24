//Lab 6 | Sophia Franke (23030)
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <stdint.h>

//Definición de pines y variables globales
#define pot1 15
#define pot2 35

#define LedR 14
#define LedG 27
#define LedB 12

int Vpot1=0;
int Vpot2=0;

int colorR=0;
int colorG=0;
int colorB=0;
int contador=0;

//Pines del LCD (RS, E, D4, D5, D6, D7) ; No acepta a 8 bits por lo que se conecta a 4 bits
LiquidCrystal lcd(26, 25, 33, 32, 22, 23); // RS, E, D4, D5, D6, D7
void actualizarLCD();


void setup() {
//Inicialización del LCD y de la comunicación serial
  lcd.begin(16,2);
 
  Serial.begin(115200);

  // Configuración de los leds RGB como salida y su inicialización en PWM

  ledcSetup(0, 5000, 8);
  ledcAttachPin(LedR, 0);

  ledcSetup(1, 5000, 8);
  ledcAttachPin(LedG, 1);

  ledcSetup(2, 5000, 8);
  ledcAttachPin(LedB, 2);
}

void loop() {
//Lectura amalógica de los potenciómetros y luego realizar el mapeo de 0-4095 a 0-255 para los colores
  Vpot1 =analogRead(pot1);
  Vpot2 =analogRead(pot2);
  colorR = map(Vpot1,0,4095,0,255);
  colorG = map(Vpot2,0,4095,0,255);

// Controlar el valor del contador con '+' y '-' en el monitor serial
  if (Serial.available()) {
    char c = Serial.read();
    if (c == '+') {
      contador++;
      if (contador > 255) {
        contador = 255; // Limitar el valor máximo a 255
      }
    } else if (c == '-') {
      contador--;
      if (contador < 0) {
        contador = 0; // Limitar el valor mínimo a 0
      }
    }
  }
  // Mostrar los valores en el monitor serial. Delay para que se pueda leer.
  Serial.print("Rojo: ");
  Serial.println(colorR);
  Serial.print(" Verde: ");
  Serial.println(colorG);
  Serial.print(" Azul: ");
  Serial.println(contador);
  delay(800);

  // Actualizar los valores en el LCD utilizando la función
  actualizarLCD();
  delay(500);

  // Controlar los LEDs RGB con PWM usando ledcWrite
  ledcWrite(0, colorR);
  ledcWrite(1, colorG);
  ledcWrite(2, contador);
}

// Función para actualizar los valores en el LCD tomando los valores de las variables globales
void actualizarLCD() {
  lcd.clear();           
  lcd.setCursor(0, 0);
  lcd.print("R:");
  lcd.setCursor(0, 1);
  lcd.print(colorR);
  lcd.setCursor(6, 0);
  lcd.print("G:");
  lcd.setCursor(6, 1);
  lcd.print(colorG);
  lcd.setCursor(12, 0);
  lcd.print("B:");
  lcd.setCursor(12, 1);
  lcd.print(contador);
}


