#pragma once
#include "BLEMidiBase.h"
#include <NimBLEDevice.h>

class BLEMidiClientClass : public BLEMidi, public NimBLEClientCallbacks {
public:
    void begin(const std::string deviceName);
    bool connectToServer(NimBLEAdvertisedDevice* device);  // ✅ исправлено

    void onConnect(NimBLEClient* pClient);      // ❌ без override
    void onDisconnect(NimBLEClient* pClient);   // ❌ без override

private:
    void sendPacket(uint8_t *packet, uint8_t packetSize) override; // ✅ можно оставить
    NimBLEClient* pClient = nullptr;
    NimBLECharacteristic* pCharacteristic = nullptr;
};

extern BLEMidiClientClass BLEMidiClient;