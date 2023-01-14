void verstellung() 
{
if (init_done==0)
   {
   initcnt++;
   if (initcnt > 10)
      {
      Serial.println("Jetzt kopieren");
      Sollwinkel_breite = Tgszeit_breite;
      //a = (-18 * Zeit) + 343;
      Serial.println(Sollwinkel_breite);
      Serial.println("fertig kopiert");
      char stringBuffer2[6];
      dtostrf(Sollwinkel_breite, 2, 2, stringBuffer2);
      client.publish(MQTTstatus,stringBuffer2);
      init_done = 1;
      }
   }
else if (Spannung_12V_avg > 8 || verstellung_counter > 0)
   {
   verstellung_counter++;
   if (verstellung_counter == 1)
      {
      digitalWrite(33, HIGH); // Servorelais an
      hoehe.attach(22); 
      breite.attach(23); 
      }
   else if (verstellung_counter == 4)
      {
      // hoehe.attach(22); 
      // breite.attach(23); 
      //breite
      if (((avg0 + avg2) * Verstellschwelle) < (avg1 + avg3))
         {
         Serial.println("nach rechts drehen");
         if (Sollwinkel_breite > 1) 
            {
            Sollwinkel_breite--;
            Sollwinkel_breite--;
            breite.write(Sollwinkel_breite);
            }
         }
      else if (((avg1 + avg3) * Verstellschwelle) < (avg0 + avg2))
         {
         Serial.println("nach links drehen"); 
         if (Sollwinkel_breite < 180) 
           {
           Sollwinkel_breite++;
           breite.write(Sollwinkel_breite);
           }
         }
      else
         {
         Serial.println("nichts"); 
         }

      //höhe
      if (((avg0 + avg1) * Verstellschwelle) < (avg2 + avg3))
         {
         Serial.println("nach unten");
         if (Sollwinkel_hoehe < 150) 
            {
            Sollwinkel_hoehe++;
            hoehe.write(Sollwinkel_hoehe);
            }
         }  
      else if (((avg2 + avg3) * Verstellschwelle) < (avg0 + avg1))
         {
         Serial.println("nach oben"); 
         if (Sollwinkel_hoehe > 60) 
            {
            Sollwinkel_hoehe--;
            hoehe.write(Sollwinkel_hoehe);
            }
         }
      else
         {
         Serial.println("nichts"); 
         }

      // hoehe.detach();
      // breite.detach();    
      char stringBuffer2[6];
      dtostrf(Sollwinkel_breite, 2, 2, stringBuffer2);
      client.publish("Sollwinkel_breite",stringBuffer2);

      char stringBuffer3[6];
      dtostrf(Sollwinkel_hoehe, 2, 2, stringBuffer3);
      client.publish("Sollwinkel_hoehe",stringBuffer3);

      Serial.println(Sollwinkel_breite);
      Serial.println(Sollwinkel_hoehe);
      } 
   else if (verstellung_counter == 5)
      {
      hoehe.detach();
      breite.detach();     
      verstellung_counter = 0;
      }
   }
}