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
      client.subscribe(MQTTsub3);
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


void wifirec_setup()
{
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
}


void wifirec() 
{
if (WiFi.status() != WL_CONNECTED) 
   {
   Serial.print("Attempting to connect to WPA SSID: ");
   Serial.println(ssid);
   // Connect to WPA/WPA2 network
   WiFi.begin(ssid, pass);
   }
}
