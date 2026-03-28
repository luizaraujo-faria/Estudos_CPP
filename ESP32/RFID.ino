#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

// ===== LCD =====
LiquidCrystal_I2C lcd(0x27, 20, 4);

// ===== RFID =====
#define SS_PIN 5   // SDA (SS)
#define RST_PIN 4  // PINO RST 4

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);

  // ===== I2C (LCD) =====
  Wire.begin(21, 22); // SDA = 21 | SCL = 22

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");

  // ===== SPI (RFID) =====
  SPI.begin(18, 19, 23, 5); 
  // PINOS SCK = 18, MISO = 19, MOSI = 23, SS = 5

  rfid.PCD_Init(); // INICIALIZA O RFID

  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aproxime o cartao");
}

void loop() {

  // ===== VERIFICA SE TERM CARTÃO =====
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // ===== TENTA LER O CARTÃO =====
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // ===== CARTÃO DETECTADO =====
  Serial.println("Cartao detectado!");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cartao detectado");

  // ===== LÊ UID DO CARTÃO =====
  String uid = "";

  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
    uid += " ";
  }

  uid.toUpperCase(); // PASSA PARA CAIXA ALTA

  // ===== Serial =====
  Serial.print("UID: ");
  Serial.println(uid);

  // ===== LCD =====
  lcd.setCursor(0, 1);
  lcd.print("UID:");

  lcd.setCursor(0, 2);
  lcd.print(uid);

  delay(2000);

  // ===== FINALIZA LEITURA =====
  rfid.PICC_HaltA();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aproxime o cartao");
}
