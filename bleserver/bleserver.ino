/**
 * A BLE server example.
 */

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

static BLECharacteristic *pm10Characteristic;
static BLECharacteristic *pm2_5Characteristic;
static BLECharacteristic *pm1_0Characteristic;

// creates a new user descriptor and adds it to the characteristic
static BLEDescriptor *addStringDescriptor(BLECharacteristic * characteristic, const char *uuid,
                                          const char *value)
{
    BLEDescriptor *descriptor = new BLEDescriptor(uuid);
    descriptor->setValue(value);
    characteristic->addDescriptor(descriptor);
    return descriptor;
}

void setup(void)
{
    Serial.begin(115200);
    Serial.println("Starting Arduino BLE Client application...");

    BLEDevice::init("MyDevice");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService("181A");

    // PM10
    pm10Characteristic = pService->createCharacteristic("28D5",
                                                        BLECharacteristic::PROPERTY_READ |
                                                        BLECharacteristic::PROPERTY_NOTIFY);
    addStringDescriptor(pm10Characteristic, "2901", "PM10");

    // PM2.5
    pm2_5Characteristic = pService->createCharacteristic("28D6",
                                                         BLECharacteristic::PROPERTY_READ |
                                                         BLECharacteristic::PROPERTY_NOTIFY);
    addStringDescriptor(pm2_5Characteristic, "2901", "PM2.5");

    // PM1.0
    pm1_0Characteristic = pService->createCharacteristic("28D7",
                                                         BLECharacteristic::PROPERTY_READ |
                                                         BLECharacteristic::PROPERTY_NOTIFY);
    addStringDescriptor(pm1_0Characteristic, "2901", "PM1.0");

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
