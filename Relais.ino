// #include <Solar_Fountain.ino>
void relais() 
{
if (  Pumpenrelais_an == 0 
   && Spannung_12V_avg > 9
   && Pumpe_Inhibit == false)
   {
   digitalWrite(17, HIGH);
   Pumpenrelais_an = true;
   Serial.println("Relais an");
   client.publish(MQTTstatus, "Pumpe an");
   }
if (Pumpenrelais_an == true && Spannung_12V_avg < 7)
   {
   digitalWrite(17, LOW);
   Pumpenrelais_an = false;
   Serial.println("Relais aus");
   client.publish(MQTTstatus, "Pumpe aus");
   }
}
