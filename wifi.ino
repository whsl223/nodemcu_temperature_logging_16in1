#include <OneWire.h>
#include <DallasTemperature.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"
#define ONE_WIRE_BUS D2


const char* ssid     = "ssid";
const char* password = "pw";
const char *GScriptId = "id";
String payload_base =  "{\"command\": \"append_row\", \"sheet_name\": \"Sheet1\", \"values\": ";
String payload = "";


const char* host = "script.google.com";
const int httpsPort = 443;
const char* fingerprint = "";
String url = String("/macros/s/") + GScriptId + "/exec";
HTTPSRedirect* client = nullptr;

float temperature1 ,temperature2 ,temperature3 ,temperature4 ,temperature5 ,temperature6 ,temperature7 ,temperature8 ,temperature9 ,temperature10,temperature11,temperature12,temperature13,temperature14,temperature15,temperature16;
uint8_t sensor1[8] = {0x28, 0xA0, 0xAB, 0x02, 0x00, 0x00, 0x00, 0x06};
uint8_t sensor2[8] = {0x28, 0x10, 0x0B, 0x79, 0x97, 0x09, 0x03, 0x0C};
uint8_t sensor3[8] = {0x28, 0xF8, 0xB0, 0x03, 0x00, 0x00, 0x00, 0x0A};
uint8_t sensor4[8] = {0x28, 0xE2, 0x8C, 0x96, 0xF0, 0x01, 0x3C, 0x0F};
uint8_t sensor5[8] = {0x28, 0xC6, 0xE2, 0x96, 0xF0, 0x01, 0x3C, 0xD6};
uint8_t sensor6[8] = {0x28, 0xF1, 0xB6, 0x79, 0x97, 0x03, 0x03, 0x56};
uint8_t sensor7[8] = {0x28, 0x65, 0x44, 0x79, 0x97, 0x19, 0x03, 0x15};
uint8_t sensor8[8] = {0x28, 0x0D, 0x26, 0x96, 0xF0, 0x01, 0x3C, 0x8C};
uint8_t sensor9[8] = {0x28, 0x7D, 0x2A, 0x96, 0xF0, 0x01, 0x3C, 0x35};
uint8_t sensor10[8] = {0x28, 0x73, 0xDF, 0x79, 0x97, 0x13, 0x03, 0xDC};
uint8_t sensor11[8] = {0x28, 0xA7, 0xD7, 0x96, 0xF0, 0x01, 0x3C, 0x74};
uint8_t sensor12[8] = {0x28, 0x17, 0x18, 0x79, 0x97, 0x19, 0x03, 0x57};
uint8_t sensor13[8] = {0x28, 0x8F, 0x22, 0x79, 0x97, 0x21, 0x03, 0x25};
uint8_t sensor14[8] = {0x28, 0x8F, 0xD2, 0x79, 0x97, 0x03, 0x03, 0xD3};
uint8_t sensor15[8] = {0x28, 0x3F, 0xD2, 0x79, 0x97, 0x03, 0x03, 0xD4};
uint8_t sensor16[8] = {0x28, 0xA3, 0x95, 0x95, 0xF0, 0x01, 0x3C, 0x4A};


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress Thermometer;

int deviceCount = 0;

void setup(void)
{
  Serial.println('\n');
  Serial.begin(9600);
  WiFi.begin(ssid, password);             
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  // Use HTTPSRedirect class to create a new TLS connection
  client = new HTTPSRedirect(httpsPort);
  client->setInsecure();
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");
  
  Serial.print("Connecting to ");
  Serial.println(host);

  // Try to connect for a maximum of 5 times
  bool flag = false;
  for (int i=0; i<5; i++){ 
    int retval = client->connect(host, httpsPort);
    if (retval == 1){
       flag = true;
       Serial.println("Connected");
       break;
    }
    else
      Serial.println("Connection failed. Retrying...");
  }
  if (!flag){
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    return;
  }
  delete client;    // delete HTTPSRedirect object
  client = nullptr; // delete HTTPSRedirect object
  
  

  sensors.begin();

  // locate devices on the bus
  Serial.println("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");
  
  Serial.println("Printing addresses...");
  for (int i = 0;  i < deviceCount;  i++)
  {
    Serial.print("Sensor ");
    Serial.print(i+1);
    Serial.print(" : ");
    sensors.getAddress(Thermometer, i);
    printAddress(Thermometer);
  }
}

void loop(void)
{
sensors.requestTemperatures();  
 
temperature1 = sensors.getTempC(sensor1);
temperature2 = sensors.getTempC(sensor2);
temperature3 = sensors.getTempC(sensor3);
temperature4 = sensors.getTempC(sensor4);
temperature5 = sensors.getTempC(sensor5);
temperature6 = sensors.getTempC(sensor6);
temperature7 = sensors.getTempC(sensor7);
temperature8 = sensors.getTempC(sensor8);
temperature9 = sensors.getTempC(sensor9);
temperature10 = sensors.getTempC(sensor10);
temperature11 = sensors.getTempC(sensor11);
temperature12 = sensors.getTempC(sensor12);
temperature13 = sensors.getTempC(sensor13);
temperature14 = sensors.getTempC(sensor14);
temperature15 = sensors.getTempC(sensor15);
temperature16 = sensors.getTempC(sensor16);

Serial.print("Sensor 1: ");
Serial.println(temperature1);
Serial.print("Sensor 2: ");
Serial.println(temperature2);
Serial.print("Sensor 3: ");
Serial.println(temperature3);
Serial.print("Sensor 4: ");
Serial.println(temperature4);
Serial.print("Sensor 5: ");
Serial.println(temperature5);
Serial.print("Sensor 6: ");
Serial.println(temperature6);
Serial.print("Sensor 7: ");
Serial.println(temperature7);
Serial.print("Sensor 8: ");
Serial.println(temperature8);
Serial.print("Sensor 9: ");
Serial.println(temperature9);
Serial.print("Sensor 10 :");
Serial.println(temperature10);
Serial.print("Sensor 11 :");
Serial.println(temperature11);
Serial.print("Sensor 12 :");
Serial.println(temperature12);
Serial.print("Sensor 13 :");
Serial.println(temperature13);
Serial.print("Sensor 14 :");
Serial.println(temperature14);
Serial.print("Sensor 15 :");
Serial.println(temperature15);
Serial.print("Sensor 16 :");
Serial.println(temperature16);

 static bool flag = false;
  if (!flag){
    client = new HTTPSRedirect(httpsPort);
    client->setInsecure();
    flag = true;
    client->setPrintResponseBody(true);
    client->setContentTypeHeader("application/json");
  }
  if (client != nullptr){
    if (!client->connected()){
      client->connect(host, httpsPort);
    }
  }
  else{
    Serial.println("Error creating client object!");
  }
  
  // Create json object string to send to Google Sheets
  payload = payload_base + "\"" + temperature1 + "," + temperature2 + "," + temperature3 + "," + temperature4 + ","+ temperature5 + ","+ temperature6 + ","+ temperature7 + ","+ temperature8 + ","+ temperature9 + "," + temperature10 + "," + temperature11 + "," + temperature12 + "," + temperature13 + "," + temperature14 + "," + temperature15 + ","+ temperature16 + "\"}";
  
  // Publish data to Google Sheets
  Serial.println("Publishing data...");
  Serial.println(payload);
  if(client->POST(url, host, payload)){ 
    // do stuff here if publish was successful
  }
  else{
    // do stuff here if publish was not successful
    Serial.println("Error while connecting");
  }




delay(5000);
  }

void printAddress(DeviceAddress deviceAddress)
{ 
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.print("0x");
    if (deviceAddress[i] < 0x10) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
    if (i < 7) Serial.print(", ");
  }
  Serial.println("");
}
