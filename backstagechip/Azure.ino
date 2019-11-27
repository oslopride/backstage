/*void connectToIoTHub();
void sendMqttMessage(String card);
void runMqtt();
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

// Azure IoT Hub Settings --> CHANGE THESE
#define IOTHUB_HOSTNAME         "backstagehub.azure-devices.net"
#define DEVICE_ID               "kasse1"
#define DEVICE_KEY              "zODBlFDqEXM/bk6tRUudsPklrzRsoXypSnis6W/r2jE=" //Primary key of the device


// example: <myiothub>.azure-devices.net
const char* iothub_url = "backstagehub.azure-devices.net";

// this is the id of the device created in Iot Hub
// example: myCoolDevice
const char* iothub_deviceid = "kasse1";

// <myiothub>.azure-devices.net/<myCoolDevice>
const char* iothub_user = "backstagehub.azure-devices.net/kasse1";

// SAS token should look like "SharedAccessSignature sr=backstagehub.azure-devices.net%2Fdevices%2Fkasse1&sig=DWJeW0MThqCC58J6jr8v6uBiS4xmdDpnqophW5cWzFc%3D&se=1559082259"
const char* iothub_sas_token = "SharedAccessSignature sr=backstagehub.azure-devices.net%2Fdevices%2Fkasse1&sig=gt%2FVUfyrCCr815beulgUGxhehOw4hAGi9B7RPa1kVXs%3D&se=1563999755";
// default topic feed for subscribing is "devices/<myCoolDevice>/messages/devicebound/#""
const char* iothub_subscribe_endpoint = "devices/kasse1/messages/devicebound/";

// default topic feed for publishing is "devices/<myCoolDevice>/messages/events/"
const char* iothub_publish_endpoint = "devices/kasse1/messages/events/";


WiFiClientSecure espClient;
PubSubClient pubsubclient(espClient);

long lastMsg = 0;


// setup Azure IOTHUB client
const uint INTERVAL = 20;             // SAS token validity period in minutes
const int REFRESHPERCENTAGE = 80;     // Percentage of SAS token validity used when reauthentication is attempted
const int MISSEDTOOMANY = 10;         // Reconnect to MQTT when consecutively missed this many messages 
const int BLINKER = BUILTIN_LED;
const int BLINKTIME = 700;
const int BLINKOFF = LOW;
const int BLINKON = HIGH;              // Set to BLINKOFF to disable LED

// function to connect to MQTT server
void connect_mqtt() {
  // Loop until we're reconnected
  while (!pubsubclient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (pubsubclient.connect(iothub_deviceid, iothub_user, DEVICE_KEY)) {
      Serial.println("connected");
      // ... and resubscribe
      pubsubclient.subscribe(iothub_subscribe_endpoint);
    } else {
      Serial.print("failed, rc=");
      Serial.print(pubsubclient.state());
      Serial.println("try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// callback function for when a message is dequeued from the MQTT server
void callback(char* topic, byte* payload, unsigned int length) {
  // print message to serial for debugging
  Serial.print("Message arrived: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println('---');
}

*/
/*

void connectToIoTHub() {

  // set up connection and callback for MQTT server
  pubsubclient.setServer("backstagehub.azure-devices.net", 8883);
  pubsubclient.setCallback(callback);

  // connect to MQTT
  connect_mqtt();
  
}
void runMqtt() {
  pubsubclient.loop();
}
int retry = 0;

void sendMqttMessage(String card) {

    Serial.print("is MQTT pubsubclient is still connected: ");
    Serial.println(pubsubclient.connected());

    // set up json object
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();

    // populate keys in json
    root["device"] = "123";
    // substitute the int value below for a real sensor reading (ie. an analogRead() result)
    root["card"] = card;

    // convert json to buffer for publishing
    char buffer[256];
    root.printTo(buffer, sizeof(buffer));

    // publish
    pubsubclient.publish(iothub_publish_endpoint, buffer);
 
}
*/
