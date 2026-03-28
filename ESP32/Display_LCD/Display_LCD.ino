#include <Wire.h> // ATIVA PROTOCOLO I2C DO ESP32 PARA COMUNICAÇÃO COM OUTROS DISPOSITIVOS
#include <LiquidCrystal_I2C.h>  // LIB QUE CONTROLA O DISPLAY INTERNAMENTE

// 0x27 -> ENDEREÇO DO I2C NO DISPLAY
// 16 -> COLUNAS
// 2 -> LINHAS
LiquidCrystal_I2C lcd(0x27, 16, 2); // OBJETO DO DISPLAY

String mensagem;

void setup() {
  Serial.begin(115200);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Display Ligado");

  lcd.setCursor(0, 1);
  lcd.print("Digite uma Mensagem");
}

void loop() {

    if(Serial.available()){
      
      mensagem = Serial.readString();
      mensagem.trim();

      if(!mensagem.isEmpty() && mensagem != "clear"){
        lcd.clear();
        
        // Linha 1
        lcd.setCursor(0, 0);
        lcd.print(mensagem.substring(0, 20)); // LIMITA EM 20 CARACTERES POR LINHA
        
        // Linha 2
        lcd.setCursor(0, 1);
        lcd.print(mensagem.substring(20, 40));
        
        // Linha 3
        lcd.setCursor(0, 2);
        lcd.print(mensagem.substring(40, 60));
        
        // Linha 4
        lcd.setCursor(0, 3);
        lcd.print(mensagem.substring(60, 80));
      }
      
      if(mensagem == "clear"){
        lcd.setCursor(0,0);
        lcd.clear();
      }
    }
}



/*

  PARA BUSCAR O ENDEREÇO DO DISPLAY

#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin();

  Serial.println("Procurando dispositivos I2C...");

  for (byte i = 1; i < 127; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("Encontrado: 0x");
      Serial.println(i, HEX);
    }
  }
}

void loop() {}
*/
