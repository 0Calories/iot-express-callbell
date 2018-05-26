#include <SPI.h>
#include <WiFi101.h>
#include "credentials.h" // Header file to hold values of SSID, password, local IP

/* For those interested, The credentials.h file should look something like this:
 #define SECRET_SSID "Your-SSID"
 #define SECRET_PASS "Your-Network-Password"
 IPAddress server(192,168,0,25);  
*/

char ssid[] = SECRET_SSID;    
char pass[] = SECRET_PASS;   

int port = 4200; // Port that the Express.js server is running on

int status = WL_IDLE_STATUS;

WiFiClient client;

int buttonPin = 0;
int redPin = 5;
int greenPin = 3; // I think the G and B LEDS on my RBG LED are swapped...
int bluePin = 4; 

int buttonToggle = 0;
bool canSummon = true;

void setup() {

  Serial.begin(9600);
  pinMode(buttonPin, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  setColour(255, 0, 0); // Initial colour of LED is red
  
  // Cancel if board has no wifi shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);

  // Initialize connection to WiFi
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    delay(1000);
  }
  Serial.println("Successfully connected to WiFi");
  setColour(0, 255, 0); // Set LED to green, indicating connection to WiFi
}

void loop() {

  // If cannot currently summon, block thread for 6 secs
  if (!canSummon) {
    delay(6000);
    setColour(0, 255, 0);
    canSummon = true;
  }

  buttonToggle = digitalRead(buttonPin);
  if (buttonToggle == HIGH) {
    summonRequest();
    setColour(255, 255, 0);
    delay(500);
  }
}

// Function for calling a POST HTTP request on the server
void summonRequest() {
  if (canSummon) {
    Serial.println("\nConnecting to Callbell server...");
    // if you get a connection, report back via serial:
    if (client.connect(server, port)) {
      Serial.println("Successfully connected, fired summon request!");
      // Send POST request
      client.println("POST /call");
      client.println();
      canSummon = false;
    }
  }
}

void setColour(int redVal, int greenVal, int blueVal) {
  analogWrite(redPin, redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin, blueVal);
}
