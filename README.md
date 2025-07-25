# 🌊 Water Quality Monitoring System with Arduino

## 📝 Description

This project is a prototype of a water quality monitoring system that uses an Arduino board to measure various key water parameters. The system is designed to be modular and can be integrated with different types of sensors.

## 🌟 Features

- 🎚️ Multiple measurement parameters:
  - Water turbidity
  - pH level
  - Total Dissolved Solids (TDS)
  - Electrical conductivity
  - Temperature
  - Water color (using TCS3200 sensor)
- 📶 Serial communication for data transmission
- ⚙️ Sensor calibration system
- 💾 EEPROM configuration storage

## 🛠️ Main Components

- **Microcontroller**: Arduino (compatible)
- **Sensors**:
  - Turbidity sensor
  - pH sensor
  - Total Dissolved Solids (TDS) sensor
  - Conductivity sensor
  - Temperature sensor
  - TCS3200 color sensor

## 📁 Project Structure

```
src/
├── CommandManager.*      # Serial command management
├── ConfigStoredROM.*     # EEPROM configuration storage
├── SerialComm.*          # Serial communication
├── StateManager.*        # System state management
├── Sensors/              # Sensor drivers
│   ├── ColorTCS3200.*      # Color sensor
│   ├── ConductivityReadingSensor.*  # Conductivity sensor
│   ├── PhReadingSensor.*  # pH sensor
│   ├── TemperatureReadingSensor.*  # Temperature sensor
│   ├── TotalDissolvedSolids.*  # TDS sensor
│   └── TurbidityReadingSensor.*  # Turbidity sensor
└── main.cpp             # Main entry point
```

## 🚀 Setup

### Requirements

- Arduino IDE or PlatformIO
- Compatible Arduino board
- Required libraries (specified in .h files)

### Pin Configuration

- **Analog**:

  - A0: TDS sensor
  - A1: Turbidity sensor
  - A3: Conductivity sensor
  - A8: pH sensor

- **Digital**:
  - 2: Temperature sensor
  - 8-12: TCS3200 color sensor

## 🔧 Usage

1. Upload the sketch to your Arduino board
2. Connect the sensors according to the pin configuration
3. Start serial communication to view readings
4. Use available commands to calibrate the sensors

### Available Commands

#### Initial Setup

- `setApiKey <key>`: Sets the device API key
- `setWifiSsid <network_name>`: Configures the WiFi SSID
- `setWifiPassword <password>`: Sets the WiFi password
- `configureFinished`: Completes the initial setup

#### Calibration

- `phCalibrateVol4`: Calibrates the pH sensor with 4.01pH solution
- `phCalibrateVol6`: Calibrates the pH sensor with 6.86pH solution
- `phCalibrate`: Completes the pH sensor calibration
- `phSetVol4 <value>`: Manually sets voltage for pH 4.01
- `phSetVol6 <value>`: Manually sets voltage for pH 6.86
- `calibrateFinished`: Exits calibration mode

#### Operation

- `getConfig`: Displays current device configuration
- `reading`: Starts a sensor reading sequence
- `readingFinished`: Completes the current reading sequence

#### System States

- `connecting`: Indicates device is connecting
- `socketConnected`: Confirms successful server connection
- `socketDisconnected`: Indicates server disconnection
- `connectError`: Indicates connection error

## 🤝 Contributing

### 🌿 Branching Strategy

| Branch            | Description                            | Allowed commit types                 |
| ----------------- | -------------------------------------- | ------------------------------------ |
| `main`            | Main stable branch                     | Only `merge` and tags (`vX.X.X`)     |
| `feature/<name>`  | Adds new functionalities               | `feat`, `test`, `docs`, `style`      |
| `hotfix/<name>`   | Urgent fix in production               | `fix`, `style`, `chore`              |
| `bugfix/<name>`   | Non-urgent bug fix                     | `fix`, `test`                        |
| `refactor/<name>` | Code improvements without logic change | `refactor`, `style`, `docs`, `chore` |
| `docs/<name>`     | Documentation updates                  | `docs`                               |

### ✍️ Commit types (Conventional Commits)

We use the [Conventional Commits](https://www.conventionalcommits.org/) format to improve readability of history.

| Type       | Main usage                                            | Example                                                |
| ---------- | ----------------------------------------------------- | ------------------------------------------------------ |
| `feat`     | New functionality or feature                          | `feat: add new sensor for water turbidity measurement` |
| `fix`      | Bug fix                                               | `fix: correct bug in sensor reading calculation`       |
| `refactor` | Internal code improvement (without changing behavior) | `refactor: optimize code for better performance`       |
| `docs`     | Documentation updates                                 | `docs: update README with latest project information`  |
| `test`     | Add or modify tests                                   | `test: add unit tests for sensor reading validation`   |
| `style`    | Code formatting or styling (no logic changes)         | `style: apply consistent coding style`                 |
| `chore`    | Maintenance tasks that do not affect code logic       | `chore: update dependencies to latest version`         |

Contributions are welcome. Please ensure to follow Arduino programming best practices and document your changes appropriately.

## 📄 License

This project is licensed under the MIT License. See the `LICENSE` file for more information.

## 📧 Contact

For questions or support, please open an issue in the repository.
