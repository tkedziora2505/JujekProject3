#include <iosfwd>
#include <FS.h>
#include <ArduinoJson.h>


void setup()
{


    Serial.begin(9600);
    while(!Serial);
    delay(5000);
    Serial.println("start!");
    SPIFFS.begin();
    File dataFile = SPIFFS.open("/config.json","r+");
    String string = dataFile.readString();
    char jsonTab[string.length() + 1];
    string.toCharArray(jsonTab, sizeof(jsonTab));
    StaticJsonBuffer <1024> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(jsonTab);
        if (!root.success()) {                            // everything OK
            Serial.println("MTparseObject() failed");
        }
    const char* category = root["category"];
    Serial.println(category);
    const char* name = root["name"];
    Serial.println(name);

    dataFile.close();
    SPIFFS.end();
    Serial.println("Stop");
}

void loop()
{

}





