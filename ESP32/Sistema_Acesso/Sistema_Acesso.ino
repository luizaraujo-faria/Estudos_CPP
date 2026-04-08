#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// LEDs
#define LED_AZUL 2
#define LED_AMARELO 15

HardwareSerial rfidSerial(2);

// UID autorizado
String uidAutorizado = "6000D8FEACEA";

String tag = "";
String ultimaTag = "";

unsigned long ultimoTempoLeitura = 0;
const int intervaloLeitura = 3000;

// 🔍 Função para validar UID (11 dígitos numéricos)
bool uidValido(String uid) {
  uid.trim();
  if (uid.length() != 11) return false;

  return true;
}

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);

  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_AMARELO, LOW);

  rfidSerial.begin(9600, SERIAL_8N1, 16, 17);

  lcd.setCursor(0, 0);
  lcd.print("Sistema RFID");
  lcd.setCursor(0, 1);
  lcd.print("Aproxime cartao");

  Serial.println("=== SISTEMA RFID 125kHz ===");
}

void loop() {

  while (rfidSerial.available()) {
    char c = rfidSerial.read();

    if (c == 0x02) {
      tag = "";
    }
    else if (c == 0x03) {
      verificarLeitura(tag);
    }
    else {
      tag += c;
    }
  }
}

void verificarLeitura(String uid) {

  unsigned long agora = millis();

  if (uid == ultimaTag && (agora - ultimoTempoLeitura < intervaloLeitura)) {
    return;
  }

  ultimaTag = uid;
  ultimoTempoLeitura = agora;

  processarTag(uid);
}

void processarTag(String uid) {

  Serial.println("\nCartao detectado!");
  Serial.print("RAW: ");
  Serial.println(uid);

  // 🔥 LIMPEZA DO UID (remove lixo)
  String uidLimpo = "";

  for (int i = 0; i < uid.length(); i++) {
    char c = uid[i];

    // aceita apenas HEX (0-9 A-F)
    if (isDigit(c) || (c >= 'A' && c <= 'F')) {
      uidLimpo += c;
    }
  }

  // 🔥 corta para tamanho máximo esperado (12)
  if (uidLimpo.length() >= 12) {
    uidLimpo = uidLimpo.substring(0, 12);
  }

  Serial.print("UID LIMPO: ");
  Serial.println(uidLimpo);

  lcd.clear();

  // ❌ valida tamanho correto
  if (uidLimpo.length() != 12) {

    Serial.println("FALHA NA LEITURA");

    lcd.setCursor(0, 0);
    lcd.print("Falha leitura");

    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_AZUL, LOW);

    delay(2000);

    digitalWrite(LED_AMARELO, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Aproxime cartao");

    return;
  }

  // ✅ COMPARAÇÃO CORRETA
  if (uidLimpo == uidAutorizado) {

    Serial.println("ACESSO LIBERADO");

    lcd.setCursor(0, 0);
    lcd.print("Acesso liberado");
    lcd.setCursor(0, 1);
    lcd.print(uidLimpo);

    digitalWrite(LED_AZUL, HIGH);
    digitalWrite(LED_AMARELO, LOW);

  } else {

    Serial.println("ACESSO NEGADO");

    lcd.setCursor(0, 0);
    lcd.print("Acesso negado");
    lcd.setCursor(0, 1);
    lcd.print(uidLimpo);

    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_AZUL, LOW);
  }

  delay(2000);

  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_AMARELO, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aproxime cartao");

  Serial.println("Aguardando...");
}