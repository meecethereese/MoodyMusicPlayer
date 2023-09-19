#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>

#define BUZZER_PIN 4
#define LEDC_CHANNEL 0
#define LEDC_FREQ 1000
#define C5 523
#define D5 587
#define F5 698
#define E5 659
#define B4 494
#define C4 261
#define E4 329
#define G4 392
#define A3 220
#define B3 247
#define C3 130
#define G3 196

const char* ssid = "TropicalRetreat-guest";
const char* password = "wifisignal943";
int globalState = 0;

AsyncWebServer server(80);

// put your setup code here, to run once:
void setup()
{
  // Initialize LEDC for PWM
  ledcSetup(LEDC_CHANNEL, LEDC_FREQ, 10);
  ledcAttachPin(BUZZER_PIN, LEDC_CHANNEL);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(115200);
  delay(1000);

  // Connect to Wi-Fi (Hotspot)
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }

  Serial.println("Connected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialize mDNS
  if (!MDNS.begin("shellhacksesp")) 
  {
    Serial.println("Error setting up MDNS responder!");
  } 
  else 
  {
    Serial.println("MDNS responder started");
  }

  server.on("/happy", HTTP_GET, [](AsyncWebServerRequest *request){
    getHappy();
    request->send(200, "text/plain", "Happy state received.");
  });

  server.on("/sad", HTTP_GET, [](AsyncWebServerRequest *request){
    getSad();
    request->send(200, "text/plain", "Sad state received.");
  });

  server.on("/angry", HTTP_GET, [](AsyncWebServerRequest *request){
    getAngry();
    request->send(200, "text/plain", "Angry state received.");
  });

  server.on("/neutral", HTTP_GET, [](AsyncWebServerRequest *request){
    getHappy();
    request->send(200, "text/plain", "Neutral state received.");
  });

  server.begin();

  MDNS.addService("http", "tcp", 80);
}

// put your main code here, to run repeatedly:
void loop() 
{
  switch (globalState)
  {
    case 1:
      marioDeath();
      globalState = 0;
  }

}

void getHappy()
{
  Serial.println("Received GET request on /happy");
  
  globalState = 1;

  Serial.println("State is happy");
}

void getSad()
{
  Serial.println("Received GET request on /sad");

  globalState = 2;

  Serial.println("State is sad");
}

void getAngry()
{
  Serial.println("Received GET request on /angry");

  globalState = 3;

  Serial.println("State is sad");
}

void getNeutral()
{
  Serial.println("Received GET request on /neutral");

  globalState = 1;

  Serial.println("State is neutral");
}

void marioDeath()
{
  int dash = 3000 / 88;
  
  tone(BUZZER_PIN, F5);
  delay(dash);
  noTone(BUZZER_PIN);
  delay(dash);
  fade(F5, dash * 2, 255);
  fade(E5, dash * 14, 255);
  fade(F5, dash * 3, 255);
  tone(BUZZER_PIN, D5);
  delay(dash);
  fade(D5, dash * 2, 255);
  fade(C5, dash * 2, 255);
  fade(D5, dash * 2, 255);
  fade(C5, dash * 11, 255);
  fade(D5, dash * 19, 255);
  fade(G4, dash * 10, 255);
  fade(B4, dash * 2, 255);
  fade(C4, dash * 9, 255);
  fade(B4, dash * 14, 255);
  fade(E4, dash * 3, 255);
  tone(BUZZER_PIN, E4);
  fade(C4, dash * 15, 255);
  fade(G4, dash * 24, 255);
  fade(G3, dash * 3, 255);
  fade(C3, dash * 3, 255);
  fade(G3, dash * 5, 255);
  tone(BUZZER_PIN, G3);
  delay(dash);
  fade(G3, dash * 2, 255);
  fade(A3, dash * 2, 255);
  fade(B3, dash * 11, 255);
}

void fade(int note, int fade, int volume)
{
  tone(BUZZER_PIN, note);
  delay(2 * fade/3);

  for (int i = 0; i <= fade/3; i++)
  {
    analogWrite(BUZZER_PIN, volume);
    volume = map(i, 0, fade/3, 255, 0);
  }

  noTone(BUZZER_PIN);
}