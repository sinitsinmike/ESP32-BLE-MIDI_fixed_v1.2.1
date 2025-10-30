#pragma once
#include <Arduino.h>
#include <functional>
#include <NimBLEDevice.h>

#define MIDI_SERVICE_UUID        "03b80e5a-ede8-4b33-a751-6ce34ec4c700"
#define MIDI_CHARACTERISTIC_UUID "7772e5db-3868-4112-a1a9-f2669d106bf3"

class BLEMidi {
protected:
    bool connected = false;

    void receivePacket(uint8_t* data, uint8_t size) {
#ifdef BLE_MIDI_DEBUG
        Serial.printf("[BLE_MIDI] Received %d bytes\n", size);
#endif
    }

public:
    virtual void sendPacket(uint8_t *packet, uint8_t packetSize) = 0;

    void begin(const std::string& name) {
#ifdef BLE_MIDI_DEBUG
        Serial.printf("[BLE_MIDI] Init device: %s\n", name.c_str());
#endif
    }

    // 🎵 MIDI helpers
    void noteOn(uint8_t note, uint8_t velocity, uint8_t channel = 1) {
        uint8_t packet[] = {
            0x80,
            0x80 | (channel & 0x0F),
            0x90 | (channel & 0x0F),
            note & 0x7F,
            velocity & 0x7F
        };
        sendPacket(packet, sizeof(packet));
    }

    void noteOff(uint8_t note, uint8_t velocity = 0, uint8_t channel = 1) {
        uint8_t packet[] = {
            0x80,
            0x80 | (channel & 0x0F),
            0x80 | (channel & 0x0F),
            note & 0x7F,
            velocity & 0x7F
        };
        sendPacket(packet, sizeof(packet));
    }
};