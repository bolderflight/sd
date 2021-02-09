
#include "sd/SdFat.h"

#define SD_CONFIG SdioConfig(FIFO_SDIO)

SdFat32 sd;

int main() {
    Serial.begin(115200);
    while(!Serial) {}
    if (!sd.begin(SD_CONFIG)) {
        sd.initErrorHalt(&Serial);
    } else {
        Serial.println("GOOD");
    }
    // Serial.println(status);
}

