#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>

int ledPin = 6;
int s2,s3,s4;
int status = WL_IDLE_STATUS;
char ssid[] = "Dhanu"; //WiFi Network Name
char pass[] = "123456789"; //WiFi Network Password
int keyIndex = 0;
unsigned int localPort = 6661;
char packetBuffer[255];
char  ReplyBuffer[] = "OFF";

WiFiUDP Udp;

void setup() {
pinMode (A1, INPUT);
pinMode (A2, INPUT);
pinMode (A3, INPUT);
Serial.begin(9600);

if (WiFi.status() == WL_NO_SHIELD) 
  {
    Serial.println("WiFi shield not present");
    while (true);
  }

  // Connect to WiFi
while ( status != WL_CONNECTED) 
  {
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  status = WiFi.begin(ssid, pass);
  delay(10000);
  }
  Serial.println("WiFi Status  ");
  printWiFiStatus();

  Serial.println("\n Starting Listener");
  Udp.begin(localPort);
}

void loop() {

readAnalog();
process();
IPAddress ip(192, 168, 211, 212);
Udp.beginPacket(ip, localPort);
Udp.write(ReplyBuffer);
Udp.endPacket();
//Serial.println("Data Send");

delay(200);
}

void printWiFiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void readAnalog()
{
s2 = analogRead(A1);
s3 = analogRead(A2);
s4 = analogRead(A3);
  
Serial.print(s2);
Serial.print(" -- ");
Serial.print(s3);
Serial.print(" -- ");
Serial.print(s4);
Serial.println("  ");
}

void process()
{
  if ((s2<45))
           {
                if ((s3>600))
                {
                    if((s4<600)&&(s4>400)){
                    Serial.println("1, F");
                    strcpy(ReplyBuffer, "1, F");
                  }
                   else if((s4>=600)){
                    Serial.println("1 FL");
                    strcpy(ReplyBuffer, "1, FL");
                  }
                  else if((s4<=400)){
                    Serial.println("1, FR");
                    strcpy(ReplyBuffer, "1, FR");
                  }

                  }


                if ((s3<=600) && (s3>=450))
                {
                    if((s4<600)&&(s4>400)){
                    Serial.println("1, 0");
                    strcpy(ReplyBuffer, "1, 0");
                  }
                   else if((s4>=600)){
                    Serial.println("1, L");
                    strcpy(ReplyBuffer, "1, L");
                  }
                  else if((s4<=400)){
                    Serial.println("1, R");
                    strcpy(ReplyBuffer, "1, R");
                  }

                  }



                 if ((s3<450))
                {
                    if((s4<600)&&(s4>400)){
                    Serial.println("1, B");
                    strcpy(ReplyBuffer, "1, B");
                  }
                   else if((s4>=600)){
                    Serial.println("1, BL");
                    strcpy(ReplyBuffer, "1, BL");
                  }
                  else if((s4<=400)){
                    Serial.println("1, BR");
                    strcpy(ReplyBuffer, "1, BR");
                  }

                  }

                  
                }
  else if((s2>=45))
  {
    strcpy(ReplyBuffer, "0, 0");
    Serial.println("0, 0");
  }

  else
  {
        strcpy(ReplyBuffer, "0, 0");
        Serial.println("0, 0");
  } 
  
}



