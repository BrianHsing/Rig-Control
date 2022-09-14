#include <SPI.h>
#include <Ethernet.h>
#include <WebServer.h>
#include <Streaming.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:

const byte PIN_5 = 5;
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(172, 16, 10, 10);
WebServer webserver("", 80);
//

P(htmlHead) =
  "<!doctype html><html>"
  "<head><meta charset=\"utf-8\">"
  "<title>礦機啟動與關閉</title>"
  "</head><body bgcolor=\"#0f1923\";><center>" ;

P(htmlFoot) = "</center></body></html>";

P(homePage) =
  "<p style=\"color: white; font-weight: bold; font-size: 4vh;\">礦機啟動與關閉</p>";

P(form) =
  "<form action=\"http://172.16.10.10/poweron\" method=\"post\">"
  "<p style=\"color: white; font-weight: bold; font-size: 3vh;\">Rig Power:<br><input type=\"submit\" name=\"rig\" value=\"on\" style=\"width:300px; height=300px ;font-size: 3vh;\"><br><input type=\"submit\" name=\"rig\" value=\"off\" style=\"width:300px; height=300px ;font-size: 3vh;\"></p>"
  "</form>";
P(back) =
  "<form action=\"http://172.16.10.10\" method=\"post\">"
  "<input type=\"submit\" name=\"button\" value=\"back\" style=\"width:300px; height=300px ;font-size: 3vh;\">"
  "</form>";

void defaultCmd(WebServer &server, WebServer::ConnectionType type, char *, bool) {
  server.httpSuccess();
  if (type != WebServer::HEAD) {
    server.printP(htmlHead);
    server.printP(homePage);
    server.printP(form);
    server.printP(htmlFoot);
  }
}

void postCmd(WebServer &server, WebServer::ConnectionType type, char *, bool) {
  char name[16], value[16];
  server.httpSuccess();

  if (type == WebServer::POST) {
    server.printP(htmlHead);
    while (server.readPOSTparam(name, 16, value, 16)) {
      if (strcmp(name, "rig") == 0) {
        if (strcmp(value, "on") == 0) {
          server << "<p style=\"color: white; font-weight: bold; font-size: 3vh;\">開啟成功。</p>";
          server.printP(back);
          digitalWrite(PIN_5, HIGH);
          delay(100);
          digitalWrite(PIN_5, LOW);
          delay(1000);
          break;
        }
        if (strcmp(value, "off") == 0) {
          server << "<p style=\"color: white; font-weight: bold; font-size: 3vh;\">關閉成功。</p>";
          server.printP(back);
          digitalWrite(PIN_5, HIGH);
          delay(1000);
          digitalWrite(PIN_5, LOW);
          delay(1000);
        }
      }
    }
    server.printP(htmlFoot);
  }
}

void setup() {

  pinMode(PIN_5, OUTPUT);
  Ethernet.begin(mac, ip);
  webserver.setDefaultCommand(&defaultCmd);
  webserver.addCommand("poweron", &postCmd);
  webserver.begin();

}

void loop() {
  // listen for incoming clients
  webserver.processConnection();
}
