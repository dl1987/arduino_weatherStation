#include <OneWire.h>
#include <DS18B20.h>
#include <DHT.h>

#define ONEWIRE_PIN 2
#define DHTPIN_OUT 3
#define DHTPIN_IN 4

#define SENSORS_NUM 2
#define DHTTYPE DHT11

const byte address[SENSORS_NUM][8] PROGMEM ={
  0x28, 0xFF, 0x49, 0x7F, 0x3, 0x15, 0x2, 0x2B, //term outside
  0x28, 0xFF, 0x88, 0x17, 0x43, 0x4, 0x0, 0xED  //term inside
};

OneWire onewire(ONEWIRE_PIN);
DS18B20 sensors(&onewire);
DHT dht_out(DHTPIN_OUT, DHTTYPE);
DHT dht_in(DHTPIN_IN, DHTTYPE);

void setup() {
  while(!Serial);
  Serial.begin(9600);

  sensors.begin();
  sensors.request();
  dht_out.begin();
  dht_in.begin();
}

void loop() {
  if(sensors.available())
  {
    for (byte i=0; i<SENSORS_NUM; i++)
    {
      float temp = sensors.readTemperature(FA(address[i]));;
      if(i == 0)
      {
        Serial.print("Temp.outside: ");
      }
      else
      {
        Serial.print("Temp. inside: ");
      }
      Serial.print(temp);
      Serial.println(F(" 'C"));
    }
    sensors.request();
  }

  float h_out = dht_out.readHumidity();
//  float t_out = dht_out.readTemperature();

  float h_in = dht_in.readHumidity();
//  float t_in = dht_in.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(h_out)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity out: "); 
    Serial.print(h_out);
    Serial.println(" %\t");
//    Serial.print("Temperature out: "); 
//    Serial.print(t_out);
//    Serial.println(" *C");
  }
  
  if (isnan(h_in)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity in: "); 
    Serial.print(h_in);
    Serial.println(" %\t");
//    Serial.print("Temperature in: "); 
//    Serial.print(t_in);
//    Serial.println(" *C");
  }



}
