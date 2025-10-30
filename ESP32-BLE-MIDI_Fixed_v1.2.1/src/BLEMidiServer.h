#pragma once
#include "BLEMidiBase.h"
#include <NimBLEDevice.h>

class BLEMidiServerClass : public BLEMidi, public NimBLEServerCallbacks {
public:
    void begin(const std::string deviceName);

    void setOnConnectCallback(void (*const onConnectCallback)());
    void setOnDisconnectCallback(void (*const onDisconnectCallback)());

private:
    void sendPacket(uint8_t *packet, uint8_t packetSize) override;
    void onConnect(NimBLEServer* pServer);
    void onDisconnect(NimBLEServer* pServer);

    void (*onConnectCallback)() = nullptr;
    void (*onDisconnectCallback)() = nullptr;
    NimBLECharacteristic* pCharacteristic = nullptr;
};

class CharacteristicCallback: public NimBLECharacteristicCallbacks {
public:
    CharacteristicCallback(std::function<void(uint8_t*, uint8_t)> onWriteCallback);
private:
    void onWrite(NimBLECharacteristic *pCharacteristic);
    std::function<void(uint8_t*, uint8_t)> onWriteCallback = nullptr;
};

extern BLEMidiServerClass BLEMidiServer;