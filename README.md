# IoT Radar System (ESP32-Based) 🛰️

**Informasi Mahasiswa:**
* **Proyek:** UAS - Sistem Mikrokontroler
* **Nama:** Sheila Nur Hamidah
* **NIM:** 23552011398
* **Kelas:** TIF RP 23 CNS A

---

📌 Deskripsi Proyek
Proyek IoT Radar System ini dirancang sebagai solusi pemindaian area berbasis Single-Board System memanfaatkan ESP32 sebagai unit pemrosesan tunggal. Radar ini bekerja dengan menggerakkan sensor ultrasonik menggunakan motor servo untuk memindai objek di sekitar dalam radius 0° hingga 180°.

Data spasial berupa kombinasi jarak dan sudut objek diproses secara real-time oleh ESP32, kemudian ditransmisikan langsung via Wi-Fi ke cloud dashboard untuk visualisasi data pemantauan jarak jauh.

🚀 Fitur Utama
Arsitektur Single-Board: Mengoptimalkan performa ESP32 secara efisien, menghasilkan sistem yang lebih ringkas, hemat daya, dan meminimalisir kompleksitas pengkabelan (wiring).

Pemindaian Otomatis 180°: Motor servo bergerak secara dinamis menyapu area sekitar untuk melakukan scanning sudut secara presisi.

Konektivitas Cloud Terintegrasi: Data hasil pemindaian langsung diunggah ke platform IoT (Blynk / Antares / ThingSpeak / Firebase) secara real-time melalui jaringan Wi-Fi.

Mekanisme Peringatan Dini (Early Warning): Dilengkapi dengan indikator fisik berupa Buzzer dan LED yang akan aktif secara otomatis jika terdeteksi objek dalam jarak aman yang ditentukan.

🛠️ Komponen & Perangkat Keras
ESP32 Development Board (Sebagai Kontroler Utama & Modul Wi-Fi)

Sensor Ultrasonik (HC-SR04) (Pengukur Jarak Objek)

Servo Motor (SG90 / MG90S) (Penggerak Posisi Radar)

Buzzer & LED (Sistem Alaram/Peringatan)

Kabel Jumper & Breadboard
