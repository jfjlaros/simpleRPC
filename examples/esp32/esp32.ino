#include <WiFi.h>
#include <simpleRPC.h>

#include "config.h"

WiFiServer server(PORT);


int ping(int a) {
  return a;
}


void setup() {
  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    while (client.connected()) {
      interface(
        client,
        ping, F("ping: Echo a value. @data: Value. @return: Value of data."));
    }
    client.stop();
  }
}
