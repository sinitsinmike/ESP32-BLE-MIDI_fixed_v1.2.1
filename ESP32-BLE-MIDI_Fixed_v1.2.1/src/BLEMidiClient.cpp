#include "BLEMidiClient.h"

void BLEMidiClientClass::begin(const std::string deviceName) {
    NimBLEDevice::init(deviceName);
}

bool BLEMidiClientClass::connectToServer(NimBLEAdvertisedDevice* device) {
    NimBLEClient* pClient = NimBLEDevice::createClient();
    pClient->setClientCallbacks(this);
    if (!pClient->connect(device)) return false;
#ifdef BLE_MIDI_DEBUG
    Serial.println("[BLE_MIDI] Connected to remote MIDI server");
#endif
    return true;
}

void BLEMidiClientClass::sendPacket(uint8_t *packet, uint8_t packetSize) {
    if (!connected) return;
#ifdef BLE_MIDI_DEBUG
    Serial.printf("[BLE_MIDI] Client sent %d bytes\n", packetSize);
#endif
}

void BLEMidiClientClass::onConnect(NimBLEClient* pClient) {
    connected = true;
#ifdef BLE_MIDI_DEBUG
    Serial.println("[BLE_MIDI] Client connected");
#endif
}

void BLEMidiClientClass::onDisconnect(NimBLEClient* pClient) {
    connected = false;
#ifdef BLE_MIDI_DEBUG
    Serial.println("[BLE_MIDI] Client disconnected");
#endif
}

BLEMidiClientClass BLEMidiClient;