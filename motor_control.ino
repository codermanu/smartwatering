#include <ESP8266WiFi.h>
#define LED D4  // LED at GPIO4 D2

const char* ssid = "yourwifiusername";
const char* password = "yourwifipwd";
unsigned char status_led=0;

WiFiServer server(80);

void setup() {
Serial.begin(9600);
pinMode(LED, OUTPUT);
digitalWrite(LED, LOW);

// Connect to WiFi network
Serial.println();
Serial.println();
Serial.print("Connecting to");
Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

// Start the server
server.begin();
Serial.println("Server started at");
Serial.println(WiFi.localIP());

}

void loop() {

// Check if a client has connected
WiFiClient client = server.available();
if (!client) {
return;
}

// Wait until the client sends some data
Serial.println("new client");
while (! client.available())
{
delay (1);
}

// Read the first line of the request
String req = client.readStringUntil('\r');
Serial.println(req);
client.flush();

// Match the request

if (req.indexOf("/motoroff") != -1)  {
status_led=0;
digitalWrite(LED, LOW);
Serial.println("MOTOR OFF");
}
else if(req.indexOf("/motoron") != -1)
{
status_led=1;
digitalWrite(LED,HIGH);
Serial.println("MOTOR ON");
}


// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");
client.println("");

client.println("<!DOCTYPE HTML>");
client.println("<HTML>");
client.println("<body bgcolor='#32CD32'>");
client.println("<center><H1 color=#008CBA> Water Pump Control </H1> </center>");
client.println("<br />");

client.println("<a href=\"/motoron\"\"> <center><button style='FONT-SIZE: 50px; HEIGHT: 200px; WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px; BACKGROUND-COLOR: #008CBA; border-radius: 12px; box-shadow: 0 8px 16px 0 rgba(0,0,0,0.2), 0 6px 20px 0 rgba(0,0,0,0.19);'> MOTOR ON </button></center> </a><br><br>");
client.println("<a href=\"/motoroff\"\"> <center><button style='FONT-SIZE: 50px; HEIGHT: 200px; WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px; BACKGROUND-COLOR: #008CBA; border-radius: 12px; box-shadow: 0 8px 16px 0 rgba(0,0,0,0.2), 0 6px 20px 0 rgba(0,0,0,0.19);'> MOTOR OFF </button> </center></a>");

client.println("</body>");
client.println("</html>");

delay(1);
Serial.println("Client disconnected");
Serial.println("");

}
