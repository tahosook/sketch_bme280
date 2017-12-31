
void setup() {
    Serial.begin(9600);

    initBME280_I2C();
    initWifi();
    initFirebase();
    //dumpChipInformation();
}

void loop() {
    readBME280_I2C();
    float temp = getTemp();
    float press = getPress();
    float hum = getHum();
    Serial.print("TEMP : ");
    Serial.print(temp);
    Serial.print(" DegC  PRESS : ");
    Serial.print(press);
    Serial.print(" hPa  HUM : ");
    Serial.print(hum);
    Serial.println(" %");    

    setFirebaseBME280_I2C(temp,press,hum);
    ESP.deepSleep(5*60*1000*1000,WAKE_RF_DEFAULT);
    
    delay(1000);
}
