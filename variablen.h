#pragma region Variablen
typedef enum
{
   vs_init  =0,
   vs_relais,
   vs_check,
   vs_attach,
   vs_ausfuehren,
   vs_detach,
   vs_wait,
} enum_vs;

typedef enum
{
   bs_initial  =0,
   bs_wait_after_Relais_on,
   bs_batteriebetrieb,
   bs_vollgeladen,
   bs_halbeLadung,
   bs_Leer,
   bs_externeAnforderung,
   bs_drain_caps,
   bs_balance_bat_and_caps,
} enum_bs;

#define LOOP_2000ms 2000
#define LOOP_500ms 500
#define LOOP_100ms 100
#define LOOP_200ms 200
unsigned long Last_Timestamp_1 = 0;
unsigned long Last_Timestamp_2 = 0;
unsigned long Last_Timestamp_3 = 0;
unsigned long Last_Timestamp_5 = 0;

int bs_wait_after_Relais_on_cntr = 0;
#define WAIT_AFTER_RELAIS_ON_LOOPS 10


#define VOLLGELADEN 11.8
#define DREIVIERTELVOLL 10.38 
#define HALBVOLL 9.75
#define VIERTELVOLL 9.13
#define LEER 8
#define DRAIN_CAPS_WAITTIME 5
#define BALANCE_BAT_AND_CAPS_WAITTIME 5
int balance_bat_and_caps_cntr = 0;
int drain_caps_cntr = 0;
int battery_state = bs_initial;
int old_battery_state = 99;
float Spannung_12V_avg_lt1 = 0;
float Spannung_12V_avg_lt2 = 0;
int lt_counter = 0;
float laderate = 0;
int ExterneAnforderung = false; // im Nodered nach 1h auf False setzen
int ExterneAnforderungFlag = false;
int lt_init = true;
int externe_anforderung_cntr = 0;
#define EXTERNE_ANFORDERUNG_WAITTIME 3

#define WAITTIME_VERSTELLUNG  3
#define WAITTIME_HOEHE  0
char stringBuffer1[6];

int Pumpe_ext_anf_an = true;


int verstellung_state = 0;
int waitcounter_verstellung = 0;
int verstellung_state_hoehe = 0;
int waitcounter_hoehe = 0;
int Richtung_hoehe = 0;
int Richtung_breite = 0;
float Helligkeit_Korrekturwert0 = 0.94;
float Helligkeit_Korrekturwert1 = 1.04;
float Helligkeit_Korrekturwert2 = 1;
float Helligkeit_Korrekturwert3 = 1.17;
float Spannungskorrekturwert_12V = 201.75;
int Mittelwertloops = 30;
Servo breite;
Servo hoehe;
const char* TOPIC1 = "Tgszeit";
int Sollwinkel_breite_alt = 110;
int Sollwinkel_hoehe_alt = 110;
int Sollwinkel_breite = 110;
int Sollwinkel_hoehe = 110;
int Last_Sollwinkel_breite = 110;
int Last_Sollwinkel_hoehe = 110;
volatile int Tgszeit_breite = 110;
float Verstellschwelle = 1.2;
int Helligkeit_unten_rechts_avg = 0;
int Helligkeit_unten_links_avg = 0;
int Helligkeit_oben_rechts_avg = 0;
int Helligkeit_oben_links_avg = 0;
int schleifenzaehler = 0;
float Spannung_12V = 0;
float Spannung_12V_avg = 0;
int eternity_counter = 0;
int Zeit = 0;
int Zeit1 = 0;
int Zeit2 = 0;
int Pumpenrelais_an = 0;
//int lastr = 0;
//int z = 0;
int init_done=0;
int initcnt=0;
int batterie_an = 0;
float breitendiff = 0;
float hoehendiff = 0;
int verstellung_counter_breite = 0;
int verstellung_counter_hoehe = 0;
int Wifiwait = 0;

IPAddress server1(192, 168, 178, 66);
      
int status = WL_IDLE_STATUS;

char MQTTclient[] = "SolarWifi";
char MQTTstatus[] = "Solstate";
char MQTTsub1[] = "Tgszeit";
char MQTTsub2[] = "brextanf";
char MQTTsub3[] = "brpmp";

#pragma endregion Variablen
