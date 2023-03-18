/*
Baterrierelaisüberbrückung

Helligkeitssensoren feintunen
HElligkeitssensornamen austauschen


*/
#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h> 
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>

TaskHandle_t Task1;
TaskHandle_t Task2;

#define solarfountain TRUE

#include <inserts.h>
// inserts.h contains:
// #if defined(solarfountain)
// char MQTTuser[] = "Your_MQTT_Username";
// char MQTTpassw[] = "Your_MQTT_Password"
// char ssid[] = "Your_WIFI_SSID";          
// char pass[] = "Your_Wifi_Password";     
// char OTAuser[] ="Your_OTA_Username";
// char OTApass[] = "Your_OTA_Password";  
// #endif

#include "variablen.h"
#include "ota.h"
#include "wifi_mqtt.h"

void setup() 
{  
Serial.begin(115200);
wifirec_setup();
ota_setup();
io_setup();
taskcreation_setup();

//Start MQTT
client.setServer(server1, 1885); // Adresse des MQTT-Brokers
client.setCallback(callback);   // Handler für eingehende Nachrichten
reconnect();
}

void Task1code( void * pvParameters )
  {
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());
  for(;;)
    {
    delay(100);
    }
  }
void Task2code( void * pvParameters )
  {
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());
  for(;;)
    {
    delay(100);
    }
  }

void loop() 
{
abend();

// 100ms Loop
if ( ( millis() - Last_Timestamp_5) > LOOP_100ms)
   {
   wifirec();
   reconnect();
   client.loop();
   server.handleClient();  
   relais();
   verstellung();
   Last_Timestamp_5 = millis();
   }

// 200ms Loop
if ( ( millis() - Last_Timestamp_3) > LOOP_200ms)
   {

   // Serial.println("LOOP");
   Last_Timestamp_3 = millis();
   }

// 500ms Loop
if ( ( millis() - Last_Timestamp_1) > LOOP_500ms)
   {
   mittelwertbildung();
   Last_Timestamp_1 = millis();
   }

// 2000ms Loop
if ( ( millis() - Last_Timestamp_2) > LOOP_2000ms)
   {
   mqtt();
   batterie();
   Last_Timestamp_2 = millis();
   }

}


 
