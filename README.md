# ESP32-BLE-MIDI_fixed_v1.2.1
ESP32-BLE-MIDI_fixed_v1.2.1
# 🎵 ESP32-BLE-MIDI (Fixed for NimBLE & ESP32-S3)

Обновлённая библиотека BLE MIDI для ESP32 с поддержкой **NimBLE-Arduino** и полной совместимостью с **ESP32-S3**, включая **M5Stack Cardputer**.

---

## 🚀 Цель переделки

Оригинальная библиотека [`max22-/ESP32-BLE-MIDI`](https://github.com/max22-/ESP32-BLE-MIDI) была отличной базой, но:
- Использовала устаревший стек BLE (`BLEDevice`), несовместимый с `NimBLE-Arduino`;
- Не поддерживала ESP32-S3 / Cardputer (ошибки при компиляции под Xtensa S3);
- Содержала устаревшие сигнатуры `BLEServerCallbacks` / `BLECharacteristicCallbacks`;
- Не имела стабильной работы в режиме Server+Client (MIDI Out/In);
- Не компилировалась на macOS (ARM64) в Arduino IDE 2.3.x.

---

## 🧩 Что исправлено и улучшено

### 🔧 Совместимость
✅ Полный переход на `NimBLE-Arduino 2.3.6+`  
✅ Проверено на **ESP32-S3**, **M5Stack Cardputer**, **TTGO T-Display**, **Core2**  
✅ Работает в Arduino IDE 2.3.2 (macOS ARM64 и Windows/Linux)  

---

### 🎛️ Новые возможности
- 🟢 **BLEMidiServer (MIDI OUT)** — отправка MIDI-сообщений по BLE  
- 🔵 **BLEMidiClient (MIDI IN)** — приём MIDI-сообщений от BLE-устройств  
- 🔁 Поддержка **двустороннего MIDI (In + Out)**  
- 🧠 Полная совместимость с `NimBLEService`, `NimBLECharacteristic`, `NimBLEAdvertising`  
- 🔔 Колбэки подключения и отключения  
- 🧱 Упрощённая структура для Arduino IDE (`/src`, `library.properties`, `examples`)  
- 💬 Добавлены методы `noteOn()` и `noteOff()` в базовый класс

---

## 🧠 Решённые проблемы

| Проблема | Что было | Решение |
|-----------|-----------|---------|
| `marked 'override', but does not override` | Несовместимые BLE классы | Переписано под `NimBLEServerCallbacks` |
| `No such file or directory: utility/BLEMidiServer.h` | Старый путь в структуре | Всё перенесено в `/src` |
| Несовпадение `connectToServer()` | Разные типы параметров | Исправлено на `NimBLEAdvertisedDevice*` |
| Ошибки `noteOn` / `noteOff` | Не реализованы | Добавлены в `BLEMidiBase` |
| Не компилировалась на ESP32-S3 | Старый BLE стек | Полностью на NimBLE |
| Не было метаданных | Отсутствовал `library.properties` | Добавлен и проверен |

---

## 📂 Структура библиотеки

ESP32-BLE-MIDI/
├── src/
│   ├── BLEMidiBase.h / .cpp
│   ├── BLEMidiServer.h / .cpp
│   ├── BLEMidiClient.h / .cpp
│   └── utility/
│       └── Debug.cpp
├── examples/
│   └── BidirectionalDemo/
│       └── BidirectionalDemo.ino
├── library.properties
└── README.md

---

## ⚙️ Пример использования

```cpp
#include <BLEMidiServer.h>
#include <BLEMidiClient.h>

void setup() {
  Serial.begin(115200);

  // Инициализация BLE MIDI Server (OUT)
  BLEMidiServer.begin("Cardputer Sequencer");

  // Инициализация BLE MIDI Client (IN)
  BLEMidiClient.begin("Cardputer Sequencer");

  BLEMidiServer.setOnConnectCallback([]() {
    Serial.println("🎵 BLE MIDI Connected!");
  });
}

void loop() {
  // Отправляем MIDI-сообщение
  BLEMidiServer.noteOn(60, 100, 1);
  delay(500);
  BLEMidiServer.noteOff(60, 0, 1);
  delay(500);
}
## ⚙️ История изменений (Changelog)

🆕 v1.3.0 (Октябрь 2025)
	•	Добавлена полная поддержка ESP32-S3 / M5Stack Cardputer
	•	Объединён Server + Client (двусторонний MIDI)
	•	Добавлены методы noteOn(), noteOff()
	•	Исправлены колбэки onConnect() / onDisconnect()
	•	Переработана структура под Arduino IDE 2.3.x
	•	Добавлен пример BidirectionalDemo.ino

⸻

⚙️ v1.2.1 (Сентябрь 2025)
	•	Исправлены ошибки компиляции в BLEMidiServer.h и BLEMidiClient.h
	•	Приведены сигнатуры к NimBLEServerCallbacks / NimBLEClientCallbacks
	•	Удалены старые пути /utility и конфликтующие include’ы
	•	Добавлен library.properties с метаданными
	•	Оптимизирована работа под macOS (ARM64)

⸻

🧩 v1.1.0 (Август 2025)
	•	Базовая адаптация библиотеки под NimBLE-Arduino
	•	Исправления под ESP-IDF 5.x
	•	Начальная совместимость с ESP32-S3
	•	Оптимизация BLE-соединения и уменьшение памяти

⸻

🧰 Установка
	1.	Скачайте архив ESP32-BLE-MIDI_Fixed.zip
	2.	В Arduino IDE выберите:
Sketch → Include Library → Add .ZIP Library…
	3.	Убедитесь, что в списке появилась:
ESP32 BLE MIDI (Fixed)

⸻

🧑‍💻 Авторы и благодарности

🛠️ Michael Sinitsin — интеграция с M5Stack Cardputer, тестирование под macOS ARM
📅 Октябрь 2025

 Лицензия

Библиотека распространяется под MIT License, как и оригинальная ESP32-BLE-MIDI.
Можно свободно использовать, изменять и распространять в любых проектах.

