#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL36w9Z1OaQ"
#define BLYNK_TEMPLATE_NAME "Smart Plant"

#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

/* Connections
Relay. D3
Btn.   D7
Soil.  A0
PIR.   D5
SDA.   D2
SCL.   D1
Temp.  D4
*/

//Initialize the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

char auth[] = "kwUeYmVksx9GBwKRQ842ZqGSWfIxcjid";  //Enter your Blynk Auth token
char ssid[] = "Stardust Crusadrs";  //Enter your WIFI SSID
char pass[] = "Luffy_1071";  //Enter your WIFI Password

DHT dht(D4, DHT11); //(DHT sensor pin,sensor type)  D4 DHT11 Temperature Sensor
BlynkTimer timer;

//Define component pins
#define soil A0     //A0 Soil Moisture Sensor
#define PIR D5      //D5 PIR Motion Sensor
int PIR_ToggleValue;

void checkPhysicalButton();
int relay1State = LOW;
int pushButton1State = HIGH;
#define RELAY_PIN_1       D3   //D3 Relay
#define PUSH_BUTTON_1     D7   //D7 Button
#define VPIN_BUTTON_1    V12 

//Create three variables for pressure
double T, P;
char status;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(PIR, INPUT);

  digitalWrite(RELAY_PIN_1, LOW);
  pinMode(PUSH_BUTTON_1, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_1, relay1State);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();
  pinMode(RELAY_PIN_1, OUTPUT);


  lcd.setCursor(0, 0);
  lcd.print("  Initializing  ");
  for (int a = 5; a <= 10; a++) {
    lcd.setCursor(a, 1);
    lcd.print(".");
    delay(500);
  }
  lcd.clear();
  lcd.setCursor(11, 1);
  lcd.print("W:OFF");

  // Call the function
  timer.setInterval(100L, soilMoistureSensor);
  timer.setInterval(100L, DHT11sensor);
  timer.setInterval(500L, checkPhysicalButton);
}

// Get the DHT11 sensor values
void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(t);

  lcd.setCursor(8, 0);
  lcd.print("H:");
  lcd.print(h);
}

// Get the soil moisture values
void soilMoistureSensor() {
  int value = analogRead(soil);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  Blynk.virtualWrite(V3, value);
  lcd.setCursor(0, 1);
  lcd.print("S:");
  lcd.print(value);
  lcd.print(" ");
}

// Get the PIR sensor values
void PIRsensor() {
  bool value = digitalRead(PIR);
  if (value) {
    Blynk.logEvent("pirmotion","WARNING! Motion Detected!"); //Enter your Event Name
    WidgetLED LED(V5);
    LED.on();
  } else {
    WidgetLED LED(V5);
    LED.off();
  }  
}

BLYNK_WRITE(V6)
{
 PIR_ToggleValue = param.asInt();  
}

BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(VPIN_BUTTON_1);
}

BLYNK_WRITE(VPIN_BUTTON_1) {
  relay1State = param.asInt();
  digitalWrite(RELAY_PIN_1, relay1State);

  Serial.print("Received value from Blynk cloud for VPIN_BUTTON_1: ");
  Serial.println(relay1State);
}

void checkPhysicalButton()
{
  if (digitalRead(PUSH_BUTTON_1) == LOW) {
    // pushButton1State is used to avoid sequential toggles
    if (pushButton1State != LOW) {

      // Toggle Relay state
      relay1State = !relay1State;
      digitalWrite(RELAY_PIN_1, relay1State);

      // Update Button Widget
      Blynk.virtualWrite(VPIN_BUTTON_1, relay1State);
    }
    pushButton1State = LOW;
  } else {
    pushButton1State = HIGH;
  }
}

void loop() {
    if (PIR_ToggleValue == 1)
    {
    lcd.setCursor(5, 1);
    lcd.print("M:ON ");
      PIRsensor();
    }
     else
     {
    lcd.setCursor(5, 1);
    lcd.print("M:OFF");
    WidgetLED LED(V5);
    LED.off();
     }

if (relay1State == HIGH)
{
  lcd.setCursor(11, 1);
  lcd.print("W:ON ");
  }
  else if (relay1State == LOW)
  {
    lcd.setCursor(11, 1);
    lcd.print("W:OFF");
    }
     
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
}
