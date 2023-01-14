#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h> 
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <FastLED_NeoMatrix.h>

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

#pragma region Variablen
float Helligkeit_Korrekturwert0 = 0.94;
float Helligkeit_Korrekturwert1 = 1.04;
float Helligkeit_Korrekturwert2 = 1;
float Helligkeit_Korrekturwert3 = 1.17;
float Spannungskorrekturwert_12V = 201.75;
int Mittelwertloops = 30;
Servo breite;
Servo hoehe;
const char* TOPIC1 = "Tgszeit";
int Sollwinkel_breite = 110;
int Sollwinkel_hoehe = 110;
volatile int Tgszeit_breite = 110;
float Verstellschwelle = 1.2;
int avg0 = 0;
int avg1 = 0;
int avg2 = 0;
int avg3 = 0;
int schleifenzaehler = 0;
float Spannung_12V = 0;
float Spannung_12V_avg = 0;
int eternity_counter = 0;
int Zeit = 0;
int Zeit1 = 0;
int Zeit2 = 0;
int Relaisstatus = 0;
//int lastr = 0;
//int z = 0;
int init_done=0;
int initcnt=0;
int batterie_an = 0;
float breitendiff = 0;
float hoehendiff = 0;
int verstellung_counter = 0;

int Wifiwait = 0;

IPAddress server1(192, 168, 178, 66);
      
int status = WL_IDLE_STATUS;

char MQTTclient[] = "SolarWifi";
;
char MQTTstatus[] = "Solstate";
char MQTTsub1[] = "Tgszeit";
char MQTTsub2[] = "hoehe";

#pragma endregion Variablen

#pragma region OTA
const char* host = "esp32";



WebServer server(80);

/*
 * Login page
 */

const char* loginIndex =
 "<form name='loginForm'>"
    "<table width='20%' bgcolor='A09F9F' align='center'>"
        "<tr>"
            "<td colspan=2>"
                "<center><font size=4><b>ESP32 Login Page</b></font></center>"
                "<br>"
            "</td>"
            "<br>"
            "<br>"
        "</tr>"
        "<tr>"
             "<td>Username:</td>"
             "<td><input type='text' size=25 name='userid'><br></td>"
        "</tr>"
        "<br>"
        "<br>"
        "<tr>"
            "<td>Password:</td>"
            "<td><input type='Password' size=25 name='pwd'><br></td>"
            "<br>"
            "<br>"
        "</tr>"
        "<tr>"
            "<td><input type='submit' onclick='check(this.form)' value='Login'></td>"
        "</tr>"
    "</table>"
"</form>"
"<script>"
    "function check(form)"
    "{"
    "if(form.userid.value==OTAuser && form.pwd.value==OTApass)"
    "{"
    "window.open('/serverIndex')"
    "}"
    "else"
    "{"
    " alert('Error Password or Username')/*displays error message*/"
    "}"
    "}"
"</script>";

/*
 * Server Index Page
 */

const char* serverIndex =
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
"<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
   "<input type='file' name='update'>"
        "<input type='submit' value='Update'>"
    "</form>"
 "<div id='prg'>progress: 0%</div>"
 "<script>"
  "$('form').submit(function(e){"
  "e.preventDefault();"
  "var form = $('#upload_form')[0];"
  "var data = new FormData(form);"
  " $.ajax({"
  "url: '/update',"
  "type: 'POST',"
  "data: data,"
  "contentType: false,"
  "processData:false,"
  "xhr: function() {"
  "var xhr = new window.XMLHttpRequest();"
  "xhr.upload.addEventListener('progress', function(evt) {"
  "if (evt.lengthComputable) {"
  "var per = evt.loaded / evt.total;"
  "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
  "}"
  "}, false);"
  "return xhr;"
  "},"
  "success:function(d, s) {"
  "console.log('success!')"
 "},"
 "error: function (a, b, c) {"
 "}"
 "});"
 "});"
 "</script>";

 #pragma endregion OTA

#pragma region Wifi_MQTT
void callback(char* topic, byte* payload, unsigned int length) 
{
Serial.print("Nachricht eingetroffen [");
Serial.print(topic);
Serial.print("]: ");
for (int i=0;i<length;i++) 
   {
   Serial.print((char)payload[i]);
      }
Serial.println();
String myString = String(topic); 
if (myString == "Tgszeit")
   {
   // Zeit = (((char)payload[0])-48) * 10;
   // Zeit = Zeit + (((char)payload[1])-48);
   Zeit1 = payload[0] - 0;
   Zeit1 = (Zeit1-48)*10;
   Zeit2 = payload[1] - 0;
   Zeit2 = (Zeit2-48);
   Zeit = Zeit1 + Zeit2;

   Serial.print("Zeit: ");
   Serial.println(Zeit);
   if (Zeit < 9) (Zeit = 9);
   if (Zeit > 19) (Zeit = 19);
   Tgszeit_breite = (-18 * Zeit) + 342;
   Serial.print("Tgszeit_breite: ");
   Serial.println(Tgszeit_breite);
   }
}

WiFiClient espClient;
PubSubClient client(server1, 1885, callback, espClient);
#pragma endregion Wifi_MQTT

void reconnect() 
{
// MQTT verbinden
if (!client.connected()) 
   {
   Serial.print("Versuch des MQTT Verbindungsaufbaus...");
   client.connect(MQTTclient, MQTTuser, MQTTpassw);
   //Verbindungsversuch:
   if (client.connect(MQTTclient)) 
      {
      Serial.println("Erfolgreich verbunden!");
      // Nun versendet der Arduino eine Nachricht in outTopic ...
      //send IPadress via MQTT
      String ipaddress = WiFi.localIP().toString();
      char ipchar[ipaddress.length()+1];
      ipaddress.toCharArray(ipchar,ipaddress.length()+1);
      client.publish(MQTTstatus, ipchar);
      // und meldet sich bei inTopic für eingehende Nachrichten an:
      client.subscribe(MQTTsub1);
      client.subscribe(MQTTsub2);
      client.publish(MQTTstatus, "Tageszeit");
      } 
   else 
      { // Im Fehlerfall => Fehlermeldung und neuer Versuch
      Serial.print("Fehler, rc=");
      Serial.print(client.state());
      // Serial.println(" Nächster Versuch in 5 Sekunden");
      // 5 Sekunden Pause vor dem nächsten Versuch
      // delay(5000);
      }
   }
}

void setup() 
{  
Serial.begin(115200);

#pragma region Connect_Wifi
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, pass);
while (Wifiwait < 10)
   {
   if  (WiFi.status() != WL_CONNECTED) 
      {
      delay(500);
      Serial.print(".");
      Wifiwait++;
      }
   else
      {
      Wifiwait++;     
      }
   }
Serial.println("");
Serial.println("WiFi connected.");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
#pragma endregion Connect_Wifi

#pragma region OTAsetup  
  /*use mdns for host name resolution*/
  if (!MDNS.begin(host)) { //http://esp32.local
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  /*return index page which is stored in serverIndex */
  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", loginIndex);
  });
  server.on("/serverIndex", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });
  /*handling uploading firmware file */
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });
  server.begin();
#pragma endregion OTAsetup

#pragma region set_Pins
pinMode(36, INPUT);
pinMode(39, INPUT);
pinMode(34, INPUT);
pinMode(35, INPUT);
pinMode(17, OUTPUT);
pinMode(22, OUTPUT);
pinMode(23, OUTPUT);
pinMode(33, OUTPUT);
pinMode(12, OUTPUT);
#pragma endregion set_Pins

#pragma region Taskcreation
xTaskCreatePinnedToCore(
                  Task1code,   /* Task function. */
                  "Task1",     /* name of task. */
                  10000,       /* Stack size of task */
                  NULL,        /* parameter of the task */
                  1,           /* priority of the task */
                  &Task1,      /* Task handle to keep track of created task */
                  0);          /* pin task to core 0 */                  
//delay(500); 

//create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
xTaskCreatePinnedToCore(
                  Task2code,   /* Task function. */
                  "Task2",     /* name of task. */
                  10000,       /* Stack size of task */
                  NULL,        /* parameter of the task */
                  1,           /* priority of the task */
                  &Task2,      /* Task handle to keep track of created task */
                  1);          /* pin task to core 1 */
//  delay(500); 
#pragma endregion Taskcreation

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


EVERY_N_MILLISECONDS(100) 
  {
  wifirec();
  reconnect();
  client.loop();
  server.handleClient();  
  verstellung();
  relais();
  }

EVERY_N_MILLISECONDS(500) 
  {
  mittelwertbildung();
  Serial.print("Sollwinkel_breite=");
  Serial.println(Sollwinkel_breite);

  }

EVERY_N_SECONDS(2) 
  {
  mqtt();
  batterie();
  }

 
}



 
