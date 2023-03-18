#pragma region Wifi_MQTT
void callback(char* topic, byte* payload, unsigned int length) 
{
// Serial.print("Nachricht eingetroffen [");
// Serial.print(topic);
// Serial.print("]: ");
for (int i=0;i<length;i++) 
   {
   Serial.print((char)payload[i]);
      }
        Serial.println("!"); 
// Serial.println();
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

   // Serial.print("Zeit: ");
   // Serial.println(Zeit);
   if (Zeit < 9) (Zeit = 9);
   if (Zeit > 19) (Zeit = 19);
   Tgszeit_breite = (-18 * Zeit) + 342;
   // Serial.print("Tgszeit_breite: ");
   // Serial.println(Tgszeit_breite);
   }
else if (myString == "brextanf")
   {
   ExterneAnforderung = payload[0]-48;
   Serial.println(ExterneAnforderung);
   }
else if (myString == "brpmp")
   {
   Pumpe_ext_anf_an = payload[0]-48;
   Serial.println(ExterneAnforderung);
   }


}

WiFiClient espClient;
PubSubClient client(server1, 1885, callback, espClient);
#pragma endregion Wifi_MQTT