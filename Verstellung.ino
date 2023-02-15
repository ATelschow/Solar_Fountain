// #include <Solar_Fountain.ino>
void verstellung()
{
// Statemachine breite
if (verstellung_state_breite == vs_init)
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
      verstellung_state_breite = vs_relais;
      }
   }
else if (verstellung_state_breite == vs_relais)
   {
   if (Spannung_12V_avg > 8 )
      {
      digitalWrite(33, HIGH); // Servorelais an
      verstellung_state_hoehe = vs_check;      
      verstellung_state_breite = vs_check;
      }
   }
else if (verstellung_state_breite == vs_check)
   {
   if (Sollwinkel_breite_alt == Sollwinkel_breite)
      {
      if (((avg0 + avg2) * Verstellschwelle) < (avg1 + avg3))
         {
         // Serial.println("nach rechts drehen");
         if (Sollwinkel_breite > 1) 
            {
            Sollwinkel_breite--;
            Sollwinkel_breite--;
            // breite.write(Sollwinkel_breite);
            }
         }
      else if (((avg1 + avg3) * Verstellschwelle) < (avg0 + avg2))
         {
         Serial.println("nach links drehen"); 
         if (Sollwinkel_breite < 180) 
            {
            Sollwinkel_breite++;
            // breite.write(Sollwinkel_breite);
            }
         }
      }
   else if (Sollwinkel_breite_alt != Sollwinkel_breite)
      {
      verstellung_state_breite = vs_attach;
      }
   }
else if (verstellung_state_breite == vs_attach)
   {
   breite.attach(23);
   verstellung_state_breite = vs_ausfuehren;
   } 
else if (verstellung_state_breite == vs_ausfuehren)
   {
   breite.write(Sollwinkel_breite);
   verstellung_state_breite = vs_detach;
   } 
else if (verstellung_state_breite == vs_detach)
   {
   breite.detach(); 
   Sollwinkel_breite_alt = Sollwinkel_breite;
   dtostrf(Sollwinkel_breite, 2, 2, stringBuffer1);
   client.publish("Sollwinkel_breite",stringBuffer1);
   verstellung_state_breite = vs_wait;
   } 
else if (verstellung_state_breite == vs_wait)
   {
   if (waitcounter_breite >= WAITTIME_BREITE)
      {
      waitcounter_breite = 0;
      verstellung_state_breite = vs_check;
      }
   else
      {
      waitcounter_breite++;
      }
   }

// Statemachine breite--------------------------------------------------------

if (verstellung_state_hoehe == vs_init)
   {
   //do nothing
   }
else if (verstellung_state_hoehe == vs_check)
   {
   if (Sollwinkel_hoehe_alt == Sollwinkel_hoehe)
      {
      if (((avg0 + avg1) * Verstellschwelle) < (avg2 + avg3))
         {
         // Serial.println("nach unten");
         if (Sollwinkel_hoehe < 150) 
            {
            Sollwinkel_hoehe++;
            }  
         }
      else if (((avg2 + avg3) * Verstellschwelle) < (avg0 + avg1))
         {
         // Serial.println("nach oben"); 
         if (Sollwinkel_hoehe > 60) 
            {
            Sollwinkel_hoehe--;
            }
         }
      }
   else if (Sollwinkel_hoehe_alt != Sollwinkel_hoehe)
      {
      verstellung_state_hoehe = vs_attach;
      }
   }
else if (verstellung_state_hoehe == vs_attach)
   {
   hoehe.attach(22);
   verstellung_state_hoehe = vs_ausfuehren;
   } 
else if (verstellung_state_hoehe == vs_ausfuehren)
   {
   hoehe.write(Sollwinkel_hoehe);
   verstellung_state_hoehe = vs_detach;
   } 
else if (verstellung_state_hoehe == vs_detach)
   {
   hoehe.detach(); 
   Sollwinkel_hoehe_alt = Sollwinkel_hoehe;
   dtostrf(Sollwinkel_hoehe, 2, 2, stringBuffer1);
   client.publish("Sollwinkel_hoehe",stringBuffer1);
   verstellung_state_hoehe = vs_wait;
   } 
else if (verstellung_state_hoehe == vs_wait)
   {
   if (waitcounter_hoehe >= WAITTIME_HOEHE)
      {
      waitcounter_hoehe = 0;
      verstellung_state_hoehe = vs_check;
      }
   else
      {
      waitcounter_hoehe++;
      }
   }
}
