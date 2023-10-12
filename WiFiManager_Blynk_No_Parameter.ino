//---------------------------------------------------------------------//
//WiFiManager + Blynk NO WiFiManagerParameter
//---------------------------------------------------------------------//
//---------------------------------------------------------------------//
//*********************       include Lib        **********************//
//---------------------------------------------------------------------//
#include <WiFiManager.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>


SimpleTimer Timer;
char blynk_token[] = "";  //edit token blynk
char blynk_host[] = "";   //edit host blynk
int blynk_port = 8080;    //edit port blynk
char wifimanager_name_ap[] = "IOT";            //edit WiFi AP Name
char wifimanager_password_ap[] = "00000000";              //edit WiFi AP PassWord

//---------------------------------------------------------------------//
//***********************       Define        *************************//
//---------------------------------------------------------------------//
//Define BLYNK Serial
#define BLYNK_PRINT Serial
// pin D1 Reset WiFiManager
#define sw_ResetWifi D1

//---------------------------------------------------------------------//
//*******************       void setup        *************************//
//---------------------------------------------------------------------//
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //creating WiFiManager
  Serial.println("WiFiManager :: Creating");
  WiFiManager wm;
  Serial.println("******************************");

  //Reset WiFiManager Config?
  //cout 1-5 s
  Serial.println("Reset WiFiManager Config?");
  for (int i = 5; i > 0; i--) {
    Serial.print(String(i) + " ");
    delay(1000);
  }
  Serial.println("");
  Serial.println("******************************");
  pinMode(sw_ResetWifi, INPUT_PULLUP);
  if (digitalRead(sw_ResetWifi) == LOW) {
    wm.resetSettings();
    Serial.println("WiFiManager :: Reset WiFiManager OK!");
    Serial.println("ESP8266 :: Restart!!!!");
    Serial.println("******************************");
    delay(5000);
    ESP.restart();
  }

  // Setup Wi-Fi Name AP and Password
  bool res;
  res = wm.autoConnect(wifimanager_name_ap, wifimanager_password_ap);
  Serial.println("******************************");

  if (!res) {
    Serial.println("WiFiManager :: Failed to connect");
    delay(5000);
    Serial.println("WiFiManager :: Restart!!!!");
    Serial.println("******************************");
    ESP.restart();
  } else {
    //if you get here you have connected to the WiFi
    Serial.println("WiFiManager :: connected");
    Serial.println("******************************");
    Serial.println(":: WiFiManager Info :: ");
    Serial.print("WiFiManager Local IP:: ");
    Serial.println(WiFi.localIP());
    Serial.print("WiFiManager Gateway IP:: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("WiFiManager Subnet Mask:: ");
    Serial.println(WiFi.subnetMask());
    Serial.println("******************************");

    // Blynk config token & host & port
    Blynk.config(blynk_token, blynk_host, blynk_port);

    // Blynk Server Info
    Serial.println(":: Blynk Server Info :: ");
    Serial.print("Blynk Server Host :: ");
    Serial.println(blynk_host);
    Serial.print("Blynk Server Port :: ");
    Serial.println(blynk_port);
    Serial.print("Blynk Server Token :: ");
    Serial.println(blynk_token);
    Serial.println("******************************");
  }
  // add pin mode
  pinMode(sw_ResetWifi, INPUT_PULLUP);
  //---------------------------------------------------------------------//
  //************************       Code Here        *********************//
  //---------------------------------------------------------------------//
}

//---------------------------------------------------------------------//
//************************       BLYNK        *************************//
//---------------------------------------------------------------------//
BLYNK_CONNECTED() {
  Serial.println("Blynk Server :: Connected ");
  Blynk.syncAll();
  Serial.println("Blynk Server :: Sync All Data ");
  Serial.println("******************************");
}
BLYNK_DISCONNECTED() {
  Serial.println("Blynk Server :: Failed to connect !!");
  Serial.println("Blynk Server :: Sync All Data Failed!!");
  Serial.println("******************************");
}

//---------------------------------------------------------------------//
//*******************       void loop        *************************//
//---------------------------------------------------------------------//
void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  Timer.run();
}
