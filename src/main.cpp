#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "secrets.h"
#include "Sensores/moduloRele.h"
#include "Sensores/sensorPh.h"
#include "Sensores/sensorTurbidez.h"
#include "Sensores/sensorUltrassom.h"

#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883

WiFiClient client;
PubSubClient mqtt(client);

bool bombaLigada = false;

void conectarWiFi() {
  Serial.print("Conectando ao WiFi");

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("WiFi conectado!");
}

void conectarMQTT() {
  while (!mqtt.connected()) {
    Serial.print("Conectando ao Adafruit IO via MQTT... ");

    if (mqtt.connect("ESP32_Bebedouro", IO_USERNAME, IO_KEY)) {
      Serial.println("conectado!");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(mqtt.state());
      Serial.println(" tentando de novo em 5s");
      delay(5000);
    }
  }
}

void publicarFeed(const char* feed, float valor) {
  char topic[80];
  char payload[20];

  sprintf(topic, "%s/feeds/%s", IO_USERNAME, feed);
  dtostrf(valor, 1, 2, payload);

  mqtt.publish(topic, payload);
}

void publicarFeedTexto(const char* feed, const char* texto) {
  char topic[80];

  sprintf(topic, "%s/feeds/%s", IO_USERNAME, feed);
  mqtt.publish(topic, texto);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  iniciarpH();
  iniciaRele();
  iniciarUltrassom();
  iniciarTurbidez();

  conectarWiFi();

  WiFi.setSleep(false);

  mqtt.setServer(AIO_SERVER, AIO_SERVERPORT);
  conectarMQTT();
}

void loop() {
  if (!mqtt.connected()) {
    conectarMQTT();
  }

  mqtt.loop();

  float distancia = lerUltrassom();

  if (distancia < 0) {
    Serial.println("Leitura invalida do ultrassom");
    delay(1000);
    return;
  }

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  if (!bombaLigada && distancia >= 55.0) {
    publicarFeed("distancia", distancia);

    ligarRele();
    bombaLigada = true;

    publicarFeedTexto("bomba", "ON");

    Serial.println("Bomba ligada.");

    delay(10000);
    return;
  }

  if (bombaLigada && distancia <= 35.0) {
    desligarRele();
    bombaLigada = false;

    publicarFeed("distancia", distancia);
    publicarFeedTexto("bomba", "OFF");

    float tensaoPH = lerTensaoPH();
   float PH = calcularPH(tensaoPH);

    float tensaoTurbidez = lerTensaoTurbidez();
    float turbidez = calcularNTU(tensaoTurbidez);

    publicarFeed("ph", PH);
    publicarFeed("turbidez", turbidez);

    Serial.println("Bomba desligada.");

    Serial.print("pH: ");
    Serial.print(tensaoPH, 3);
    Serial.print(" V | ");
    Serial.print(PH, 2);
    Serial.println(" pH");

    Serial.print("Turbidez: ");
    Serial.print(tensaoTurbidez, 3);
    Serial.print(" V | ");
    Serial.print(turbidez, 2);
    Serial.println(" NTU");

    delay(10000);
    return;
  }

  delay(1000);
}