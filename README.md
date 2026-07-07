# 🛰️ IoT Radar System (ESP32-Based)

> UAS Sistem Mikrokontroler - ESP32 IoT Radar dengan FreeRTOS dan Web Dashboard

---

## 👨‍🎓 Informasi Mahasiswa

| Keterangan | Detail |
|------------|--------|
| **Nama** | Sheila Nur Hamidah |
| **NIM** | 23552011398 |
| **Kelas** | TIF RP 23 CNS A |
| **Mata Kuliah** | Sistem Mikrokontroler |
| **Proyek** | IoT Radar System Berbasis ESP32 |

---

# 📖 Deskripsi Proyek

IoT Radar System merupakan sistem pemindaian objek berbasis **ESP32** yang memanfaatkan sensor ultrasonik **HC-SR04** dan motor **Servo** untuk melakukan scanning area secara otomatis dari sudut **0° hingga 180°**.

ESP32 berfungsi sebagai pusat pengendali seluruh perangkat sekaligus web server sehingga hasil pemindaian dapat dipantau secara **real-time** melalui browser menggunakan jaringan Wi-Fi.

Data yang diperoleh berupa:

- Sudut Servo
- Jarak Objek
- Status Keamanan
- Informasi Monitoring

Seluruh data dikirim dalam format **JSON API** sehingga dapat divisualisasikan pada dashboard web secara langsung.

---

# ✨ Fitur Utama

## 📡 Radar Scanning 180°

Servo bergerak otomatis dari:

- 0°
- sampai
- 180°

Sensor HC-SR04 membaca jarak objek pada setiap sudut sehingga menghasilkan data pemindaian secara real-time.

---

## 🌐 Embedded Web Server

ESP32 menyediakan web server internal yang dapat diakses melalui browser menggunakan alamat IP lokal.

Endpoint yang tersedia:

| Endpoint | Fungsi |
|----------|---------|
| `/` | Dashboard |
| `/data` | Mengirim data radar (JSON) |
| `/status` | Status perangkat |
| `/scan` | Menjalankan scanning |
| `/stop` | Menghentikan scanning |

---

## 🔔 Early Warning System

Sistem memberikan indikator berdasarkan jarak objek.

| Zona | Jarak | Indikator |
|-------|--------|-----------|
| 🟢 Aman | >30 cm | LED Hijau |
| 🟡 Waspada | 16–30 cm | LED Kuning |
| 🔴 Bahaya | ≤15 cm | LED Merah + Buzzer |


# 🛠 Hardware

Komponen yang digunakan:

- ESP32 Development Board
- Sensor Ultrasonik HC-SR04
- Servo Motor SG90
- LED Merah
- LED Kuning
- LED Hijau
- Active Buzzer
- Breadboard
- Kabel Jumper

---

# 🔌 Pin Mapping

| Komponen | GPIO |
|-----------|------|
| TRIG | GPIO 5 |
| ECHO | GPIO 18 |
| Servo | GPIO 19 |
| LED Merah | GPIO 25 |
| LED Kuning | GPIO 26 |
| LED Hijau | GPIO 27 |
| Buzzer | GPIO 23 |

---

# 🚨 Logika Early Warning

Program membagi hasil deteksi menjadi tiga kategori.

## 🔴 Zona Bahaya

**Jarak ≤15 cm**

- LED Merah ON
- Buzzer ON

---

## 🟡 Zona Waspada

**16–30 cm**

- LED Kuning ON
- Buzzer OFF

---

## 🟢 Zona Aman

**>30 cm**

- LED Hijau ON
- Buzzer OFF

---

# 🌐 Web Dashboard

BERIKUT LINK DEMO PROJECT UAS https://drive.google.com/drive/folders/1sxsOysFqAS7HrG7p0qs2c3aW4hAb_Ea-?usp=sharing

Dashboard digunakan untuk memonitor hasil scanning secara real-time.

---

## 🏠 Dashboard

Halaman utama monitoring radar.

### Fitur

- Radar Visualization
- Live Distance
- Current Angle
- Total Object Detection
- Device Status
- Detection Log
- Scan Button
- Pause Button
- Clear Data Button

> **Dashboard**

<img width="1280" height="598" alt="image" src="https://github.com/user-attachments/assets/328e23dd-ef3f-4546-aa6a-192506b4d27f" />

## 📜 Detection History

Menyimpan riwayat hasil scanning.

### Fitur

- Timestamp
- Angle
- Distance
- Status
- Export CSV

> **Tampilan History**

<img src="https://github.com/user-attachments/assets/f52f59a5-d38b-42b7-9c0f-71165add5ca4" alt="History">

## ⚙ Pengaturan

Halaman konfigurasi sistem.

### Pengaturan

#### ESP32 Connection

- IP Address
- Port
- Polling Interval

#### Threshold

- Danger Distance
- Warning Distance
- Maximum Distance

#### Notification

- Buzzer ON/OFF
- Browser Notification
- Demo Mode

> **Tampilan Pengaturan**

<img width="640" height="299" alt="image" src="https://github.com/user-attachments/assets/fa6936ec-a196-49a2-bdcd-a37dd577341d" />


## ℹ Tentang

Berisi dokumentasi sistem.

### Informasi

- Hardware Specification
- Wiring Diagram
- GPIO Mapping
- API Documentation

Contoh JSON Response

```json
{
  "angle": 90,
  "distance": 24,
  "status": "WARNING"
}
```

Endpoint API

```
GET /data
GET /status
GET /scan
GET /stop
```

> **Tampilan Tentang**

<img width="1280" height="596" alt="image" src="https://github.com/user-attachments/assets/c02f0138-e968-4d99-aacb-63214453edfb" />


# 📂 Struktur Project

```
Radar-System/
│
├── radar_sensor2.ino
├── README.md
├── assets/
│   ├── dashboard.png
│   ├── history.png
│   ├── settings.png
│   └── about.png
└── docs/
```

---

# 📊 Alur Kerja Sistem

```
HC-SR04
     │
     ▼
ESP32
     │
     ├──────── Servo Scan
     │
     ├──────── LED & Buzzer
     │
     └──────── Wi-Fi
               │
               ▼
        Web Dashboard
```

---

# 🎯 Kesimpulan

IoT Radar System berbasis ESP32 berhasil mengintegrasikan sensor ultrasonik, motor servo, indikator LED, buzzer, serta web dashboard dalam satu sistem monitoring yang mampu melakukan pemindaian objek secara real-time.

Implementasi **FreeRTOS** memungkinkan proses scanning radar dan layanan web server berjalan secara paralel pada dua core ESP32 sehingga sistem menjadi lebih responsif, stabil, dan efisien dibandingkan menggunakan metode pemrograman Arduino konvensional.

Dashboard web memberikan kemudahan dalam memonitor hasil pemindaian, melihat riwayat deteksi, melakukan konfigurasi sistem, serta mengakses dokumentasi perangkat secara terpusat.

---

# 👩‍💻 Author

**Sheila Nur Hamidah**

NIM : **23552011398**

Universitas Teknologi Bandung

Program Studi Teknik Informatika
