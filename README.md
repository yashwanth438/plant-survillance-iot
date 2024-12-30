# Smart Plant Monitoring System

This project is a Smart Plant Monitoring System built using an ESP8266 microcontroller, various sensors, and Blynk IoT integration. The system monitors soil moisture, temperature, and humidity levels, and detects motion near the plant. It also controls a water pump relay and displays sensor data on an LCD screen.

## Features

- **Soil Moisture Monitoring**: Tracks the soil moisture level using an analog sensor and sends data to Blynk.
- **Temperature and Humidity Monitoring**: Measures environmental temperature and humidity using a DHT11 sensor.
- **Motion Detection**: Uses a PIR sensor to detect motion and logs an event in Blynk.
- **Relay Control**: Controls a water pump via a relay, which can be toggled manually or through the Blynk app.
- **LCD Display**: Displays real-time sensor data and system states on a 16x2 I2C LCD.

## Components Used

1. **ESP8266 WiFi Module**
2. **DHT11 Temperature and Humidity Sensor**
3. **Soil Moisture Sensor**
4. **PIR Motion Sensor**
5. **Relay Module**
6. **16x2 I2C LCD Display**
7. **Push Button**

## Circuit Connections

| Component               | Pin on ESP8266 |
|-------------------------|-----------------|
| Relay                  | D3              |
| Push Button            | D7              |
| Soil Moisture Sensor   | A0              |
| PIR Motion Sensor      | D5              |
| LCD SDA                | D2              |
| LCD SCL                | D1              |
| DHT11 Sensor           | D4              |

## Setup Instructions

### Prerequisites
1. Arduino IDE installed on your computer.
2. Blynk app installed on your smartphone.

### Installation

1. Clone or download this repository.
2. Open the `.ino` file in Arduino IDE.
3. Install the following libraries via Arduino Library Manager:
   - **Blynk**
   - **DHT Sensor Library**
   - **Adafruit Unified Sensor**
   - **LiquidCrystal_I2C**
4. Replace the placeholders in the code with your credentials:
   - `auth`: Your Blynk authentication token.
   - `ssid`: Your Wi-Fi SSID.
   - `pass`: Your Wi-Fi password.
5. Connect the components as per the circuit diagram.
6. Select the correct board (**NodeMCU 1.0 (ESP-12E Module)**) and COM port in the Arduino IDE.
7. Upload the code to the ESP8266.

### Blynk Configuration
1. Create a new project in the Blynk app and note the authentication token.
2. Add the following widgets:
   - **Button (V12)**: Toggle the relay.
   - **Value Display (V0)**: Show temperature.
   - **Value Display (V1)**: Show humidity.
   - **Value Display (V3)**: Show soil moisture.
   - **LED (V5)**: Indicate motion detection.
3. Configure the widget pins as per the code.

## Usage

1. Power on the system and connect it to Wi-Fi.
2. Monitor real-time sensor data on the LCD and the Blynk app.
3. Use the Blynk app to:
   - View soil moisture, temperature, and humidity data.
   - Receive motion detection alerts.
   - Toggle the water pump relay.
4. Observe the LCD for local display of data and system state:
   - `T:XX` for temperature.
   - `H:XX` for humidity.
   - `S:XX` for soil moisture.
   - `M:ON/OFF` for motion detection.
   - `W:ON/OFF` for water pump status.

## License

This project is open-source and available under the MIT License. Feel free to use, modify, and share.

## Acknowledgments

- [Blynk](https://blynk.io/) for their IoT platform.
- [Arduino](https://www.arduino.cc/) for their hardware and software ecosystem.

---

### Troubleshooting

- Ensure the ESP8266 is connected to Wi-Fi with the correct credentials.
- Verify the sensors and components are properly wired.
- Check the Blynk app for logs if values are not updating.
- Use the Serial Monitor (9600 baud rate) for debugging.
