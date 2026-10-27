# ESP32 → ThingSpeak: Live Temperature & Humidity Monitoring

**Student:** Mayar Othman
**University ID:** 12323342
**University:** An-Najah National University
**Course:** Internet of Things (IoT)

---

## Project Description

This project reads live **temperature** and **humidity** values from a **DHT22** sensor connected to an **ESP32**, then sends them to the **ThingSpeak** cloud platform over Wi-Fi every 25 seconds. ThingSpeak stores the readings and displays them publicly using its built-in live charts.

The project was built and tested on the **Wokwi** online simulator with Internet simulation enabled.

### How it works
1. The ESP32 connects to Wi-Fi (`Wokwi-GUEST` in the simulator).
2. It reads temperature (°C) and humidity (%) from the DHT22 sensor.
3. It sends an HTTP GET request to the ThingSpeak Update API:
   ```
   http://api.thingspeak.com/update?api_key=XXXX&field1=<temp>&field2=<humidity>&status=UniversityID_12323342
   ```
4. ThingSpeak returns the new entry ID and updates the live charts.

The **University ID (12323342)** is included both in the HTTP request (`status` parameter) and in every line printed to the Serial Monitor.

---

## Links

| | |
|---|---|
| **ThingSpeak Public Channel** | https://thingspeak.mathworks.com/channels/3551735 |
| **Wokwi Simulation** | WOKWI_LINK_HERE |

### ThingSpeak Channel Setup
- **Channel name:** `Mayar_Othman_12323342`
- **Field 1:** Temperature (°C)
- **Field 2:** Humidity (%)
- **Access:** Public

---

## Hardware / Simulation

| Component | Details |
|---|---|
| Microcontroller | ESP32 DevKit C v4 |
| Sensor | DHT22 (temperature & humidity) |
| Platform | Wokwi simulator (Internet simulation enabled) |

### Wiring

| DHT22 Pin | ESP32 Pin |
|---|---|
| VCC | 3.3V |
| GND | GND |
| DATA (SDA) | **GPIO 15** |

```
   DHT22                ESP32
 ┌────────┐          ┌──────────┐
 │  VCC   │──────────│  3.3V    │
 │  DATA  │──────────│  GPIO 15 │
 │  GND   │──────────│  GND     │
 └────────┘          └──────────┘
```

![Wokwi circuit](screenshots/wokwi_circuit.png)

---

## Repository Structure

```
├── sketch.ino          # ESP32 source code
├── diagram.json        # Wokwi circuit (schematic)
├── libraries.txt       # Required libraries for Wokwi
├── README.md
└── screenshots/
    ├── channel_page.png
    ├── temperature_graph.png
    ├── humidity_graph.png
    ├── serial_monitor.png
    └── wokwi_circuit.png
```

## Libraries Used
- `WiFi.h` (built-in ESP32)
- `HTTPClient.h` (built-in ESP32)
- `DHT sensor library` by Adafruit

---

## How to Run

1. Open the Wokwi project link above (or create a new ESP32 project and copy `sketch.ino`, `diagram.json` and `libraries.txt`).
2. In `sketch.ino`, replace `YOUR_WRITE_API_KEY` with your ThingSpeak channel's **Write API Key**.
3. Start the simulation.
4. Click the DHT22 sensor to change temperature and humidity values while it runs.
5. Open the ThingSpeak public channel to watch the charts update.

> Note: ThingSpeak's free plan accepts one update every 15 seconds, so the code sends every 25 seconds.

---

## Results

### Serial Monitor
Shows Wi-Fi connection, sensor readings, University ID, and `HTTP 200` responses with increasing entry IDs.

![Serial Monitor](screenshots/serial_monitor.png)

### ThingSpeak Channel Page
![Channel page](screenshots/channel_page.png)

### Live Temperature Graph
![Temperature graph](screenshots/temperature_graph.png)

### Live Humidity Graph
![Humidity graph](screenshots/humidity_graph.png)
