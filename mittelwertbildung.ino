void mittelwertbildung()
{
Helligkeit_unten_rechts_avg = 0;
Helligkeit_unten_links_avg = 0;
Helligkeit_oben_rechts_avg = 0;
Helligkeit_oben_links_avg = 0;
Spannung_12V_avg = 0;
while (schleifenzaehler < Mittelwertloops)
   {
   int value0 = analogRead(36);
   Helligkeit_unten_rechts_avg = Helligkeit_unten_rechts_avg + value0;
   int value1 = analogRead(39);
   Helligkeit_unten_links_avg = Helligkeit_unten_links_avg + value1;
   int value2 = analogRead(34);
   Helligkeit_oben_rechts_avg = Helligkeit_oben_rechts_avg + value2;
   int value3 = analogRead(35);
   Helligkeit_oben_links_avg = Helligkeit_oben_links_avg + value3;
   Spannung_12V = analogRead(32);
   Spannung_12V_avg = Spannung_12V_avg + Spannung_12V;
   schleifenzaehler++;
   }
schleifenzaehler = 0;
Helligkeit_unten_rechts_avg= Helligkeit_unten_rechts_avg / Mittelwertloops * Helligkeit_Korrekturwert0;
Helligkeit_unten_links_avg= Helligkeit_unten_links_avg / Mittelwertloops * Helligkeit_Korrekturwert1;
Helligkeit_oben_rechts_avg= Helligkeit_oben_rechts_avg / Mittelwertloops * Helligkeit_Korrekturwert2;
Helligkeit_oben_links_avg= Helligkeit_oben_links_avg / Mittelwertloops * Helligkeit_Korrekturwert3;
Spannung_12V_avg= Spannung_12V_avg / Mittelwertloops / Spannungskorrekturwert_12V ;

// Serial.println("Analog Value :");
// Serial.println(Helligkeit_unten_rechts_avg);
// Serial.println(Helligkeit_unten_links_avg);
// Serial.println(Helligkeit_oben_rechts_avg); 
// Serial.println(Helligkeit_oben_links_avg);
// Serial.println(Spannung_12V_avg);
}
