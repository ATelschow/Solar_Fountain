// #include <Solar_Fountain.ino>
void mqtt() 
{
if (!client.connected())
   { 
   client.connect(MQTTclient, MQTTuser, MQTTpassw);
   }
else
   {

   dtostrf(Spannung_12V_avg, 2, 2, stringBuffer1);
   client.publish("Spannung_12V_avg",stringBuffer1);

   dtostrf(Helligkeit_unten_rechts_avg, 2, 2, stringBuffer1);
   client.publish("Helligkeit_unten_rechts_avg",stringBuffer1);

   dtostrf(Helligkeit_unten_links_avg, 2, 2, stringBuffer1);
   client.publish("Helligkeit_unten_links_avg",stringBuffer1);

   dtostrf(Helligkeit_oben_rechts_avg, 2, 2, stringBuffer1);
   client.publish("Helligkeit_oben_rechts_avg",stringBuffer1);

   dtostrf(Helligkeit_oben_links_avg, 2, 2, stringBuffer1);
   client.publish("Helligkeit_oben_links_avg",stringBuffer1);

   breitendiff = (((Helligkeit_unten_rechts_avg + Helligkeit_oben_rechts_avg) - (Helligkeit_unten_links_avg + Helligkeit_oben_links_avg)) / (Helligkeit_unten_rechts_avg + Helligkeit_oben_rechts_avg*1.00)) * 100;
   hoehendiff = (((Helligkeit_unten_rechts_avg + Helligkeit_unten_links_avg) - (Helligkeit_oben_rechts_avg + Helligkeit_oben_links_avg)) / (Helligkeit_unten_rechts_avg + Helligkeit_unten_links_avg*1.00)) * 100;

   dtostrf(breitendiff, 2, 2, stringBuffer1);
   client.publish("breitendiff",stringBuffer1);

   dtostrf(hoehendiff, 2, 2, stringBuffer1);
   client.publish("hoehendiff",stringBuffer1);

   dtostrf(laderate, 2, 2, stringBuffer1);
   client.publish("Laderate",stringBuffer1);

   }
}
