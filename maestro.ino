#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>


const char* ssid = "Nombre de la red";
const char* password = "Contraseña  de la red";
WiFiServer server(80);

int motor = 0;

void setup() {
  Wire.begin(); // 
   Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  }
}
 
void loop() {
 
  delay(2000);
  if (WiFi.status() == WL_CONNECTED) { 
 
    HTTPClient http; 
    
    http.begin("http://api.thingspeak.com/channels/< your api key>/feeds/last.json");
    int httpCode = http.GET();                                                       
 
    if (httpCode > 0) { 
      DynamicJsonBuffer jsonBuffer;
      String  payload = http.getString();
       JsonObject& root = jsonBuffer.parseObject(payload);      
      String motor= root["field1"];
      http.end();
  
      if(motor == "motor1"){
         Wire.beginTransmission(1); 
      Wire.write(1); 
      Wire.endTransmission();
        InsertNone();
        motor="0";
      }
      if(motor == "motor2"){
        Wire.beginTransmission(1);
      Wire.write(2); 
      Wire.endTransmission();
        InsertNone();
        motor = "0";
      }
    }
  }
 
  delay(3000);   
 
}

void InsertNone(){
   // Insertar vacio
   HTTPClient httpDel;
   httpDel.begin("http://api.thingspeak.com/update.json?api_key=<your api key>&field1=0");
   int httpCode2 = httpDel.POST("Enviado desde arduino");    
   String pay = httpDel.getString();
   httpDel.end();
   delay(2000);
}
