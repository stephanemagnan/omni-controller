
boolean printout = false;

// INITIALIZE STATE FLAGS
byte fa_state = 0;
byte lat_state = 0;
byte rot_state = 0;

byte fa_last_state = 0;
byte lat_last_state = 0;
byte rot_last_state = 0;

byte fa_flag = 0;
byte lat_flag = 0;
byte rot_flag = 0;

// INITIALIZE TIME VARIABLES
unsigned long fa_rise=0;
unsigned long lat_rise=0;
unsigned long rot_rise=0;

unsigned long fa_fall=0;
unsigned long lat_fall=0;
unsigned long rot_fall=0;

unsigned long fa_pulse=1500;
unsigned long lat_pulse=1500;
unsigned long rot_pulse=1500;

unsigned long m1_pulse=1500;
unsigned long m2_pulse=1500;
unsigned long m3_pulse=1500;
unsigned long m4_pulse=1500;

unsigned long period=14000;
unsigned long this_width=0;
unsigned long last_width=0;
unsigned long this_time=0;
unsigned long last_time=0;


// PIN DEFINITIONS 
int fa_pin=2; 
int lat_pin=3; 
int rot_pin=4;

int m1_pin = 5;
int m2_pin = 6;
int m3_pin = 7;
int m4_pin = 8;

void setup(){
 Serial.begin(9600);
 // INPUT PINS
 pinMode(fa_pin, INPUT);
 pinMode(lat_pin, INPUT);
 pinMode(rot_pin, INPUT);  
 
 // OUTPUT PINS
 pinMode(m1_pin, OUTPUT);  
 pinMode(m2_pin, OUTPUT);  
 pinMode(m3_pin, OUTPUT);  
 pinMode(m4_pin, OUTPUT);  

 last_time=micros();
}

void loop(){

//GET CURRENT TIME
this_time=micros();
this_width=this_time-fa_rise; 

//GET CURRENT STATES
fa_state=digitalRead(fa_pin);
lat_state=digitalRead(lat_pin);
rot_state=digitalRead(rot_pin);

//SEARCH FOR RISING
if (fa_state==1 && fa_last_state == 0){
 fa_rise=this_time;
 digitalWrite(m1_pin, HIGH);
 digitalWrite(m2_pin, HIGH);
 digitalWrite(m3_pin, HIGH);
 digitalWrite(m4_pin, HIGH);
}
if (lat_state==1 && lat_last_state == 0){
 lat_rise=this_time; 
}

if (rot_state==1 && rot_last_state == 0){
 rot_rise=this_time; 
}

//SEARCH FOR FALLING
if (fa_state==0 && fa_last_state == 1){
 fa_fall=this_time;
 fa_flag=1;
}
if (lat_state==0 && lat_last_state == 1){
 lat_fall=this_time;
 lat_flag=1;
}
if (rot_state==0 && rot_last_state == 1){
 rot_fall=this_time;
 rot_flag=1;
}

//STOP PULSE WRITE
if(last_width<m1_pulse && this_width>=m1_pulse){
 digitalWrite(m1_pin, LOW);  
}
if(last_width<m2_pulse && this_width>=m2_pulse){
 digitalWrite(m2_pin, LOW);  
}
if(last_width<m3_pulse && this_width>=m3_pulse){
 digitalWrite(m3_pin, LOW);  
}
if(last_width<m4_pulse && this_width>=m4_pulse){
 digitalWrite(m4_pin, LOW);  
}

// HAVE ALL INPUTS RETURNED TO ZERO
if(fa_flag==1 && lat_flag==1 && rot_flag ==1){
 fa_flag=0;
 lat_flag=0;
 rot_flag=0;
 
 fa_pulse=fa_fall-fa_rise;
 lat_pulse=lat_fall-lat_rise;
 rot_pulse=rot_fall-rot_rise;

 float fa_norm=(fa_pulse-1500)/500;
 float lat_norm=(lat_pulse-1500)/500;
 float rot_norm=(rot_pulse-1500)/500;

 float m1_norm=1*fa_norm+1*lat_norm+1*rot_norm;
 float m2_norm=1*fa_norm-1*lat_norm+1*rot_norm;
 float m3_norm=-1*fa_norm-1*lat_norm+1*rot_norm;
 float m4_norm=-1*fa_norm+1*lat_norm+1*rot_norm;

 float m_max = max(max(m1_norm,m2_norm),max(m3_norm,m4_norm));
 if(m_max>1){
   m1_norm=m1_norm/m_max;
   m2_norm=m2_norm/m_max;
   m3_norm=m3_norm/m_max;
   m4_norm=m4_norm/m_max;
 }
 m1_pulse=(unsigned long)(m1_norm*500+1500);
 m2_pulse=(unsigned long)(m2_norm*500+1500);
 m3_pulse=(unsigned long)(m3_norm*500+1500);
 m4_pulse=(unsigned long)(m4_norm*500+1500);  

  

 // PRINT THE CURRENT STATUS TO MONITOR
  if (printout){
   Serial.print("Fore/Aft:");
   Serial.print(fa_pulse);
   Serial.print(",");
   Serial.print("Lateral:");
   Serial.print(lat_pulse);
   Serial.print(",");
   Serial.print("Rotation:");
   Serial.print(rot_pulse);
   Serial.print("M1:");
   Serial.print(m1_pulse);
   Serial.print(",");
   Serial.print("M2:");
   Serial.print(m2_pulse);
   Serial.print(",");
   Serial.print("M3:");
   Serial.print(m3_pulse);
   Serial.print(",");
   Serial.print("M4:");
   Serial.print(m4_pulse);
   Serial.println(",");
  }
}

// SET LAST STATE AS CURRENT
fa_last_state=fa_state;
lat_last_state=lat_state;
rot_last_state=rot_state;

last_time=this_time;
last_width=this_width;

}
