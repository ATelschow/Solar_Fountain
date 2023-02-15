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

   dtostrf(avg0, 2, 2, stringBuffer1);
   client.publish("avg0",stringBuffer1);

   dtostrf(avg1, 2, 2, stringBuffer1);
   client.publish("avg1",stringBuffer1);

   dtostrf(avg2, 2, 2, stringBuffer1);
   client.publish("avg2",stringBuffer1);

   dtostrf(avg3, 2, 2, stringBuffer1);
   client.publish("avg3",stringBuffer1);

   breitendiff = (((avg0 + avg2) - (avg1 + avg3)) / (avg0 + avg2*1.00)) * 100;
   hoehendiff = (((avg0 + avg1) - (avg2 + avg3)) / (avg0 + avg1*1.00)) * 100;

   dtostrf(breitendiff, 2, 2, stringBuffer1);
   client.publish("breitendiff",stringBuffer1);

   dtostrf(hoehendiff, 2, 2, stringBuffer1);
   client.publish("hoehendiff",stringBuffer1);

   dtostrf(laderate, 2, 2, stringBuffer1);
   client.publish("Laderate",stringBuffer1);

   }
}
