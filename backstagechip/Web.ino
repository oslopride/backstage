void initWifi();
void sendGet(String card);
void runWifi();
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>

#include <WiFiClientSecure.h> 
#include <WiFiManager.h>  
void configModeCallback (WiFiManager *myWiFiManager);

const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80
WiFiClient client;
HTTPClient http;
bool isSendRequest = false;
String requestUrl;
    
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void initWifi() {
   WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.autoConnect("Backstagr", "");

  Serial.println("Connected to WiFi");
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }


  Serial.println("Connected to WiFi");
  Serial.println(WiFi.SSID());
  Serial.println();
  Serial.print("IP Address = ");
  Serial.println(WiFi.localIP());
  pinMode(BLINKER, OUTPUT);
  digitalWrite(BLINKER, BLINKOFF);
}

void runWifi() {
  MDNS.update();
  if(isSendRequest) {
    sendRequest();
  }
}
const char fingerprint[] PROGMEM = "3a b0 b1 c2 7f 74 6f d9 0c 34 f0 d6 a9 60 cf 73 a4 22 9d e8";

void sendGet(String card) {
    isSendRequest = true;
    requestUrl = "http://backstagekassa.azurewebsites.net/api/artist/CardRead?device=123&card="; //prod
    //requestUrl = "http://10.0.0.95:64098/api/artist/CardRead?device=123&card="; //bajonett 
    requestUrl.concat(card);
}
int retry = 0;
void sendRequest()
{
  
  Serial.print("[HTTP] begin...\n"+requestUrl);
  if (http.begin(client, requestUrl)) {  // HTTP


    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      retry = 0;
      isSendRequest = false;
      String payload = http.getString();
        
      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        Serial.println(payload);  
        Serial.println("card found");  
        handleStrip(RAINBOW);
      }
      else if(payload == "not found") {
        Serial.println("card not found"); 
        handleStrip(BMP);
      }
    } else if(retry < 5){
      retry +=1;
      Serial.printf("[HTTP] GET... failed, error: %s\n trying again... ", http.errorToString(httpCode).c_str());
      Serial.print(retry);
      Serial.println(".");
    }
    else {
      Serial.printf("[HTTP] GET... failed totally, error: %s\n... ", http.errorToString(httpCode).c_str());
      isSendRequest = false;
    }

    http.end();
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
    isSendRequest = false;
  }

  requestUrl = "";
/*WiFiClientSecure httpsClient;    //Declare object of class WiFiClient
 
  String Link, host;
  Link = "/api/artist/CardRead?device=123&card="+card;
  host = "backstagekassa.azurewebsites.net";
  Serial.println("backstagekassa.azurewebsites.net");
 
  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  httpsClient.setFingerprint(fingerprint);
  httpsClient.setTimeout(15000); // 15 Seconds
  delay(500);
  
  Serial.print("HTTPS Connecting");
  int r=0; //retry counter
  while((!httpsClient.connect(host, httpsPort)) && (r < 30)){
      delay(100);
      Serial.print(".");
      r++;
  }
  if(r==30) {
    Serial.println("Connection failed");
  }
  else {
    Serial.println("Connected to web");
  }
  
  Serial.print("requesting URL: ");
  Serial.println(host+Link);
 
  httpsClient.print(String("GET ") + Link + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +               
               "Connection: close\r\n\r\n");
 
  Serial.println("request sent");
                  
  while (httpsClient.connected()) {
    String line = httpsClient.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
 
  Serial.println("reply was:");
  Serial.println("==========");
  String line;
  while(httpsClient.available()){        
    line = httpsClient.readStringUntil('\n');  //Read Line by Line
    Serial.println(line); //Print response
  }
  Serial.println("==========");
  Serial.println("closing connection");
    
  delay(2000);  //GET Data at every 2 seconds*/
}
  // Make a HTTP request:
 // String url ="backstagekassa.azurewebsites.net/api/artist/CardRead?device=123&card="+card;
  
//}
