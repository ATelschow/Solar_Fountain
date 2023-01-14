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
