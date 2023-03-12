#include <SPI.h>
#include <LoRa.h>
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");
  carrier.noCase();
  carrier.begin();

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);
  // Passing in FAHRENHEIT as the unit parameter to ENV.readTemperature(...),
  // allows you to read the sensor values in imperial units
  float temperature = carrier.Env.readTemperature(FAHRENHEIT);
  float humidity    = carrier.Env.readHumidity();

  // send packet
  LoRa.beginPacket();
 LoRa.print("T ");
  LoRa.print(temperature);
  LoRa.print(counter);
  LoRa.endPacket();
 // print each of the sensor values
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °F");

 // Serial.print("Humidity    = ");
 // Serial.print(humidity);
//  Serial.println(" %");

  // print an empty line
 // Serial.println();
  counter++;

  delay(5000);
}
