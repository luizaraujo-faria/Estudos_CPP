int led = 2;  // RECEBE PINO DO LED
char comando; // RECEBE O COMANDO DO TECLADO

void setup() {
  Serial.begin(115200);

  // CANAL, FREQUENCIA, RESOLUÇÃO
  ledcAttach(led, 5000, 8);

  Serial.println("=== CONTROLE DO LED ===");
  Serial.println("1 - Ligar LED");
  Serial.println("0 - Desligar LED");
  Serial.println("f - Fade");
}

void loop() {

  if (Serial.available()) {
    comando = Serial.read();

    if (comando == '1') {
      ledcWrite(led, 255);
      Serial.println("LED LIGADO");
    }

    if (comando == '0') {
      ledcWrite(led, 0);
      Serial.println("LED DESLIGADO");
    }

    if (comando == 'f') {
      Serial.println("Modo FADE");

      while (true) {

        for (int i = 0; i <= 255; i++) {
          ledcWrite(led, i);
          delay(10);
        }

        for (int i = 255; i >= 0; i--) {
          ledcWrite(led, i);
          delay(10);
        }

        if (Serial.available()) {
          char c = Serial.read();
          if (c == 's') {
            break;
          }
        }
      }
    }
  }
}
