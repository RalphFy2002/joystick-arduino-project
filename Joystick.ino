#include <Arduino.h>


// Broches pour le joystick analogique
const int VRX_PIN = 34;  // Broche GPIO34 pour l'axe X
const int VRY_PIN = 35;  // Broche GPIO35 pour l'axe Y
const int SW_PIN = 32;   // Broche GPIO32 pour le bouton (optionnel)

// Variables pour stocker les valeurs brutes
int xValue = 0;
int yValue = 0;
int buttonState = 0;

// Variables pour les résultats traités
float speed = 0;
float direction = 0; // en degrés (0° = devant, 90° = droite)

// Seuil pour ignorer les petites variations autour du centre
const int DEADZONE = 50;

void setup() {
  Serial.begin(115200);
  
  pinMode(VRX_PIN, INPUT);
  pinMode(VRY_PIN, INPUT);
  pinMode(SW_PIN, INPUT_PULLUP); // Bouton avec résistance pull-up interne
}

void loop() {
  // Lecture des valeurs brutes
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  buttonState = digitalRead(SW_PIN);
  
  // Conversion des valeurs (0-4095) en (-512 à 512) pour ESP32
  xValue = map(xValue, 0, 4095, -512, 512);
  yValue = map(yValue, 0, 4095, -512, 512);
  
  // Application de la zone morte
  if(abs(xValue) < DEADZONE) xValue = 0;
  if(abs(yValue) < DEADZONE) yValue = 0;
  
  // Calcul de la vitesse (0 à 100%)
  speed = sqrt(sq(xValue) + sq(yValue)) / 5.12; // 512 = 100%
  speed = constrain(speed, 0, 100);
  
  // Calcul de la direction (en degrés)
  if(speed > 0) {
    direction = atan2(-yValue, xValue) * 180 / PI;
    direction = fmod((direction + 360), 360); // Normalisation (0-360)
  } else {
    direction = 0;
  }
  
  // Affichage des résultats
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.print(yValue);
  Serial.print(" | Bouton: ");
  Serial.print(buttonState);
  Serial.print(" | Vitesse: ");
  Serial.print(speed);
  Serial.print("% | Direction: ");
  Serial.print(direction);
  Serial.println("°");
  
  delay(100); // Petit délai pour la stabilité
}