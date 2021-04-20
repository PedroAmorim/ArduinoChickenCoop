int commande_haut=2; // Bouton haut
int commande_bas=3; // Bouton bas

int etat_bp_h;
int etat_bp_b;

void setup() {
    Serial.begin(9600); // Ouverture du port série et debit de communication fixé à 9600 bauds

    Serial.println("--- Setup ---");

    pinMode(commande_haut, INPUT_PULLUP); // Inverse de la lecture sur entrée BP haut
    pinMode(commande_bas, INPUT_PULLUP); // Inverse de la lecture sur entrée BP bas
}

void loop() {

    // Lecture de l'état des boutons
    etat_bp_h=!digitalRead(commande_haut); // Inverse de la lecture sur entrée BP haut
    etat_bp_b=!digitalRead(commande_bas); // Inverse de la lecture sur entrée BP bas

    if(etat_bp_h) // Appui sur BP haut mais pas sur le bas
    {
        Fermer_porte(); // Lancer la fonction fermeture de la porte du poulailler
    }

    if(etat_bp_b) // Appui sur BP bas mais pas sur le haut
    {
        Ouvrir_porte(); // Lancer la fonction ouverture de la porte du poulailler
    }

    delay(1000);
}

// Séquence d'alimentation du moteur pour fermer la porte
void Fermer_porte(){
    Serial.println("Fermeture porte"); /// Affichage sur le moniteur série du texte

    Serial.println("Porte Fermée"); // Affichage sur le moniteur série
}

// Séquence d'alimentation du moteur pour ouvrir la porte
void Ouvrir_porte(){
    Serial.println("Ouvrir porte"); /// Affichage sur le moniteur série du texte

    Serial.println("Porte Ouverte"); // Affichage sur le moniteur série
}