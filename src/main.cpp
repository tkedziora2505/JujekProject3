#include <iosfwd>
#include <FS.h>
#include <ArduinoJson.h>
class JsonFile {
    private:
        String _ssid;
        String _password;
        String _bssid;

    public:
        void displayConfig() {
            Serial.println("ssid: " + _ssid);
            Serial.println("password: " + _password);
            Serial.println("bassid: " + _bssid);
        }
        void loadConfig() {
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

            const char* ssid = root["ssid"];
            _ssid = ssid;
            const char* password = root["password"];
            _password = password;
            const char* bssid = root["bssid"];
            _bssid = bssid;

        }

        void setSsid (String ssid) {
            _ssid = ssid;
        }

        void setPassword (String password) {
            _password = password;
        }

        void setBssid (String bssid) {
            _bssid = bssid;
        }

        String getSsid() {
            return _ssid;
        }

        String getPassword() {
            return _password;
        }

        String getBssid() {
            return _bssid;
        }

//    void saveConfigJson() {
//        //save the custom parameters to FS
//        Serial.println("saving config");
//        DynamicJsonBuffer jsonBuffer;
//        JsonObject& json = jsonBuffer.createObject();
//        json["mqtt_server"] = mqtt_server;
//        json["mqtt_port"] = mqtt_portStr;
//        json["mqtt_username"] = mqtt_username;
//        json["mqtt_password"] = mqtt_password;
//        json["mqtt_topic"] = mqtt_topic;
//
//        File configFile = SPIFFS.open("/config.json", "w");
//        if (!configFile) {
//            Serial.println("failed to open config file for writing");
//        }
//
//        json.printTo(Serial);
//        Serial.println();
//        json.printTo(configFile);
//        configFile.close();
//        //end save
//    }
};

void setup()
{


    Serial.begin(9600);
    while(!Serial);
    delay(5000);
    Serial.println("start!");

    JsonFile config;
    config.loadConfig();
    Serial.println("Config 1 ===============");
    config.displayConfig();
    Serial.println("Config 2 ===============");
    config.setSsid("Abracadabra");
    Serial.println(config.getSsid());

    Serial.println("Stop");
}

void loop()
{

}
