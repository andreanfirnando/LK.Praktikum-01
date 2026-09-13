#include <DHT.h>

const byte dhtPin = 13;
const byte ldrPin = 36;
const byte relayPin = 12;
const byte ledPin = 5;

#define DHTTYPE DHT22

DHT dht(dhtPin, DHTTYPE);

#define RELAY_ON HIGH
#define RELAY_OFF LOW

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(relayPin, RELAY_OFF);
  digitalWrite(ledPin, LOW);

  Serial.println("--- Sistem Otomasi Smart Warehouse Dimulai ---");
}

void loop() {
  delay(2000);

  float temp = dht.readTemperature();
  int ldrValue = analogRead(ldrPin);

  if (isnan(temp)) {
    Serial.println("Peringatan: Gagal membaca data dari sensor DHT!");
    return;
  }

  Serial.print("Suhu: ");
  Serial.print(temp);
  Serial.print(" °C | Intensitas LDR (ADC): ");
  Serial.println(ldrValue);

  if (temp > 34.0 || ldrValue < 300) {
    digitalWrite(relayPin, RELAY_ON);
    digitalWrite(ledPin, HIGH);
    Serial.println("Status: Peringatan: Aktuator Aktif! (Kondisi Buruk Terdeteksi)\n");
  } else {
    digitalWrite(relayPin, RELAY_OFF);
    digitalWrite(ledPin, LOW);
    Serial.println("Status: Kondisi Aman (Aktuator Nonaktif)\n");
  }
}