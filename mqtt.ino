void mqtt() 
{
if (!client.connected())
   { 
   client.connect(MQTTclient, MQTTuser, MQTTpassw);
   }
else
   {
   char stringBuffer1[6];
   dtostrf(Spannung_12V_avg, 2, 2, stringBuffer1);
   client.publish("Spannung_12V_avg",stringBuffer1);

   // char stringBuffer2[6];
   // dtostrf(a, 2, 2, stringBuffer2);
   // client.publish("a",stringBuffer2);


   // char stringBuffer3[6];
   // dtostrf(b, 2, 2, stringBuffer3);
   // client.publish("b",stringBuffer3);


   char stringBuffer4[6];
   dtostrf(avg0, 2, 2, stringBuffer4);
   client.publish("avg0",stringBuffer4);

   char stringBuffer5[6];
   dtostrf(avg1, 2, 2, stringBuffer5);
   client.publish("avg1",stringBuffer5);


   char stringBuffer6[6];
   dtostrf(avg2, 2, 2, stringBuffer6);
   client.publish("avg2",stringBuffer6);

   char stringBuffer7[6];
   dtostrf(avg3, 2, 2, stringBuffer7);
   client.publish("avg3",stringBuffer7);

   breitendiff = (((avg0 + avg2) - (avg1 + avg3)) / (avg0 + avg2*1.00)) * 100;
   hoehendiff = (((avg0 + avg1) - (avg2 + avg3)) / (avg0 + avg1*1.00)) * 100;

   char stringBuffer8[6];
   dtostrf(breitendiff, 2, 2, stringBuffer8);
   client.publish("breitendiff",stringBuffer8);

   char stringBuffer9[6];
   dtostrf(hoehendiff, 2, 2, stringBuffer9);
   client.publish("hoehendiff",stringBuffer9);

   }
}
