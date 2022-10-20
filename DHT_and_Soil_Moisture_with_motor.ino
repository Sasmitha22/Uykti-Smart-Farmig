#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);



const int Pin=0;
const int limit=480;
const int RELAY_PIN = A5; 
 
void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(13,OUTPUT);
  
  Serial.println(F("DHTxx test!"));
  dht.begin();
  
  // put your setup code here, to run once:

}

void loop() {
  int value;
  int percentage;
  value = analogRead(Pin);
  percentage = 100-((value-0)/(1023.0-0)) * 100;
  if (percentage >40){
  digitalWrite(RELAY_PIN, HIGH); // turn on pump 5 seconds
  Serial.println("Motor doesn't run");
  delay(3600);
  }
  else {
  digitalWrite(RELAY_PIN, LOW);  // turn off pump 5 seconds
  Serial.println("Motor runs");
  delay(3600);
  }
  Serial.println("Moisture Level:");
  Serial.println(percentage);

  //delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("C "));
  Serial.print(f);
  Serial.print(F("F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("C "));
  Serial.print(hif);
  Serial.println(F("F"));

}
