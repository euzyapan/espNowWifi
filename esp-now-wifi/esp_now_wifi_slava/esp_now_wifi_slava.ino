
#include <Arduino.h>
#include <esp_now.h>
#include "WiFi.h"

typedef struct struct_message {
     String d;
} struct_message;

struct_message myData;


// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) 
{
  memcpy(&myData, incomingData, sizeof(myData));

 Serial.print("Bytes received: ");
 Serial.println(len);
 Serial.print("String: ");
 Serial.println(myData.d);  
}


void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
  delay(100);

  Serial.println("Starting...\n");

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // print our mac address
  Serial.println(WiFi.macAddress());

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    for(;;) {      delay(1);  } // do not initialize wait forever
  }
  
  Serial.println("initialized ESP-NOW");



  // Register for a callback function that will be called when data is received
  
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // put your main code here, to run repeatedly:

}
