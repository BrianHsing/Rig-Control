#include <SPI.h>
#include <Ethernet.h>
#include <WebServer.h>
#include <Streaming.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
const byte PIN_8 = 8;
const byte PIN_7 = 7;
const byte PIN_6 = 6;
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
  "<title>礦機重新啟動</title>"
  "</head><body bgcolor=\"#0f1923\";><center>" ;

P(htmlFoot) = "</center></body></html>";

P(homePage) =
  "<p style=\"color: white; font-weight: bold; font-size: 4vh;\">礦機死當時，請點選下方按鈕重新啟動</p>";

P(form) =
  "<form action=\"http://172.16.10.10/PowerOn\" method=\"post\">"
  "<p style=\"color: white; font-weight: bold; font-size: 3vh;\">小軒的礦機:<br><input type=\"submit\" name=\"AMD\" value=\"PowerOn\" style=\"width:300px; height=300px ;font-size: 3vh;\"></p>"
  "<p style=\"color: white; font-weight: bold; font-size: 3vh;\">二姊的1660礦機:<br><input type=\"submit\" name=\"1660\" value=\"PowerOn\" style=\"width:300px; height=300px ;font-size: 3vh;\"></p>"
  "<p style=\"color: white; font-weight: bold; font-size: 3vh;\">小宇的AMD礦機:<br><input type=\"submit\" name=\"rig1\" value=\"PowerOn\" style=\"width:300px; height=300px ;font-size: 3vh;\"></p>"
  "<p style=\"color: white; font-weight: bold; font-size: 3vh;\">小宇的Nvidia礦機:<br><input type=\"submit\" name=\"rig2\" value=\"PowerOn\" style=\"width:300px; height=300px ;font-size: 3vh;\"></p>"
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
      if (strcmp(name, "AMD") == 0) {
        if (strcmp(value, "PowerOn") == 0) {
          server << "<p style=\"color: white; font-weight: bold; font-size: 3vh;\">重開成功。</p>";
          server.printP(back);
          digitalWrite(PIN_8, HIGH);
          delay(100);
          digitalWrite(PIN_8, LOW);
        }
      }
      if (strcmp(name, "1660") == 0) {
        if (strcmp(value, "PowerOn") == 0) {
          server << "<p style=\"color: white; font-weight: bold; font-size: 3vh;\">重開成功。</p>";
          server.printP(back);
          digitalWrite(PIN_7, HIGH);
          delay(100);
          digitalWrite(PIN_7, LOW);
        }
      }
      if (strcmp(name, "rig1") == 0) {
        if (strcmp(value, "PowerOn") == 0) {
          server << "<p style=\"color: white; font-weight: bold; font-size: 3vh;\">重開成功。</p>";
          server.printP(back);
          digitalWrite(PIN_6, HIGH);
          delay(100);
          digitalWrite(PIN_6, LOW);
        }
      }
      if (strcmp(name, "rig2") == 0) {
        if (strcmp(value, "PowerOn") == 0) {
          server << "<p style=\"color: white; font-weight: bold; font-size: 3vh;\">重開成功。</p>";
          server.printP(back);
          digitalWrite(PIN_5, HIGH);
          delay(100);
          digitalWrite(PIN_5, LOW);
        }
      }
    }
    server.printP(htmlFoot);
  }
}

void setup() {
  pinMode(PIN_8, OUTPUT);
  pinMode(PIN_7, OUTPUT);
  pinMode(PIN_6, OUTPUT);
  pinMode(PIN_5, OUTPUT);
  Ethernet.begin(mac, ip);
  webserver.setDefaultCommand(&defaultCmd);
  webserver.addCommand("PowerOn", &postCmd);
  webserver.begin();

}

void loop() {
  // listen for incoming clients
  webserver.processConnection();
}
