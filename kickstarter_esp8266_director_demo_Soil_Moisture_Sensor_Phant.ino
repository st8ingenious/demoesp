#include <ESP8266WiFi.h>
#include <Phant.h>
const char WiFiSSID[] = "xxxxxxxxxx";
const char WiFiPSK[] = "xxxxxxxxxx";

const int LED_PIN = 5; 
const char PhantHost[] = "data.sparkfun.com";
const char PublicKey[] = "xxxxxxxxxx";
const char PrivateKey[] = "xxxxxxxxxx";

const unsigned long postRate = 30000;
unsigned long lastPost = 0;

int thresholdUp = 400;
int thresholdDown = 250;

int sensorPin = A0;
String DisplayWords;
  int sensorValue;

void setup() 
{
  initHardware();
  connectWiFi();
}

void loop() 
{
  if (lastPost + postRate <= millis())
  {
    if (postToPhant())
      lastPost = millis();
    else
      delay(100);    
  }
  
  sensorValue = analogRead(sensorPin);
   //Serial.print("Water Level: ");
  // Serial.print(sensorValue);

  if (sensorValue <= thresholdDown){

    DisplayWords = "Wet, Leave it!";
    // Serial.println(DisplayWords);

  } else if (sensorValue >= thresholdUp){
    DisplayWords = "Dry, Water it!";
    // Serial.println(DisplayWords);

  } else {
      //  Serial.println(DisplayWords);
  }
  delay(500);
}

void connectWiFi()
{
  byte ledStatus = LOW;

  WiFi.mode(WIFI_STA);
  WiFi.begin(WiFiSSID, WiFiPSK);

  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED_PIN, ledStatus); 
    ledStatus = (ledStatus == HIGH) ? LOW : HIGH;

    delay(100);
  }
}

void initHardware()
{
  //Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

int postToPhant()
{
  digitalWrite(LED_PIN, HIGH);
  Phant phant(PhantHost, PublicKey, PrivateKey);
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.macAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String postedID = "cb-" + macID;
    phant.add("time", millis());
  phant.add("soil", sensorValue);
   phant.add("prom", DisplayWords);

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(PhantHost, httpPort)) 
  {
    return 0;
  }
  client.print(phant.post());

  while(client.available()){
    String line = client.readStringUntil('\r');
   // Serial.print(line); // Trying to avoid using serial
  }

  digitalWrite(LED_PIN, LOW);

  return 1; // Return success
}
