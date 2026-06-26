#include <ESP32Servo.h>
#include <WiFi.h>
#include <WebServer.h> // Menggunakan library WebServer bawaan ESP32

// =========================================================================
// FREE RTOS
// =========================================================================
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// =========================================================================
// KONFIGURASI WI-FI (Ganti sesuai dengan nama Wi-Fi dan Password di rumahmu)
// =========================================================================
const char* ssid     = "Dida's Galaxy A52";
const char* password = "Dida1234";

// Membuat objek Server pada Port 80
WebServer server(80);

// Variables global untuk menyimpan data terbaru agar bisa diakses oleh Web
int currentAngle = 0;
int currentDistance = 0;

// =========================================================================
// CONFIGURASI PIN
// =========================================================================
#define TRIG_PIN 5
#define ECHO_PIN 18
#define SERVO_PIN 19
#define LED_RED 25
#define LED_YELLOW 26
#define LED_GREEN 27
#define BUZZER_PIN 23

Servo myServo;

// =========================================================================
// DEKLARASI FUNGSI
// =========================================================================
int getDistance();
void kendaliIndikator(int distance);
void handleGetData();

// =========================================================================
// DEKLARASI TASK RTOS
// =========================================================================
void TaskRadar(void *pvParameters);
void TaskWebServer(void *pvParameters);

void setup() {

  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  myServo.attach(SERVO_PIN);

  // -----------------------------------------------------------------------
  // PROSES KONEKSI WI-FI
  // -----------------------------------------------------------------------
  Serial.print("Menghubungkan ke Wi-Fi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Terhubung!");
  Serial.print("Silakan masukkan IP ini ke web: ");
  Serial.println(WiFi.localIP());

  // -----------------------------------------------------------------------
  // PENGATURAN ROUTE API UNTUK WEB
  // -----------------------------------------------------------------------
  server.on("/data", HTTP_GET, handleGetData);

  server.enableCORS(true);

  server.begin();

  Serial.println("HTTP Web Server siap digunakan.");

  // =========================================================================
  // MEMBUAT TASK RTOS
  // =========================================================================

  xTaskCreatePinnedToCore(
    TaskRadar,
    "Task Radar",
    4096,
    NULL,
    1,
    NULL,
    1);

  xTaskCreatePinnedToCore(
    TaskWebServer,
    "Task Web",
    4096,
    NULL,
    1,
    NULL,
    0);
}

void loop() {
  // Semua proses dijalankan oleh FreeRTOS
  vTaskDelay(portMAX_DELAY);
}

// =========================================================================
// TASK RTOS UNTUK WEB SERVER
// =========================================================================
void TaskWebServer(void *pvParameters) {

  while (true) {

    server.handleClient();

    vTaskDelay(pdMS_TO_TICKS(5));
  }
}

// =========================================================================
// TASK RTOS UNTUK RADAR
// =========================================================================
void TaskRadar(void *pvParameters) {

  while (true) {

    // -----------------------------------------------------------------------
    // PERGERAKAN 1: 0 ke 180 derajat
    // -----------------------------------------------------------------------
    for (int angle = 0; angle <= 180; angle += 1) {

      myServo.write(angle);

      vTaskDelay(pdMS_TO_TICKS(15));

      if (angle % 2 == 0) {

        currentAngle = angle;
        currentDistance = getDistance();

        kendaliIndikator(currentDistance);
      }
    }

    // -----------------------------------------------------------------------
    // PERGERAKAN 2: 180 ke 0 derajat
    // -----------------------------------------------------------------------
    for (int angle = 180; angle >= 0; angle -= 1) {

      myServo.write(angle);

      vTaskDelay(pdMS_TO_TICKS(15));

      if (angle % 2 == 0) {

        currentAngle = angle;
        currentDistance = getDistance();

        kendaliIndikator(currentDistance);
      }
    }
  }
}

// =========================================================================
// FUNGSI API UNTUK MENGIRIM DATA JSON KE WEB
// =========================================================================
void handleGetData() {

  String json =
      "{\"angle\":" +
      String(currentAngle) +
      ",\"distance\":" +
      String(currentDistance) +
      "}";

  server.send(200, "application/json", json);
}

// =========================================================================
// FUNGSI UNTUK MENGHITUNG JARAK OBJEK
// =========================================================================
int getDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  int distance = duration * 0.034 / 2;

  return distance;
}

// =========================================================================
// FUNGSI LOGIKA KENDALI TRAFFIC LAMP & BUZZER BERDASARKAN JARAK
// =========================================================================
void kendaliIndikator(int distance) {

  if (distance > 0 && distance <= 15) {

    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(BUZZER_PIN, HIGH);

  } else if (distance > 15 && distance <= 30) {

    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

  } else {

    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
  }
}