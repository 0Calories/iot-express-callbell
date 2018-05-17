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

void setup() {

  Serial.begin(9600);

  // Cancel if board has no wifi shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  // Initialize connection to WiFi
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    // Wait 1 second for connection:
    delay(1000);
  }
  Serial.println("Successfully connected to WiFi");

  summonRequest();
}

void loop() {
  // If WiFi is unavailable, give up on life :(
  if (!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting from server.");
    client.stop();
    while (true) {;}
  }

  // TODO: Check if button has been pressed and call summonRequest()
}

// Function for calling a POST HTTP request on the server
void summonRequest() {
  Serial.println("\nConnecting to Callbell server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, port)) {
    Serial.println("Successfully connected, fired summon request!");
    // Send POST request
    client.println("POST /call");
    client.println();
  }
}
