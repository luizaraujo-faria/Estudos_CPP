#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define SS_PIN 5
#define RST_PIN 4

#define LED_AZUL 2
#define LED_AMARELO 15

MFRC522 rfid(SS_PIN, RST_PIN);

// UID AUTORIZADO
String uidAutorizado = "EF FB B9 A3"; // exemplo

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();


  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);

  SPI.begin(18, 19, 23, 5);
  rfid.PCD_Init();

  lcd.setCursor(0, 0);
  lcd.print("Sistema RFID");
  lcd.setCursor(0, 1);
  lcd.print("Aproxime cartao");
}

void loop() {

  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  String uid = "";

  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
    uid += " ";
  }

  uidAutorizado.trim(); 
  uid.toUpperCase();
  uid.trim();

  Serial.println(uid);

  lcd.clear();

  if (uid == uidAutorizado) {
    // ✅ ACESSO LIBERADO
    lcd.setCursor(0, 0);
    lcd.print("Acesso liberado");

    digitalWrite(LED_AZUL, HIGH);

    delay(2000);

  } 
  else {
    // ❌ ACESSO NEGADO
    lcd.setCursor(0, 0);
    lcd.print("Acesso negado");

    digitalWrite(LED_AMARELO, HIGH);

    delay(2000);
  }

  // Desliga tudo
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_AMARELO, LOW);

  rfid.PICC_HaltA();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aproxime cartao");
}
