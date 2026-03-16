#include <IRremote.hpp>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 4, A0, A1, A2, A3);

int brightness = 200;   // default brightness
bool powerOn = true;
const int RECV_PIN = 2;

// RGB LED pins
const int R_PIN = 3;
const int G_PIN = 5;
const int B_PIN = 6;

// Single LEDs
const int RED_LED = 8;
const int GREEN_LED = 9;
const int BLUE_LED = 10;
const int YELLOW_LED = 11;

// Mode variable
int mode = 0;
unsigned long previousMillis = 0;
const long partyInterval = 100;  // speed of party mode
const long interval = 20;   // master rhythm speed
int hue = 0;                // shared color position

byte M_char[8] = {
  B10001,
  B11011,
  B10101,
  B10001,
  B10001,
  B10001,
  B10001,
  B00000
};

byte A_char[8] = {
  B01110,
  B10001,
  B10001,
  B11111,
  B10001,
  B10001,
  B10001,
  B00000
};

byte CAT_char[8] = {
  B10001,
  B10101,
  B10001,
  B11111,
  B10001,
  B10001,
  B01110,
  B00000
};
byte HEART_char[8] = {
  B01101,
  B11111,
  B11111,
  B01111,
  B00110,
  B00110,
  B00110,
  B00000
};



void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);

  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  lcd.begin(16, 2);
  lcd.createChar(0, M_char);
  lcd.createChar(1, A_char);
  lcd.createChar(2, CAT_char);
  lcd.createChar(3, HEART_char);
  lcd.clear();

  // Row 0: MA + cat
  lcd.setCursor(0,0);
  lcd.write(byte(0)); // M
  lcd.write(byte(1)); // A
  lcd.print("  ");
  lcd.write(byte(3)); // Heart
  lcd.print(" ");
  lcd.write(byte(2)); // Cat

  // Row 1: Text
  lcd.setCursor(0,1);
  lcd.print("Minh Anh's Lamp");

  // delay(1000);
  // lcd.clear();

}
void showMode(const char* name) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mode:");
  lcd.setCursor(0, 1);
  lcd.print(name);
}

void setColor(int r, int g, int b) {
  analogWrite(R_PIN, r);
  analogWrite(G_PIN, g);
  analogWrite(B_PIN, b);
}

void setSingleLEDs(bool r, bool g, bool b, bool y) {
  digitalWrite(RED_LED, r);
  digitalWrite(GREEN_LED, g);
  digitalWrite(BLUE_LED, b);
  digitalWrite(YELLOW_LED, y);
}

void loop() {
  if (IrReceiver.decode()) {
    uint8_t cmd = IrReceiver.decodedIRData.command;
    Serial.print("Command: ");
    Serial.println(cmd, HEX);

  if (cmd == 0x0C) { mode = 1; showMode("Red"); }
  if (cmd == 0x18) { mode = 2; showMode("Green"); }
  if (cmd == 0x5E) { mode = 3; showMode("Blue"); }
  if (cmd == 0x08) { mode = 4; showMode("Yellow"); }
  if (cmd == 0x1C) { mode = 5; showMode("Rainbow"); }
  if (cmd == 0x5A) { mode = 6; showMode("Random"); }
  if (cmd == 0x52) { mode = 7; showMode("Breathe"); }
  if (cmd == 0x4A) { mode = 8; showMode("Party"); }
  if (cmd == 0x42) { mode = 9; showMode("Calm"); }

    IrReceiver.resume();
  }

  switch (mode) {
    case 1: // Red
      setColor(255, 0, 0);
      setSingleLEDs(1,0,0,0);
      break;

    case 2: // Green
      setColor(0, 255, 0);
      setSingleLEDs(0,1,0,0);
      break;

    case 3: // Blue
      setColor(0, 0, 255);
      setSingleLEDs(0,0,1,0);
      break;

    case 4: // Yellow
      setColor(255, 255, 0);
      setSingleLEDs(0,0,0,1);
      break;

    case 5: { // Rainbow fade
      static int x = 0;
      x = (x + 1) % 768;

      int r, g, b;
      if (x < 256) { r = 255 - x; g = x; b = 0; }
      else if (x < 512) { r = 0; g = 511 - x; b = x - 256; }
      else { r = x - 512; g = 0; b = 767 - x; }

      setColor(r, g, b);

      // --- NEW: sync single LEDs to rainbow brightness ---
      int brightness = max(r, max(g, b));  // 0–255

      analogWrite(RED_LED, brightness);
      analogWrite(GREEN_LED, brightness);
      analogWrite(BLUE_LED, brightness);

      // Yellow LED (non-PWM)
      digitalWrite(YELLOW_LED, brightness > 120);

      delay(5);
      break;
    }


    case 6: // Random - Sync With RGB
    {
      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis >= 150) {
        previousMillis = currentMillis;

        int r = random(256);
        int g = random(256);
        int b = random(256);

        setColor(r, g, b);

        // Match single LEDs to RGB intensity
        digitalWrite(RED_LED, r > 120);
        digitalWrite(GREEN_LED, g > 120);
        digitalWrite(BLUE_LED, b > 120);

        // Yellow = combination of red + green
        digitalWrite(YELLOW_LED, (r > 120 && g > 120));
      }

      break;
    }

    case 7: // Breathe - All LEDs Sync
    {
      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        static int brightness = 0;
        static int direction = 5;

        brightness += direction;

        if (brightness <= 0 || brightness >= 255) {
          direction = -direction;
        }

        setColor(brightness, brightness, brightness);

        // Single LEDs follow same rhythm
        digitalWrite(RED_LED, brightness > 150);
        digitalWrite(GREEN_LED, brightness > 150);
        digitalWrite(BLUE_LED, brightness > 150);
        digitalWrite(YELLOW_LED, brightness > 150);
      }

      break;
    }
    case 8: // Party Mode (Non-Blocking)
    {
      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis >= partyInterval) {
        previousMillis = currentMillis;

        // Random RGB color
        setColor(random(255), random(255), random(255));

        // Random single LEDs
        digitalWrite(RED_LED, random(2));
        digitalWrite(GREEN_LED, random(2));
        digitalWrite(BLUE_LED, random(2));
        digitalWrite(YELLOW_LED, random(2));
      }

      break;
    }
    case 9: // Calm - Soft Synced Version
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 20) {  // slow rhythm
      previousMillis = currentMillis;

      static int x = 0;
      x = (x + 1) % 768;

      int r, g, b;

      if (x < 256) {
        r = 255 - x;
        g = x;
        b = 0;
      }
      else if (x < 512) {
        r = 0;
        g = 511 - x;
        b = x - 256;
      }
      else {
        r = x - 512;
        g = 0;
        b = 767 - x;
      }

      r = r / 3;
      g = g / 3;
      b = b / 3;

      setColor(r, g, b);

      digitalWrite(RED_LED, r > 40);
      digitalWrite(GREEN_LED, g > 40);
      digitalWrite(BLUE_LED, b > 40);
      digitalWrite(YELLOW_LED, (r > 40 && g > 40));
    }

    break;
  }

  }

}
