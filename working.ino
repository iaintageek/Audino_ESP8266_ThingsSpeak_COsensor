#include <ThingSpeak.h>

#include <ESP8266WiFi.h>

WiFiClient client;

String apiKey = "C32HE1JBC15TWG94";

const char *ssid =  "";
const char *pass =  "";
const char* server = "api.thingspeak.com";
const char*url="https://api.thingspeak.com/update";
unsigned long channelID = ; //Enter your credentials
char* writeAPIKey = " ";
unsigned int dataFieldOne = 1;                            // Field to write temperature data
unsigned int dataFieldTwo = 2;  
void setup()
{
    Serial.begin(9600);
    
  Serial.println("Connecting to ");
       Serial.println(ssid);
       WiFi.begin(ssid, pass);
      
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
            
     }
      Serial.println("");
  
    ThingSpeak.begin( client );

}



void loop()
{ 
    float sensor_volt,sensorValue=0.0;
    float RS_gas,RS_air;
    float ratio;// Get ratio RS_GAS/RS_air
    float R0;

     for(int i = 0; i<20;i++)
     {

 sensorValue = sensorValue + analogRead(A0);
 delay(900);
     }

     sensorValue = sensorValue/100.0;
 sensor_volt = sensorValue/1024*5.0;
 RS_air = (5.0-sensor_volt)/sensor_volt;
 R0 = RS_air/(26+(1/3));


     
    sensorValue = analogRead(A0);
    sensor_volt=(float)sensorValue/1024*5.0;
    RS_gas= (5.0-sensor_volt)/(sensor_volt);
    ratio = RS_gas/R0;
    Serial.print("R0 : ");
    Serial.println(R0);

    float ppm = 100 * pow(log10(40)/log10(0.09), ratio);
    Serial.print("PPM: ");
    Serial.println(ppm);
    write2TSData(channelID,dataFieldOne,R0,dataFieldTwo,ppm);
          client.stop();
    delay(6000);
   
}

 void  write2TSData( long channelID,unsigned int dataFieldOne,float R0,unsigned int dataFieldTwo,float ppm)
                          {
                             ThingSpeak.setField( dataFieldOne,R0);
                             ThingSpeak.setField( dataFieldTwo,ppm);
                             int writeSuccess = ThingSpeak.writeFields( channelID, writeAPIKey );
                      //      return writeSuccess;
                          }
    
