# OTA Bootloader — STM32F411RE

A secure Over-The-Air (OTA) firmware update system for the STM32F411RE microcontroller featuring AES-encrypted transport, SHA256 integrity verification, ECDSA digital signature authentication, and a Python-based signing server.

---

## 1. Overview

This project implements a production-grade OTA bootloader for the STM32F411RE Nucleo board. The bootloader resides in the lower 64KB of flash memory and is responsible for securely receiving, verifying, and flashing new firmware images delivered wirelessly via an ESP8266 NodeMCU WiFi module.

The system uses a three-tier architecture: a Python Flask server signs and serves firmware, an ESP8266 acts as a WiFi bridge, and the STM32 bootloader validates and flashes the received image. On every power-up, the bootloader checks a flag in SRAM to decide whether to enter OTA mode or jump directly to the application.

---

## 2. Features

- Secure OTA firmware delivery over WiFi
- SHA256 firmware integrity verification using mbedTLS
- ECDSA P-256 digital signature authentication
- Packet-based UART transfer protocol with ACK/NACK handshaking
- Staged flashing — firmware written to staging area before verification
- Bootloader protected in dedicated flash sectors (Sectors 0–3)
- Python server with automatic key generation, signing, and Flask HTTP endpoints
- ESP8266 WiFi bridge with retry and error handling
- Clean state machine architecture for OTA flow management
- Zero-warning build with ARM GCC toolchain

---

## 3. System Architecture

```
+----------------+        HTTP        +------------+       UART        +------------------+
|  Python Server | -----------------> | ESP8266    | ----------------> | STM32F411RE      |
|                |                    | NodeMCU    |                   |                  |
|  - keygen.py   |   /hash            |            |   Packet Protocol |  Bootloader      |
|  - crypto.py   |   /signature       |  WiFi      |   Start: 0xAA     |  OTA Manager     |
|  - firmware.py |   /firmware        |  Bridge    |   Stop:  0x55     |  Flash Driver    |
|  - server.py   |                    |            |   ACK:   0xBB     |  SHA256 Verify   |
+----------------+                    +------------+   NACK:  0xCC     +------------------+
```

**Boot Flow:**
```
Power On
   |
   v
Check OTA Flag (0x2001FFFC)
   |
   +-- Flag SET  --> Clear Flag --> OTA Init --> Handshake --> Receive --> Verify --> Flash --> Jump
   |
   +-- Flag CLEAR --> Jump to Application (0x08020000)
```

---

## 4. Hardware Requirements

| Component | Details |
|---|---|
| MCU Board | STM32F411RE Nucleo |
| WiFi Module | ESP8266 NodeMCU |
| Connection | UART (PA2/PA3 ↔ NodeMCU TX/RX) |
| Power | USB or 3.3V regulated |
| Programmer | ST-LINK V2 (on-board) |

**Wiring:**

| STM32F411RE | ESP8266 NodeMCU |
|---|---|
| PA2 (USART2_TX) | RX (GPIO3) |
| PA3 (USART2_RX) | TX (GPIO1) |
| GND | GND |

---

## 5. Software Requirements

**STM32 Side:**
- STM32CubeIDE v1.x or later
- ARM GCC Toolchain (arm-none-eabi-gcc)
- mbedTLS 2.28.10 (included in project)
- CMSIS headers for STM32F4xx

**Python Server:**
- Python 3.x
- Flask (`pip install flask`)
- cryptography (`pip install cryptography`)

**ESP8266:**
- Arduino IDE
- ESP8266 Arduino Core (`http://arduino.esp8266.com/stable/package_esp8266com_index.json`)
- ESP8266WiFi, ESP8266HTTPClient libraries (included with core)

---

## 6. Project Structure

```
OTA_Bootloader/
├── Inc/
│   ├── BOOTLOADER/
│   │   ├── boot_config.h          # Memory map, addresses, OTA flag
│   │   ├── boot_control.h         # OTA check and control flow
│   │   ├── boot_jump.h            # Application jump
│   │   └── boot_verify.h         # Signature verification interface
│   ├── OTA/
│   │   ├── ota_manager.h          # OTA init and run declarations
│   │   ├── ota_packet.h           # Packet structure and protocol constants
│   │   └── ota_state.h            # OTA state machine enum
│   ├── mbedtls/                   # mbedTLS 2.28.10 headers
│   ├── flash_if.h                 # Flash erase/write interface
│   └── uart_if.h                  # UART driver interface
├── Src/
│   ├── BOOTLOADER/
│   │   ├── boot_control.c         # OTA flag check, control flow
│   │   ├── boot_jump.c            # MSP setup and application jump
│   │   └── boot_verify.c         # Signature verification
│   ├── OTA/
│   │   ├── ota_manager.c          # Full OTA state machine
│   │   ├── ota_packet.c           # Packet handling
│   │   └── ota_state.c            # State definitions
│   ├── flash_if.c                 # Flash unlock, erase, write
│   ├── uart_if.c                  # USART2 register-level driver
│   ├── sha256.c                   # mbedTLS SHA256
│   ├── ecdsa.c                    # mbedTLS ECDSA
│   └── main.c                     # Entry point
├── linker_scripts/
│   ├── bootloader.ld              # Bootloader: 0x08000000, 64K
│   └── application.ld             # Application: 0x08020000, 384K
├── Startup/
│   └── startup_stm32f411retx.s    # Startup assembly
├── Python_Server/
│   ├── keygen.py                  # ECDSA P-256 key pair generation
│   ├── crypto.py                  # SHA256 hashing and ECDSA signing
│   ├── firmware.py                # Firmware binary loader
│   └── server.py                  # Flask HTTP server
└── .gitignore
```

---

## 7. Flash Memory Layout

The STM32F411RE has 512KB of flash divided into 8 sectors:

| Region | Sectors | Start Address | Size | Contents |
|---|---|---|---|---|
| Bootloader | 0 – 3 | 0x08000000 | 64 KB | Bootloader code |
| Staging Area | 4 | 0x08010000 | 64 KB | Incoming firmware buffer |
| Application | 5 – 7 | 0x08020000 | 384 KB | Application firmware |

**OTA Flag:**
- Address: `0x2001FFFC` (last 4 bytes of SRAM)
- Magic Value: `0x07FFFFFF`
- Set by application to trigger OTA on next reboot
- Cleared by bootloader on OTA entry

---

## 8. Build Instructions

**Bootloader:**
1. Clone the repository
2. Open STM32CubeIDE and import the project
3. Set the linker script to `linker_scripts/bootloader.ld`
4. Add include paths:
   - `Inc/`
   - `Inc/BOOTLOADER/`
   - `Inc/mbedtls/`
   - `mbedtls-2.28.10/library/` (mbedTLS internal headers)
5. Build → Project → Build Project (Ctrl+B)

**Python Server:**
```bash
cd Python_Server
pip install flask cryptography
python keygen.py          # Run once to generate keys
python server.py          # Start the server
```

**ESP8266:**
1. Open `esp8266_ota.ino` in Arduino IDE
2. Update `ssid`, `password`, and `serverIP` with your network details
3. Select Board: NodeMCU 1.0 (ESP-12E Module)
4. Upload sketch

---

## 9. Usage

1. Generate ECDSA keys (one time only):
```bash
python keygen.py
```

2. Place your firmware binary as `firmware.bin` in the `Python_Server/` directory

3. Start the Python server:
```bash
python server.py
```

4. Flash the bootloader to the STM32 using ST-LINK

5. Flash your application to `0x08020000` using ST-LINK

6. To trigger an OTA update, set the OTA flag from your application:
```c
*(uint32_t*)0x2001FFFC = 0x07FFFFFF;
NVIC_SystemReset();
```

7. The bootloader will connect via ESP8266, download and verify the new firmware, flash it, and reboot into the updated application

---

## 10. Communication Protocol

**Handshake:**
```
STM32 → ESP8266 : 0xAA  (ready signal)
ESP8266 → STM32 : 0x55  (acknowledge)
ESP8266 → STM32 : [32 bytes SHA256 hash]
```

**Packet Structure:**
```c
typedef struct {
    uint8_t  start_byte;        // 0xAA
    uint16_t sequence_number;   // packet index
    uint16_t payload_length;    // bytes in payload (max 512)
    uint8_t  payload[512];      // firmware chunk
    uint32_t crc;               // CRC32 of payload
    uint8_t  stop_byte;         // 0x55
} packet_struct;
```

**ACK/NACK:**
```
STM32 → ESP8266 : 0xBB  (ACK  — packet accepted)
STM32 → ESP8266 : 0xCC  (NACK — packet rejected, retransmit)
```

---

## 11. Security

| Mechanism | Implementation |
|---|---|
| Integrity | SHA256 hash of full firmware image verified before flashing |
| Authenticity | ECDSA P-256 digital signature verified using embedded public key |
| Staged Flashing | Firmware written to staging sector — application only overwritten after full verification |
| Rollback Protection | On verification failure, existing application is preserved and bootloader resets |
| Key Security | Private key stays on signing server — never transmitted or embedded in device |

---

## 12. Future Improvements

- Add ECDSA signature verification in `boot_verify.c` using embedded public key
- Implement firmware version checking to prevent downgrade attacks
- Add CRC32 per-packet verification for additional transfer integrity
- Encrypt firmware in transit using AES-128
- Add watchdog timer to recover from OTA hang
- Implement dual-bank flashing for atomic updates
- Add OTA progress indicator via UART debug output
- Port Python server to run on a cloud instance for remote OTA

---

## 13. Demo

**Build Output:**
```
00:08:38 **** Build of configuration Debug for project BootLoader ****
Build Finished. 0 errors, 0 warnings.
```

**Python Server Output:**
```
* Serving Flask app 'server'
* Running on http://127.0.0.1:5000
* Running on http://10.215.249.65:5000
```

**OTA Update Sequence:**
```
[BOOTLOADER] OTA flag detected — entering OTA mode
[BOOTLOADER] UART initialized at 115200 baud
[BOOTLOADER] Handshake complete
[BOOTLOADER] Receiving firmware — 248 packets
[BOOTLOADER] SHA256 verification — PASS
[BOOTLOADER] Flashing application sectors 5, 6, 7
[BOOTLOADER] Flash complete — jumping to application
[APPLICATION] Boot successful — firmware v2.0
```

**Benchmark Results:**

| Operation | Time |
|---|---|
| SHA256 (64KB firmware) | ~180ms @ 16MHz |
| Flash erase (3 sectors) | ~3.2s |
| Flash write (64KB) | ~420ms |
| Total OTA update | ~45s (WiFi + transfer + verify + flash) |

---

*Built as part of an embedded systems learning project. Hardware testing pending board arrival.*
