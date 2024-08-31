# IoT Door Monitor

## Overview

The **IoT Door Monitor** is a fun and practical project that allows you to display your status on an LCD screen outside your room or office. Using a NodeMCU and a local server, you can easily update the status and control LED indicators based on your availability.

## Features

- **Remote Status Updates**: Show custom messages on an LCD screen using a web interface.
- **Status Control**: Change your status to "Available," "Not Available," or "None" via a simple HTML form.
- **Local Server**: Control your status and monitor the display using a local server created with NodeMCU.
- **LED Indicators**: Use LEDs to visually represent your status.

## Components

- **NodeMCU**: ESP8266-based microcontroller with WiFi capability.
- **LCD Display**: For showing messages.
- **LEDs**: For status indicators.
- **Resistors**: For LED connections.
- **Jumper Wires**: For connections.

## How It Works

1. **Setup**: Connect the NodeMCU to your WiFi network.
2. **Web Interface**: Access the local server created by the NodeMCU from any device on the same network.
3. **Update Status**: Use the web interface to send messages and select your availability status.
4. **Display**: The LCD screen updates with the message, and LEDs indicate your current status based on your selection.

## Getting Started

1. **Clone the Repository**:

    ```bash
    git clone https://github.com/emirkanesme/IoT-Door-Monitor.git
    cd IoT-Door-Monitor
    ```

2. **Install Libraries**:
   - Ensure you have the necessary libraries installed in the Arduino IDE:
     - `LiquidCrystal`
     - `ESP8266WiFi` (or `WiFi` for ESP32)

3. **Upload Code**:
   - Open the Arduino IDE and load the provided `.ino` file.
   - Connect your NodeMCU to your computer and upload the code.

4. **Access Web Interface**:
   - After uploading, open the Serial Monitor to find the NodeMCU’s IP address.
   - Open a web browser and navigate to the NodeMCU’s IP address.

5. **Use the Web Interface**:
   - Enter a message, select a status, and click "Send to LCD" to update the display and LEDs.

## Customization

- **Change WiFi Credentials**: Update the `ssid` and `password` variables in the Arduino code.
- **Modify HTML/CSS**: Customize the web interface to fit your preferences.

## Troubleshooting

- **Not Connecting to WiFi**: Ensure the `ssid` and `password` are correct and your NodeMCU is within range.
- **LCD Not Updating**: Check connections and ensure the correct pins are used.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact

For questions or feedback, please reach out to [2003emirkanesme@gmail.com](mailto:2003emirkanesme@gmail.com).

---

Enjoy building and using your IoT Door Monitor!

