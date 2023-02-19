// #include <Solar_Fountain.ino>
void verstellung()
{
// Statemachine breite
if (verstellung_state == vs_init)
   {
   initcnt++;
   if (initcnt > 10)
      {
      Serial.println("Jetzt kopieren");
      Sollwinkel_breite = Tgszeit_breite;
      //a = (-18 * Zeit) + 343;
      Serial.println(Sollwinkel_breite);
      Serial.println("fertig kopiert");
      dtostrf(Sollwinkel_breite, 2, 2, stringBuffer1);
      client.publish("Sollwinkel_breite",stringBuffer1);
      verstellung_state = vs_relais;
      }
   }
else if (verstellung_state == vs_relais)
   {
   if (Spannung_12V_avg > 8 )
      {
      digitalWrite(33, HIGH); // Servorelais an
      verstellung_state = vs_check;
      }
   }
else if (verstellung_state == vs_check)
   {
   if (((Helligkeit_unten_rechts_avg + Helligkeit_oben_rechts_avg) * Verstellschwelle) < (Helligkeit_unten_links_avg + Helligkeit_oben_links_avg))
   {
   // Serial.println("nach rechts drehen");
   if (Sollwinkel_breite > 1) 
      {
      Sollwinkel_breite--;
      Sollwinkel_breite--;
      // breite.write(Sollwinkel_breite);
      }
   }
   else if (((Helligkeit_unten_links_avg + Helligkeit_oben_links_avg) * Verstellschwelle) < (Helligkeit_unten_rechts_avg + Helligkeit_oben_rechts_avg))
   {
   Serial.println("nach links drehen"); 
   if (Sollwinkel_breite < 180) 
      {
      Sollwinkel_breite++;
      // breite.write(Sollwinkel_breite);
      }
   }
   if (((Helligkeit_unten_rechts_avg + Helligkeit_unten_links_avg) * Verstellschwelle) < (Helligkeit_oben_rechts_avg + Helligkeit_oben_links_avg))
   {
   // Serial.println("nach unten");
   if (Sollwinkel_hoehe < 150) 
      {
      Sollwinkel_hoehe++;
      }  
   }
   else if (((Helligkeit_oben_rechts_avg + Helligkeit_oben_links_avg) * Verstellschwelle) < (Helligkeit_unten_rechts_avg + Helligkeit_unten_links_avg))
   {
   // Serial.println("nach oben"); 
   if (Sollwinkel_hoehe > 60) 
      {
      Sollwinkel_hoehe--;
      }
   }
   
   if (  (Sollwinkel_breite_alt != Sollwinkel_breite)
      || (Sollwinkel_hoehe_alt != Sollwinkel_hoehe) )
      {
      verstellung_state = vs_attach;
      }
   }
else if (verstellung_state == vs_attach)
   {
   breite.attach(23);
   hoehe.attach(22);
   verstellung_state = vs_wait;
   } 
else if (verstellung_state == vs_ausfuehren)
   {
   if (Sollwinkel_breite_alt != Sollwinkel_breite)
      {
      breite.write(Sollwinkel_breite);
      }
   if (Sollwinkel_hoehe_alt != Sollwinkel_hoehe)
      {
      hoehe.write(Sollwinkel_hoehe);
      }   
      breite.detach(); 
   hoehe.detach();
   verstellung_state = vs_detach;
   } 
else if (verstellung_state == vs_detach)
   {
   // breite.detach(); 
   // hoehe.detach();
   Sollwinkel_breite_alt = Sollwinkel_breite;
   dtostrf(Sollwinkel_breite, 2, 2, stringBuffer1);
   client.publish("Sollwinkel_breite",stringBuffer1);
   Sollwinkel_hoehe_alt = Sollwinkel_hoehe;
   dtostrf(Sollwinkel_hoehe, 2, 2, stringBuffer1);
   client.publish("Sollwinkel_hoehe",stringBuffer1);
   verstellung_state = vs_check;
   } 
else if (verstellung_state == vs_wait)
   {
   if (waitcounter_verstellung >= WAITTIME_VERSTELLUNG)
      {
      waitcounter_verstellung = 0;
      verstellung_state = vs_ausfuehren;
      }
   else
      {
      waitcounter_verstellung++;
      }
   }
}

