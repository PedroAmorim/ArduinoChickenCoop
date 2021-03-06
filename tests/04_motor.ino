// --- Init rtc object ---
// Lib https://github.com/Makuna/Rtc/
#include <ThreeWire.h>
#include <RtcDS1302.h>

ThreeWire myWire(7, 8, 6); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

// --- Init manual mode objects ---

// attachInterrupt ne fonctione qu'avec les pin 2 et 3 sur les carte Uno
const int btn_up = 2;   // Bouton haut
const int btn_down = 3; // Bouton bas
const int limit_switch_up = 9;    // Capteur fin de course haut brancher sur broche NC
const int limit_switch_down = 12; // Capteur fin de course bas brancher sur broche NC
boolean lsup = false;             // Déclaration variable Fin de Course Haut
boolean lsdown = false;           // Déclaration variable Fin de Course Bas

const int auto_mode = 4; // Interrupteur mode auto
int auto_mode_state = false;

// --- Motor objects ---

const int motor_in1 = 10;
const int motor_in2 = 11;

void setup()
{

    Serial.begin(9600); // Ouverture du port série et debit de communication fixé à 9600 bauds
    Serial.println("--- Setup ---");
    Serial.print("Compiled: ");
    Serial.print(__DATE__);
    Serial.print(" ");
    Serial.println(__TIME__);

    // --- Init rtc module ---
    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    RtcDateTime now = Rtc.GetDateTime();

    // Update RTC time if needed
    if (now < compiled || !Rtc.IsDateTimeValid())
    {
        Serial.println("RTC: Updating DateTime");
        Rtc.SetDateTime(compiled);
    }

    Serial.print("RTC time: ");
    printDateTime(now);
    Serial.println();

    // --- Init manual mode ---

    pinMode(btn_up, INPUT_PULLUP);
    pinMode(btn_down, INPUT_PULLUP);
    pinMode(limit_switch_up, INPUT_PULLUP);
    pinMode(limit_switch_down, INPUT_PULLUP);
    pinMode(auto_mode, INPUT_PULLUP);
    auto_mode_state = digitalRead(auto_mode);

    // https://eskimon.fr/tuto-arduino-204-un-simple-bouton#les-interruptions-mat%C3%A9rielles
    attachInterrupt(digitalPinToInterrupt(btn_up), buttonUpAction, FALLING);
    attachInterrupt(digitalPinToInterrupt(btn_down), buttonDownAction, FALLING);

    // --- Init motor ---
    pinMode(motor_in1, OUTPUT);
    pinMode(motor_in2, OUTPUT);
    digitalWrite(motor_in1, LOW);
    digitalWrite(motor_in2, LOW);

    // --- Init door
    lsup = digitalRead(limit_switch_up);
    lsdown = digitalRead(limit_switch_down);

    if (lsup == false && lsdown == false) {
      Serial.println("Initialisation de la porte.");
      openDoor();
      closeDoor();
    }
}

void loop()
{
    Serial.println("Loop ---"); // Affichage sur le moniteur série

    // RTC module : https://github.com/Makuna/Rtc/wiki/RtcDateTime-object
    RtcDateTime now = Rtc.GetDateTime();
    Serial.print("Heure: ");
    Serial.println(now.Hour());
    Serial.print("Minutes: ");
    Serial.println(now.Minute());

    delay(2000);

}

// Action des boutons Up et Down

void buttonUpAction()
{
    if (ManualModeActive() == true)
    {
        openDoor();
    }
    else
    {
        Serial.println("Mode auto activé, les boutons sont désactivé.");
    }
}

void buttonDownAction()
{
    if (ManualModeActive() == true)
    {
        closeDoor();
    }
    else
    {
        Serial.println("Mode auto activé, les boutons sont désactivé.");
    }
}

bool ManualModeActive()
{

    auto_mode_state = digitalRead(auto_mode);
    Serial.print("auto_mode_state :");
    Serial.println(auto_mode_state);

    if (auto_mode_state == false)
    {
      Serial.println("Mode: Manual"); // Affichage sur le moniteur série
      return true;
    } else {
      Serial.println("Mode: Auto");
      return false;
    }

}

// Séquence d'alimentation du moteur pour fermer la porte
void closeDoor()
{
    Serial.println("Fermeture porte"); /// Affichage sur le moniteur série du texte

    lsdown = digitalRead(limit_switch_down);

    while (lsdown == false)
    {
        digitalWrite(motor_in1, HIGH);
        digitalWrite(motor_in2, LOW);
        lsdown = digitalRead(limit_switch_down);
    }

    digitalWrite(motor_in1, LOW);
    digitalWrite(motor_in2, LOW);

    Serial.println("Porte Fermée"); // Affichage sur le moniteur série
}

// Séquence d'alimentation du moteur pour ouvrir la porte
void openDoor()
{
    Serial.println("Ouvrir porte"); /// Affichage sur le moniteur série du texte

    lsup = digitalRead(limit_switch_up);

    while (lsup == false)
    {
        digitalWrite(motor_in1, LOW);
        digitalWrite(motor_in2, HIGH);
        lsup = digitalRead(limit_switch_up);
    }

    digitalWrite(motor_in1, LOW);
    digitalWrite(motor_in2, LOW);

    Serial.println("Porte Ouverte"); // Affichage sur le moniteur série
}

// RTC Module

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime &dt)
{
    char datestring[20];

    snprintf_P(datestring,
               countof(datestring),
               PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
               dt.Day(),
               dt.Month(),
               dt.Year(),
               dt.Hour(),
               dt.Minute(),
               dt.Second());
    Serial.print(datestring);
}