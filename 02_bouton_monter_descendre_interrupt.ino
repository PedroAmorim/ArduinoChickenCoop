// attachInterrupt ne fonctione qu'avec les pin 2 et 3 sur les carte Uno
const int btn_up=2; // Bouton haut
const int btn_down=3; // Bouton bas

void setup() {
    Serial.begin(9600); // Ouverture du port série et debit de communication fixé à 9600 bauds
    Serial.println("--- Setup ---");

    pinMode(btn_up, INPUT);
    pinMode(btn_down, INPUT);

    // https://eskimon.fr/tuto-arduino-204-un-simple-bouton#les-interruptions-mat%C3%A9rielles
    attachInterrupt(digitalPinToInterrupt(btn_up), openDoor, FALLING);
    attachInterrupt(digitalPinToInterrupt(btn_down), closeDoor, FALLING);
}

void loop() {
    delay(1000);
}

// Séquence d'alimentation du moteur pour fermer la porte
void closeDoor(){
    Serial.println("Fermeture porte"); /// Affichage sur le moniteur série du texte

    Serial.println("Porte Fermée"); // Affichage sur le moniteur série
}

// Séquence d'alimentation du moteur pour ouvrir la porte
void openDoor(){
    Serial.println("Ouvrir porte"); /// Affichage sur le moniteur série du texte

    Serial.println("Porte Ouverte"); // Affichage sur le moniteur série
}