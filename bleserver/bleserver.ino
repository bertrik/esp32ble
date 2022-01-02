/**
 * A BLE server example.
 */

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

static BLECharacteristic *pm10Characteristic;
static BLECharacteristic *pm2_5Characteristic;
static BLECharacteristic *pm1_0Characteristic;

void setup(void)
{
    Serial.begin(115200);
    Serial.println("Starting Arduino BLE Client application...");

    BLEDevice::init("MyDevice");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService("181A");

    pm10Characteristic = pService->createCharacteristic("28D5",
                                                        BLECharacteristic::PROPERTY_READ |
                                                        BLECharacteristic::PROPERTY_NOTIFY);
    pm2_5Characteristic = pService->createCharacteristic("28D6",
                                                         BLECharacteristic::PROPERTY_READ |
                                                         BLECharacteristic::PROPERTY_NOTIFY);
    pm1_0Characteristic = pService->createCharacteristic("28D7",
                                                         BLECharacteristic::PROPERTY_READ |
                                                         BLECharacteristic::PROPERTY_NOTIFY);

    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID("181A");
    BLEDevice::startAdvertising();
}

static int last_second = 0;

void loop(void)
{
    unsigned long ms = millis();
    int second = ms / 1000;
    if (second != last_second) {
        last_second = second;
        double pm10 = 10.0;
        double pm2_5 = 2.5;
        double pm1_0 = 1.0;

        pm10Characteristic->setValue(pm10);
        pm2_5Characteristic->setValue(pm2_5);
        pm1_0Characteristic->setValue(pm1_0);
    }

}
