//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseRoom_ESP8266 is a sample that demo using multiple sensors
// and actuactor with the FirebaseArduino library.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#include "secret.h"

void initWifi()
{
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
}
void initFirebase()
{
  //Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.begin(FIREBASE_HOST);
}

void setFirebaseBME280_I2C(float temp, float press, float hum)
{
  StaticJsonBuffer<100> jsonBuffer;
  JsonObject &json = jsonBuffer.createObject();
  json["temp"] = temp;
  String strpress = String(press);
  json["press"] = strpress;
  json["hum"] = hum;
  json.printTo(Serial);
  Firebase.push("bme280", json);
  if (Firebase.failed())
  {
    Serial.print("setting /bme280 failed:");
    Serial.println(Firebase.error());
    return;
  }
}
