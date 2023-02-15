
void batterie()
{
// #include <Solar_Fountain.ino>
// 5 Sekunden Loop
if (batterie_an == true)
   {
   if (lt_init == true )
      {
      if (lt_counter > 9 && lt_counter < 20)
         {
         Spannung_12V_avg_lt1 = Spannung_12V_avg_lt1 + Spannung_12V_avg;
         }    
      if (lt_counter == 20)
         {
         Spannung_12V_avg_lt1 = Spannung_12V_avg_lt1/10;
         lt_init = false;
         }
      }


   if (lt_counter >=120 && lt_counter <130 )
      {
      Spannung_12V_avg_lt2 = Spannung_12V_avg_lt2 + Spannung_12V_avg;
      }
   lt_counter++;
   if (lt_counter == 130)
      {
      Spannung_12V_avg_lt2 = Spannung_12V_avg_lt2/10;
      laderate = Spannung_12V_avg_lt2 / Spannung_12V_avg_lt1;
      Spannung_12V_avg_lt1 = Spannung_12V_avg_lt2;
      Spannung_12V_avg_lt2 = 0;
      lt_counter = 0;
      }
   }
else
   {
   Spannung_12V_avg_lt1=0;
   Spannung_12V_avg_lt2=0;
   lt_init= true;
   laderate = 1;
   lt_counter=0;
   }



if (battery_state == bs_initial)
   {
   // check next state
   if (Pumpenrelais_an == true)
      {
      batterie_an = true;
      battery_state = bs_batteriebetrieb;
      }
   if (  ( Pumpe_Inhibit == true )
      && ( Spannung_12V_avg > DREIVIERTELVOLL ) )
      {
      batterie_an = true;
      battery_state = bs_balance_bat_and_caps;
      }
   }
else if (battery_state == bs_batteriebetrieb)
   {
   if (Spannung_12V_avg > VOLLGELADEN)
      {
      batterie_an = false;
      battery_state = bs_vollgeladen;
      }
   else if (   (Spannung_12V_avg < HALBVOLL)
         //   &&  (laderate < 1) 
           &&  (ExterneAnforderung == false) )
      {
      batterie_an = false;
      battery_state = bs_halbeLadung;
      }
   else if (Spannung_12V_avg < LEER)
      {
      batterie_an = false;
      battery_state = bs_Leer;
      }
   }
else if (battery_state == bs_vollgeladen)
   {
   if ( Spannung_12V_avg < HALBVOLL ) 
      {
      batterie_an = true;
      battery_state = bs_batteriebetrieb;
      }
   }
else if (battery_state == bs_halbeLadung)
   {
   if ( (Spannung_12V_avg > DREIVIERTELVOLL) && (Pumpenrelais_an == true) )
      {
      batterie_an = true;
      battery_state = bs_batteriebetrieb;
      }
   }
else if (battery_state == bs_Leer)
   {
   if ( Spannung_12V_avg > DREIVIERTELVOLL )
      {
      batterie_an = true;
      battery_state = bs_batteriebetrieb;
      }
   }
else if (battery_state == bs_drain_caps)
   {
   if ( drain_caps_cntr >= DRAIN_CAPS_WAITTIME)
      {
      drain_caps_cntr=0;
      battery_state = bs_initial;
      }
   else
      {
      drain_caps_cntr++;
      }
   }
else if (battery_state == bs_externeAnforderung)
   {
   if (externe_anforderung_cntr >= EXTERNE_ANFORDERUNG_WAITTIME)
      {
      externe_anforderung_cntr=0;
      Pumpenrelais_an = true;
      digitalWrite(17, HIGH);
      battery_state = bs_batteriebetrieb;
      }
   else
      {
      externe_anforderung_cntr++;
      }
   }
else if (battery_state == bs_balance_bat_and_caps)
   {
   if ( balance_bat_and_caps_cntr >= BALANCE_BAT_AND_CAPS_WAITTIME)
      {
      balance_bat_and_caps_cntr=0;
      battery_state = bs_batteriebetrieb;
      }
   else
      {
      balance_bat_and_caps_cntr++;
      }
   }



if ( ExterneAnforderung == true && ExterneAnforderungFlag == false)
   {
   batterie_an = true;
   // Pumpenrelais_an = true;
   // digitalWrite(17, HIGH);
   ExterneAnforderungFlag = true;
   battery_state = bs_externeAnforderung;
   }

if ( ExterneAnforderung == false && ExterneAnforderungFlag == true)
   {
   batterie_an = false;
   ExterneAnforderungFlag = false;
   battery_state = bs_drain_caps;
   }
if (batterie_an == true)
   {
   digitalWrite(16, HIGH);
   }
else
   {
   digitalWrite(16, LOW);
   }

Serial.print(battery_state);
Serial.print(" : ");
Serial.print(Spannung_12V_avg);
Serial.print(" : ");
Serial.print(Spannung_12V_avg_lt1);
Serial.print(" : ");
Serial.print(Spannung_12V_avg_lt2);
Serial.print(" : ");
Serial.print(laderate);
Serial.println("\\");

if (battery_state != old_battery_state) 
   {
   old_battery_state = battery_state;
   dtostrf(battery_state, 2, 2, stringBuffer1);
   client.publish("battery_state",stringBuffer1);
   switch (battery_state) 
      {
      case 0: client.publish(MQTTstatus, "bs_initial");break;
      case 1: client.publish(MQTTstatus, "bs_batteriebetrieb");break;
      case 2: client.publish(MQTTstatus, "bs_vollgeladen");break;
      case 3: client.publish(MQTTstatus, "bs_halbeLadung");break;
      case 4: client.publish(MQTTstatus, "bs_Leer");break;
      case 5: client.publish(MQTTstatus, "bs_externeAnforderung");break;
      case 6: client.publish(MQTTstatus, "bs_drain_caps");break;
      default: client.publish(MQTTstatus, "Error");break;
      }
   }
}
