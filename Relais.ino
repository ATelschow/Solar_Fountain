void relais() 
{
if (Relaisstatus == 0 && Spannung_12V_avg > 11)
   {
   digitalWrite(17, HIGH);
   Relaisstatus = 1;
   Serial.println("Relais an");
   client.publish(MQTTstatus, "Relais an");
   }
if (Relaisstatus == 1 && Spannung_12V_avg < 8)
   {
   digitalWrite(17, LOW);
   Relaisstatus = 0;
   Serial.println("Relais aus");
   client.publish(MQTTstatus, "Relais aus");
   }
}
