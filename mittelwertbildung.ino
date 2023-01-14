void mittelwertbildung()
{
avg0 = 0;
avg1 = 0;
avg2 = 0;
avg3 = 0;
Spannung_12V_avg = 0;
while (schleifenzaehler < Mittelwertloops)
   {
   int value0 = analogRead(36);
   avg0 = avg0 + value0;
   int value1 = analogRead(39);
   avg1 = avg1 + value1;
   int value2 = analogRead(34);
   avg2 = avg2 + value2;
   int value3 = analogRead(35);
   avg3 = avg3 + value3;
   Spannung_12V = analogRead(32);
   Spannung_12V_avg = Spannung_12V_avg + Spannung_12V;
   schleifenzaehler++;
   }
schleifenzaehler = 0;
avg0= avg0 / Mittelwertloops * Helligkeit_Korrekturwert0;
avg1= avg1 / Mittelwertloops * Helligkeit_Korrekturwert1;
avg2= avg2 / Mittelwertloops * Helligkeit_Korrekturwert2;
avg3= avg3 / Mittelwertloops * Helligkeit_Korrekturwert3;
Spannung_12V_avg= Spannung_12V_avg / Mittelwertloops / Spannungskorrekturwert_12V ;

// Serial.println("Analog Value :");
// Serial.println(avg0);
// Serial.println(avg1);
// Serial.println(avg2); 
// Serial.println(avg3);
// Serial.println(Spannung_12V_avg);
}
