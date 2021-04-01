#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "*********";       //Network name          
const char *password = "******";            //network password   


#define IFTTT_API_KEY "yYHSVT_0kpqScBE-mWcyU"
#define IFTTT_EVENT_NAME "suBasti"

WiFiClient wifi_istemci;
HTTPClient http;

int sensorPin = A0;               //Sensörü bağladığımız pin
int esikDegeri =450;              //Su miktarı için eşik değeri
int veri;                          

void setup() {
  WiFi.mode(WIFI_STA);                        // ESP8266 istasyon moduna alınıyor. 
  WiFi.begin(ssid, password);                 // SSID ve şifre girilierek wifi başlatılıyor.

  Serial.print("Bağlantı kuruluyor");
  while (WiFi.status() != WL_CONNECTED)       // Wifi bağlantısı sağlanana kadar bekleniyor.
  { 
    delay(500);                               // Bu arada her 500 ms de bir seri ekrana yan yana noktalar yazdırılarak
    Serial.print(".");                        // görsellik sağlanıyor.
  }
  
  Serial.println("");                         // Bir alt satıra geçiliyor.

  
  Serial.begin(115200);
  Serial.print("Bağlantı kuruluyor"); 
  pinMode(sensorPin, INPUT); 
}
void loop() {
  veri = analogRead(sensorPin);    //Sensörden analog veriyi okuyoruz.
  
  if(veri > esikDegeri){           //Sensör verisi eşik değerini geçerse if içerisindeki kodlar uygulanır.
    //Serial.println("veri alabiliyorum");
    Serial.println(veri);
    calistir();
    
    delay(1000);

  }
  else{                            //Sensör verisi eşik değerinden küçük olursa if içerisindeki kodlar uygulanır.
    
    Serial.println(veri);
    
    delay(1000);
    
  }
}
//-------------------------------------------------------------------------
void calistir()
{
  
    char ifttt_url[255];
    sprintf(ifttt_url,"http://maker.ifttt.com/trigger/%s/with/key/%s",IFTTT_EVENT_NAME,IFTTT_API_KEY);
    Serial.printf("Http Request -> %s",ifttt_url);
    http.begin(ifttt_url); 
    int httpCode = http.GET();                                                                 
    String payload = http.getString();  
    Serial.print("\r\nHttp Response <- ");
    Serial.println(payload);
    Serial.printf("Http Code: %d\r\n",httpCode);
    http.end();
  
}
