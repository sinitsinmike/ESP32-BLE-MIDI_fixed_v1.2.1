#include "BLEMidiServer.h"

void BLEMidiServerClass::begin(const std::string deviceName) {
    NimBLEDevice::init(deviceName);
    NimBLEServer *pServer = NimBLEDevice::createServer();
    pServer->setCallbacks(this);

    NimBLEService *pService = pServer->createService(MIDI_SERVICE_UUID);
    pCharacteristic = pService->createCharacteristic(
        MIDI_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::WRITE_NR
    );

    pCharacteristic->setCallbacks(new CharacteristicCallback(
        [this](uint8_t *data, uint8_t size) { this->receivePacket(data, size); }
    ));

    pService->start();
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(MIDI_SERVICE_UUID);
    pAdvertising->start();
}

void BLEMidiServerClass::setOnConnectCallback(void (*const cb)()) { this->onConnectCallback = cb; }
void BLEMidiServerClass::setOnDisconnectCallback(void (*const cb)()) { this->onDisconnectCallback = cb; }

void BLEMidiServerClass::sendPacket(uint8_t *packet, uint8_t packetSize) {
    if (!connected) return;
    pCharacteristic->setValue(packet, packetSize);
    pCharacteristic->notify();
#ifdef BLE_MIDI_DEBUG
    Serial.printf("[BLE_MIDI] Sent %d bytes\n", packetSize);
#endif
}

void BLEMidiServerClass::onConnect(NimBLEServer* pServer) {
    connected = true;
#ifdef BLE_MIDI_DEBUG
    Serial.println("[BLE_MIDI] Connected");
#endif
    if (onConnectCallback) onConnectCallback();
}

void BLEMidiServerClass::onDisconnect(NimBLEServer* pServer) {
    connected = false;
#ifdef BLE_MIDI_DEBUG
    Serial.println("[BLE_MIDI] Disconnected");
#endif
    if (onDisconnectCallback) onDisconnectCallback();
    pServer->startAdvertising();
}

CharacteristicCallback::CharacteristicCallback(std::function<void(uint8_t*, uint8_t)> cb) : onWriteCallback(cb) {}
void CharacteristicCallback::onWrite(NimBLECharacteristic *pCharacteristic) {
    std::string rxValue = pCharacteristic->getValue();
    if (rxValue.length() > 0 && onWriteCallback)
        onWriteCallback((uint8_t*)rxValue.c_str(), rxValue.length());
}
BLEMidiServerClass BLEMidiServer;