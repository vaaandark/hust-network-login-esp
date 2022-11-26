#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include "config.h"

String urlencode(String url) {
  String res = "";
  char buf[4];
  for (int i = 0; i < url.length(); ++i) {
    if (isalnum(url[i]) || strchr(".~_-", url[i])) {
      res.concat(url[i]);
    } else {
      sprintf(buf, "%%%02X", url[i]);
      res.concat(buf);
    }
  }
  return res;
}

void try_connect_wifi(const char *ssid, const char *password) {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }
  Serial.println();
  Serial.print("Wifi connected at ");
  Serial.println(WiFi.localIP());
  delay(1000);
}

String get_querystr(WiFiClient &client, const char *host, int port) {
  client.connect(host, port);
  String request = (String)"GET / HTTP/1.1\r\nHost: " + host + "\r\nUser-Agent: curl/7.74.0\r\nAccept: */*\r\n\r\n";
  client.print(request);
  String response = client.readString();
  int end = response.indexOf("\'</script>");
  int begin = response.indexOf("wlanuserip");
  String querystr = response.substring(begin, end);
  Serial.println();
  Serial.println("querystr:");
  Serial.println(querystr);
  return urlencode(querystr);
}

void try_login(WiFiClient &client, String &querystr) {
  if (querystr.length() < 100) {
    Serial.println("Query string is too short! Pass!");
    return;
  }
  const char *post_host = "192.168.50.3";
  int post_port = 8080;
  String content = (String)"userId=" + USERNAME + "&password=" + PASSWORD + "&service=&queryString=" + querystr + "&passwordEncrypt=false";
  client.connect(post_host, post_port);
  String post = (String)"POST /eportal/InterFace.do?method=login HTTP/1.1\r\n" +
    "Host: " + post_host + "\r\n" +
    "Accept: */*\r\n" +
    "User-Agent: hust-network-login-esp\r\n" +
    "Content-Length: " + content.length() + "\r\n" +
    "Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n\r\n" +
    content;
  Serial.println();
  Serial.println("post:");
  Serial.println(post);
  client.print(post);
}

void setup(){
  Serial.begin(115200);
  try_connect_wifi(SSID, SSID_PASSWORD);
  delay(1000);
}

void loop(){
  WiFiClient client;
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
  }
  String querystr = get_querystr(client, "baidu.com", 80);
  try_login(client, querystr);
  delay(15000);
}
