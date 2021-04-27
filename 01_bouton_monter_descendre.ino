// attachInterrupt ne fonctione qu'avec les pin 2 et 3 sur les carte Uno
const int btn_up = 2; // Bouton haut
const int btn_down = 3; // Bouton bas
const int auto_mode = 4; // Interrupteur mode auto
int auto_mode_state = HIGH;

void setup() {
    Serial.begin(9600); // Ouverture du port série et debit de communication fixé à 9600 bauds
    Serial.println("--- Setup ---");

    pinMode(btn_up, INPUT_PULLUP);
    pinMode(btn_down, INPUT_PULLUP);
    pinMode(auto_mode, INPUT);

    // On  lit l'état de l'interrupteur
    ManualModeActive();

    // https://eskimon.fr/tuto-arduino-204-un-simple-bouton#les-interruptions-mat%C3%A9rielles
    attachInterrupt(digitalPinToInterrupt(btn_up), openDoor, FALLING);
    attachInterrupt(digitalPinToInterrupt(btn_down), closeDoor, FALLING);
}

void loop() {
    delay(1000);
    Serial.println("Loop ---"); // Affichage sur le moniteur série

    if(ManualModeActive() == true) {
      Serial.println("Loop: mode Manual");
    } else {
      Serial.println("Loop: mode Auto");
    }
}

// Séquence d'alimentation du moteur pour fermer la porte
void closeDoor(){

  if(ManualModeActive() == true) {
    Serial.println("Fermeture porte"); /// Affichage sur le moniteur série du texte
    delay(2000);
    Serial.println("Porte Fermée"); // Affichage sur le moniteur série
  }
    // Serial.println("Mode auto activé, les boutons sont désactivé.");

}

// Séquence d'alimentation du moteur pour ouvrir la porte
void openDoor(){

  if(ManualModeActive() == true) {
    Serial.println("Ouvrir porte"); /// Affichage sur le moniteur série du texte
    delay(2000);
    Serial.println("Porte Ouverte"); // Affichage sur le moniteur série
  }
   // Serial.println("Mode auto activé, les boutons sont désactivé.");
}

bool ManualModeActive(){

  auto_mode_state = digitalRead(auto_mode);
  Serial.print("Mode: auto_mode_state :");
  Serial.println(auto_mode_state);

  if (auto_mode_state == LOW) {
    Serial.println("Mode: Manual"); // Affichage sur le moniteur série
    return true;
  } else {
    Serial.println("Mode: Auto");
    return false;
  }
}