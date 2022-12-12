#include <SoftwareSerial.h>
SoftwareSerial mySerial(8, 10);

int button = 1;
int RedLED = 6;
int buzzer = 7;
String cmd = "";

// Choose two Arduino pins to use for software serial
int RXPin = 2;
int TXPin = 3;

//Default baud of NEO-6M is 9600
int GPSBaud = 9600;

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);
double Lat = 12.0126405;       //variable for lattitude
double Lot = 79.8527392;
String gpsdata;

void setup () {

pinMode(buzzer, OUTPUT) ;
pinMode(RedLED, OUTPUT);
pinMode(button, INPUT);
mySerial.begin(9600);
Serial.begin(9600);
gpsSerial.begin(GPSBaud);
Serial.println("Initializing...");
  delay(1000);

 mySerial.println("AT");                 // Sends an ATTENTION command, reply should be OK
 // updateSerial();
  mySerial.println("AT+CMGF=1");          // Configuration for sending SMS
  //updateSerial();
  mySerial.println("AT+CNMI=1,2,0,0,0");  // Configuration for receiving SMS
  //updateSerial();
  //sendSMS();
  //delay(5000);
}

void loop () {

button =digitalRead(1);
Serial.println(button);
 
 if (digitalRead(button)== HIGH )
{
 while (gpsSerial.available() > 0)
   Serial.write(gpsSerial.read());
   //gpsdata =gpsSerial.read();
//  gpsdata = (gpsSerial.location.lat(), 6);
    sendSMS();
  
digitalWrite(buzzer, HIGH);

digitalWrite(RedLED, HIGH);
}
else
{
digitalWrite(RedLED, LOW);
digitalWrite(buzzer,LOW);
}
}

void sendSMS(){
 // int gpsdata = gpsSerial.read();
  // mySerial.print(gpsdata);
   String msg = "I am in trouble!: http://bit.ly/3U2tRHh" + String(gpsdata);
  mySerial.println("AT+CMGF=1");
  delay(500);
  mySerial.println("AT+CMGS=\"+919952464958\"\r");
  
 
  mySerial.println ("Need help!");
  mySerial.println(msg);
  delay(500);
  mySerial.write(26);
}



void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {

    cmd+=(char)Serial.read();
 
    if(cmd!=""){
      cmd.trim();  // Remove added LF in transmit
      if (cmd.equals("S")) {
        sendSMS();
      } else {
        mySerial.print(cmd);
        mySerial.println("");
      }
    }
  }
  
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
