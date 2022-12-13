
#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "*********"
#define WIFI_PASSWORD "**********"

/* 2. Define the API key */
#define API_KEY "paste the API Key here"

/* 3. Define the user Email and password that already registerd or added in your project */
#define USER_EMAIL "**********"
#define USER_PASSWORD "*********"

/* 4. If work with RTDB, define the RTDB URL */
#define DATABASE_URL "https://****-****-default-rtdb.firebaseio.com" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 6. Define the Firebase Data object */
FirebaseData fbdo;

/* 7. Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;

/* 8. Define the FirebaseConfig data for config data */
FirebaseConfig config;

unsigned long dataMillis = 0;

void setup()
{
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    /* Assign the api key (required) */
    config.api_key = API_KEY;

    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    /* Assign the RTDB URL */
    config.database_url = DATABASE_URL;

    Firebase.reconnectWiFi(true);
    fbdo.setResponseSize(4096);

    String base_path = "/UsersData/";

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

    /* Initialize the library with the Firebase authen and config */
    Firebase.begin(&config, &auth);
}

void loop()
{
    // Firebase.ready() should be called repeatedly to handle authentication tasks.

    if (millis() - dataMillis > 10000 && Firebase.ready())
    {
        dataMillis = millis();

        //Construct the topic path:
        String room1_temp_topic = "rm_1/temp";
        String user_id = auth.token.uid.c_str();
        String path = user_id+"/Things/" + room1_temp_topic;

        // Read "rm_1/temp" value:
        float room1_temp_setpoint = 0;
        if (Firebase.getString(fbdo, path + "/Value")) { 
              room1_temp_setpoint = fbdo.stringData().toFloat();
              Serial.println(room1_temp_setpoint);   
        }else Serial.println(fbdo.errorReason());

        // Write in "rm_1/temp" feedback:
        if (Firebase.setString(fbdo, path + "/Feedback", room1_temp_setpoint + 1)){
              Serial.println(room1_temp_setpoint + 1);
        }else Serial.println(fbdo.errorReason());
    }
}
