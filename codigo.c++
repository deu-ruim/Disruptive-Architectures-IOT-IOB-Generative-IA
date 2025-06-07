#include "DHT.h"
#include <WiFi.h>
#include "ThingSpeak.h"

#define DHTPIN 33
#define DHTTYPE DHT22
#define BUTTON_PIN 18

#define LED_SENSOR_ON 25
#define LED_SENSOR_OFF 26
#define LED_ENVIANDO 27

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

const char* ssid = "Wokwi-GUEST";
const char* pass = "";

unsigned long myChannelNumber = 2983597;
const char* myWriteAPIKey = "WCU18Y7Q4O90EPF6";

bool sensorLigado = false;
bool ultimoEstadoBotao = HIGH;

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  ultimoEstadoBotao = digitalRead(BUTTON_PIN); 

  pinMode(LED_SENSOR_ON, OUTPUT);
  pinMode(LED_SENSOR_OFF, OUTPUT);
  pinMode(LED_ENVIANDO, OUTPUT);

  digitalWrite(LED_SENSOR_ON, LOW);
  digitalWrite(LED_SENSOR_OFF, HIGH);
  digitalWrite(LED_ENVIANDO, LOW);

  WiFi.begin(ssid, pass);
  Serial.print("Conectando WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");

  ThingSpeak.begin(client);
}

void loop() {
  bool estadoAtualBotao = digitalRead(BUTTON_PIN);
  if (estadoAtualBotao == LOW && ultimoEstadoBotao == HIGH) {
    sensorLigado = !sensorLigado; 
    Serial.println(sensorLigado ? "Sensor LIGADO" : "Sensor DESLIGADO");


    digitalWrite(LED_SENSOR_ON, sensorLigado ? HIGH : LOW);
    digitalWrite(LED_SENSOR_OFF, sensorLigado ? LOW : HIGH);

    delay(200);
  }
  ultimoEstadoBotao = estadoAtualBotao;

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado. Tentando reconectar...");
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nWiFi reconectado!");
  }

  if (sensorLigado) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float hic = dht.computeHeatIndex(t, h, false);

    if (isnan(h) || isnan(t)) {
      Serial.println("Erro ao ler do DHT!");
      return;
    }

    Serial.printf("Temp: %.2f°C | Umid: %.2f%% | HI: %.2f°C\n", t, h, hic);

    ThingSpeak.setField(1, t);  
    ThingSpeak.setField(2, h);   
    ThingSpeak.setField(3, 1);      
    ThingSpeak.setField(4, hic);    
    ThingSpeak.setStatus("Sensor ativo");

    digitalWrite(LED_ENVIANDO, HIGH);
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    digitalWrite(LED_ENVIANDO, LOW);

    if (x == 200) {
      Serial.println("Dados enviados!");
    } else {
      Serial.println("Erro HTTP: " + String(x));
    }
  } else {
    Serial.println("Sensor desligado. Nenhum dado enviado.");
    ThingSpeak.setField(3, 0); 
    ThingSpeak.setStatus("Sensor desligado");
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  }

  delay(20000); // 20 segundos 
}
