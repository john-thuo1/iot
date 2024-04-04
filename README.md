
## Case Study 2 Overview
In Case Study 2, I used ESP8266 Node MCU, Soil Moisture Sensor, and DHT11 Sensor to capture Soil Moisture Level, Temperature, and Humidity. This data was then visualized on the LCD and ThingSpeak Platform. 

### Storing Case Study 2 Credentials for Local Running
1. **Create `case2_credentials.h` file**: 
    - Create a new file named `case2_credentials.h` in the same directory as your main sketch file.
    
2. **Define Credentials**: 
    - In `case2_credentials.h`, define the following credentials:
        - WiFi SSID (`ssid`)
        - WiFi Password (`password`)
        - ThingSpeak Write API Key (`write_apiKey`)
        - ThingSpeak Channel ID (`channelID`)
        
    ```cpp
    const char* ssid = "YourWiFiSSID";
    const char* password = "YourWiFiPassword";
    const char* write_apiKey = "YourThingSpeakAPIKey";
    const unsigned long channelID = YourThingSpeakChannelID;
    ```
    
3. **Include Credentials in the Main Sketch**:
    - Include `case2_credentials.h` at the beginning of your main sketch.
    
    ```cpp
    #include "case2_credentials.h"
    ```

## Case Study 3 Overview
In Case Study 3,  I used Adafruit to display Light Intensity captured by the LDR Sensor. Ada Fruit's MQTT broker was also used to simulate a Publish/Subscribe model.

### Storing Credentials
1. **Create `case3_credentials.h` file**: 
    - Create a new file named `case3_credentials.h` in the same directory as your main sketch file.
    
2. **Define Credentials**: 
    - In `case3_credentials.h`, define the following credentials:
    
    ```cpp
    #define WLAN_SSID       "WIFI SSID"
    #define WLAN_PASS       "WIFI Password"
    
    #define AIO_SERVER      "io.adafruit.com"
    #define AIO_SERVERPORT  1883
    #define AIO_USERNAME    "Your Adafruit's Username"
    #define AIO_KEY         "Your Adafruit's API KEY"
    
    #define myChannelNumber   YourThingSpeakChannelNumber
    const char* myWriteAPIKey  = "Your ThingSpeak WriteAPIKey";
    ```
        
3. **Include Credentials in the Main Sketch**:
    - Include `case3_credentials.h` at the beginning of your main sketch.
    
    ```cpp
    #include "case3_credentials.h"
    ```


