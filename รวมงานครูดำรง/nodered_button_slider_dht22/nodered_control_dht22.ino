
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#define DHTPIN 27
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
// Update these with values suitable for your network.
const char* ssid = "iPhone ของ Pon";
const char* password = "ponBamkyrr";

// Config MQTT Server
//server address
const char* mqtt_server = "172.20.10.3";
//port
const char* mqtt_port = "1883";
//username
const char* mqtt_user = "";
//password
const char* mqtt_password = "";

const int resolution = 8;
const int ledChannel = 0;
const int freq = 5000;

const int LED_PIN = 12;
const int LED_PIN2 = 14;
const int LED_PIN3 = 25;
static char celsiusTemp[7];
static char fahrenheitTemp[7];
static char humidityTemp[7];

const int pir = 26;
const int val=0;
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  
  ledcSetup(ledChannel, freq, resolution);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(LED_PIN2, ledChannel);
  pinMode(LED_PIN, OUTPUT);
pinMode(LED_PIN2, OUTPUT);
pinMode(LED_PIN3, OUTPUT); 
pinMode(pir, INPUT);
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

 


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, 1883);
 
  client.setCallback(callback);
  Serial.println("DHTxx test!");

dht.begin();

}

void loop() {
  if (!client.connected()) {
    Serial.println("Attemping MQTT connection...");

    if (client.connect("ESP32Cient", mqtt_user, mqtt_password)) {
      Serial.println ("connect");
      //topicname
      client.subscribe("esp32");
     client.subscribe("esptemp");
       client.subscribe("esphu");
       client.subscribe("esppir");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
      return;
    }
  }
  client.loop();
  int val = digitalRead(pir); //อ่านค่าสัญญาณ digital ขา8 ที่ต่อกับเซ็นเซอร์
/*Serial.print("val = "); // พิมพ์ข้อมความส่งเข้าคอมพิวเตอร์ "val = "
Serial.println(val); // พิมพ์ค่าของตัวแปร val*/


if (val == 0) { // ค่า เป็น 0 ตรวจจับเจอวัตถุ สั่งให้ไฟ LED ติด
digitalWrite(LED_PIN3, LOW); // สั่งให้ LED ติดสว่าง
client.publish("esppir","ปลอดภัย");
}
if (val == 1) {
digitalWrite(LED_PIN3, HIGH); // สั่งให้ LED ดับ
client.publish("esppir","มีคนเดินผ่าน");
  
    
   
    Serial.println("Alert!!!!");
}
delay(100);
}


boolean isNumeric(String str) {
    unsigned int stringLength = str.length();
 
    if (stringLength == 0) {
        return false;
    }
 
    boolean seenDecimal = false;
 
    for(unsigned int i = 0; i < stringLength; ++i) {
        if (isDigit(str.charAt(i))) {
            continue;
        }
 
        if (str.charAt(i) == '.') {
            if (seenDecimal) {
                return false;
            }
            seenDecimal = true;
            continue;
        }
        return false;
    }
    return true;
}

/*void dhtread(){
  
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    strcpy(celsiusTemp, "Failed");
    strcpy(fahrenheitTemp, "Failed");
    strcpy(humidityTemp, "Failed");
  }
  else {
    // Computes temperature values in Celsius + Fahrenheit and Humidity
    float hic = dht.computeHeatIndex(t, h, false);
    dtostrf(hic, 6, 2, celsiusTemp);
    float hif = dht.computeHeatIndex(f, h);
    dtostrf(hif, 6, 2, fahrenheitTemp);
    dtostrf(h, 6, 2, humidityTemp);
    // You can delete the following Serial.prints, it s just for debugging purposes
  }


  client.publish("room/temperature", celsiusTemp);
  client.publish("room/humidity", humidityTemp);

}*/
void callback(char* topic, byte* payload, unsigned int length) {
  /*Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");*/
  String msg = "";
  int i = 0;
  int a=0;
  while (i < length) msg += (char)payload[i++];
int val = digitalRead(pir); //อ่านค่าสัญญาณ digital ขา8 ที่ต่อกับเซ็นเซอร์
/*Serial.print("val = "); // พิมพ์ข้อมความส่งเข้าคอมพิวเตอร์ "val = "
Serial.println(val);*/

float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    strcpy(celsiusTemp, "Failed");
    strcpy(fahrenheitTemp, "Failed");
    strcpy(humidityTemp, "Failed");
  }
  else {
    // Computes temperature values in Celsius + Fahrenheit and Humidity
    float hic = dht.computeHeatIndex(t, h, false);
    dtostrf(hic, 6, 2, celsiusTemp);
    float hif = dht.computeHeatIndex(f, h);
    dtostrf(hif, 6, 2, fahrenheitTemp);
    dtostrf(h, 6, 2, humidityTemp);
    // You can delete the following Serial.prints, it s just for debugging purposes
  }
  



  if (msg == "ON") {

    digitalWrite(LED_PIN, HIGH);
    Serial.println("ledon");
   
  }
  if (msg == "OFF") {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LEDOFF");
    
  }
  if (msg == "temp checking") {
    client.publish("esptemp",celsiusTemp);
  
    
    Serial.print("Temperature: "); 
    Serial.print(celsiusTemp);
    Serial.println(" *C");
  }
if (msg == "humidity checking") {
    client.publish("esphu",humidityTemp);
  
    
    Serial.print("Humidity: "); 
    Serial.print(humidityTemp);
    Serial.println("%");
  }
if (isNumeric(msg)){
  
  int x = msg.toInt();
  ledcWrite (ledChannel, (x*25.5));
}
  

 
    
    if (msg == "flashing"){
      while(a<=10){
digitalWrite(LED_PIN,HIGH);
delay(100);
digitalWrite(LED_PIN,LOW);
delay(100);
a++;
      }
      a =0;
    
    }
  
    
     
  // put your main code here, to run repeatedly:

  
  

}
