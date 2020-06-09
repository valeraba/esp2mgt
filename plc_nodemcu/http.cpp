/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

#include "http.h"
#include "config.h"

void debugLog(const __FlashStringHelper* aFormat, ...);
char localIp[16] = {0};


ESP8266WebServer server(80);
bool isAP       = false;
bool isConnect  = false;
String authPass = "";
String HTTP_User = "";
int    UID       = -1;


//---Соединение с WiFi----------
static bool ConnectWiFi(void) {

  // Если WiFi не сконфигурирован
  if (strcmp(EC_config.net.ssid, "none") == 0) {
    debugLog(F("WiFi is not config ...\n"));
    return false;
  }

  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.mode(WIFI_STA);

  // Пытаемся соединиться с точкой доступа
  debugLog(F("\nConnecting to: %s\n"), EC_config.net.ssid);
  WiFi.begin(EC_config.net.ssid, EC_config.net.pass);
  delay(1000);

  // Максиммум N раз проверка соединения (12 секунд)
  for ( int j = 0; j < 15; j++ ) {
    if (WiFi.status() == WL_CONNECTED) {
      debugLog(F("\nWiFi connect: "));
      //Serial.print(WiFi.localIP());
      //Serial.print("/");
      //Serial.print(WiFi.subnetMask());
      //Serial.print("/");
      //Serial.println(WiFi.gatewayIP());
      return true;
    }
    delay(1000);
    //Serial.print(WiFi.status());
  }
  debugLog(F("\nConnect WiFi failed ...\n"));
  return false;
}

//-------Старт WiFi---------
void WiFi_begin(void) {
  // Подключаемся к WiFi
  if (isAP) {
    debugLog(F("Start AP %s\n"), EC_config.net.name);
    WiFi.mode(WIFI_AP);
    WiFi.softAP(EC_config.net.name, EC_config.net.password);
    debugLog(F("Open http://192.168.4.1 in your browser\n"));
  }
  else {
    // Получаем статический IP если нужно
    WiFi.mode(WIFI_STA);
    isConnect = ConnectWiFi();
    if (isConnect) {
      if (EC_config.net.ip != (uint32_t)0 && !EC_config.net.dhcp)
        WiFi.config(EC_config.net.ip, EC_config.net.gw, EC_config.net.msk);
      debugLog(F("Open http://"));
      strncpy (localIp, WiFi.localIP().toString().c_str(), 16);
      debugLog(F("%s"), localIp);
      debugLog(F(" in your browser"));
    }
  }
}


/**
   Обработчик событий WEB-сервера
*/
void HTTP_loop(void) {
  server.handleClient();
}


// Функция проверки пароля
bool HTTP_checkAuth(const char* password) {
  //debugLog(F("password: %s\norig: %s\n"), password, EC_config.password);
  if (strcmp(password, EC_config.net.password) == 0)
    return true;
  return false;
}

// Проверка авторизации
bool HTTP_isAuth() {
  //Serial.print("AUTH ");
  if (server.hasHeader("Cookie")) {
    //Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    //Serial.print(cookie);

    if (cookie.indexOf("password=") != -1) {
      authPass = cookie.substring(cookie.indexOf("password=") + 9);
      return HTTP_checkAuth((char*)authPass.c_str());
    }
  }
  return false;
}


char tempBuf[10];
#define EC_STR(str) ;out+=(str);out+=
#define EC_BYTE(b) ;sprintf(tempBuf,"%u",(b));out+=tempBuf;out+=
#define EC_CHECK(b) ;if(b)out+="checked";out+=
#define EC_DEVICE_ID ;if(EC_config.net.deviceId <= 0x7fffffff)sprintf(tempBuf,"%u",EC_config.net.deviceId);else tempBuf[0]=0;out+=tempBuf;out+=
#define EC_HISTORY(b) ;if(EC_config.app.history&(1<<b))out+=" checked";out+=


// Страница авторизации
void loginHandler() {
  const char* msg = "";
  if (server.hasArg("password")) {
    String password = server.arg("password");

    if (HTTP_checkAuth(password.c_str())) {
      String header = "HTTP/1.1 301 OK\r\nSet-Cookie: password=" + password + "\r\nLocation: /\r\nCache-Control: no-cache\r\n\r\n";
      server.sendContent(header);
      debugLog(F("Login Success\n"));
      return;
    }
    msg = "неправильный пароль";
    debugLog(F("Login Failed\n"));
  }
  else {
    if (HTTP_isAuth()) {
      debugLog(F("logout\n"));
      String header = "HTTP/1.1 301 OK\r\nSet-Cookie: password=\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
      server.sendContent(header);
      return;
    }
  }

  String out =
    F("<html>" "\r\n"
      "<head>" "\r\n"
      "\t" "<meta charset='utf-8'/>" "\r\n"
      "\t" "<title>") EC_STR(EC_config.net.name) F("</title>" "\r\n"
      "\t" "<style>body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; } input {width:250px; height:28px}</style>" "\r\n"
      "</head>" "\r\n"
      "<body>" "\r\n"
      "<h1>Авторизация</h1>" "\r\n"
      "<form action='/login' method='POST'>" "\r\n"
      "\t" "<input type='password' name='password' placeholder='password' size='32' length='32'>" "\r\n"
      "\t" "<br><br>" "\r\n"
      "\t" "<input type='submit' value='Вход'>" "\r\n"
      "</form>" "\r\n"
      "<h3>") EC_STR(msg) F("</h3>"
      "</body>" "\r\n"
      "</html>" "\r\n");

  server.send(200, "text/html", out);
}

/**
   Перейти на страничку с авторизацией
*/
void HTTP_gotoLogin() {
  String header = "HTTP/1.1 301 OK\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
  server.sendContent(header);
}


// Оработчик главной страницы сервера
void mainHandler(void) {
  // Проверка авторизации

  if (!HTTP_isAuth()) {
    HTTP_gotoLogin();
    return;
  }

  /*/ Сохранение контроллера
  if (server.hasArg("relay")) {
    bool val = digitalRead(PIN_RELAY);
    digitalWrite(PIN_RELAY, !val);
    //server.sendContent("HTTP/1.1 301 OK\r\nLocation: /\r\nCache-Control: no-cache\r\n\r\n");
    server.sendContent("HTTP/1.1 303 See Other\r\nLocation: /\r\nCache-Control: no-cache\r\n\r\n");
    return;
  }*/

  const char* mode = "";
  if (isAP)
    mode = "Устройство в режиме точки доступа";

/*  const char* relayState;
  const char* relayCmd;
  if (digitalRead(PIN_RELAY)) {
    relayState = "включено";
    relayCmd = "Выключить";
  }
  else {
    relayState = "выключено";
    relayCmd = "Включить";
  }*/

  String out =
    F("<html>" "\r\n"
      "<head>" "\r\n"
      "\t" "<meta charset = \"utf-8\"/>" "\r\n"
      "\t" "<title>") EC_STR(EC_config.net.name) F("</title>" "\r\n"
      "\t" "<style>body{ background-color: #dddddd; font-family: Arial, Helvetica, Sans-Serif; color: #000088; }</style>" "\r\n"
      "</head>" "\r\n"
      "<body>" "\r\n"
      "<h1>") EC_STR(EC_config.net.name) F("</h1>" "\r\n"
      "<ul>" "\r\n"
      "\t" "<li><a href='/config'>Настройка параметров сети</a></li>" "\r\n"
      "\t" "<li><a href='/login'>Выход</a></li>" "\r\n"
      "</ul>" "\r\n"
      "<h3>") EC_STR(mode) F("</h3>" "\r\n"
/*      "<h3>Реле ") EC_STR(relayState) F("</h3>" "\r\n"
      "<form action='/' method='POST'>" "\r\n"
      "\t" "<input type='submit' name='relay' value='") EC_STR(relayCmd) F(" реле'>" "\r\n"
      "</form>" "\r\n"*/
      "<button onclick='unbind()'>Отвязать датчики</button>" "\r\n"

      "<p><b>Список исторических данных</b></p>" "\r\n"
      "<input type='checkbox' id='p0'") EC_HISTORY(0) F(">D1<br>" "\r\n"
      "<input type='checkbox' id='p1'") EC_HISTORY(1) F(">D2<br>" "\r\n"
      "<input type='checkbox' id='p2'") EC_HISTORY(2) F(">D5<br>" "\r\n"
      "<input type='checkbox' id='p3'") EC_HISTORY(3) F(">D6<br>" "\r\n"
      "<input type='checkbox' id='p4'") EC_HISTORY(4) F(">RX<br>" "\r\n"
      "<input type='checkbox' id='p5'") EC_HISTORY(5) F(">variable_1<br>" "\r\n"
      "<input type='checkbox' id='p6'") EC_HISTORY(6) F(">variable_2<br>" "\r\n"
      "<input type='checkbox' id='p7'") EC_HISTORY(7) F(">variable_3<br>" "\r\n"
      "<input type='checkbox' id='p8'") EC_HISTORY(8) F(">variable_4<br>" "\r\n"
      "<input type='checkbox' id='p9'") EC_HISTORY(9) F(">variable_5<br>" "\r\n"
      "<input type='checkbox' id='p10'") EC_HISTORY(10) F(">variable_6<br>" "\r\n"
      "<input type='checkbox' id='p11'") EC_HISTORY(11) F(">variable_7<br>" "\r\n"
      "<input type='checkbox' id='p12'") EC_HISTORY(12) F(">variable_8<br>" "\r\n"
      "<p><button onclick = 'history()'>Сохранить список</button></p>" "\r\n"

      "<script>" "\r\n"
      "\t" "function unbind() {" "\r\n"
      "\t\t" "var xhr = new XMLHttpRequest();" "\r\n"
      "\t\t" "xhr.open('POST', '/unbind');" "\r\n"
      "\t\t" "xhr.onload = function() { alert('OK') };" "\r\n"
      "\t\t" "xhr.onerror = function() { alert('ERROR') };" "\r\n"
      "\t\t" "xhr.send();" "\r\n"
      "\t" "}" "\r\n"

      "\t" "function history() {" "\r\n"
      "\t\t" "var value = 0;" "\r\n"
      "\t\t" "for (var i = 0; i < 13; i++) {" "\r\n"
      "\t\t\t" "if (document.getElementById('p' + i).checked)" "\r\n"
      "\t\t\t\t" "value |= (1 << i); " "\r\n"
      "\t\t" "}" "\r\n"
      "\t\t" "var xhr = new XMLHttpRequest();" "\r\n"
      "\t\t" "xhr.open('GET', '/history?val=' + value);" "\r\n"
      "\t\t" "xhr.onload = function() { alert('OK') };" "\r\n"
      "\t\t" "xhr.onerror = function() { alert('ERROR') };" "\r\n"
      "\t\t" "xhr.send();" "\r\n"
      "\t" "}" "\r\n"

      "</script>" "\r\n"
            
      "</body>" "\r\n"
      "</html>" "\r\n");

  server.send ( 200, "text/html", out );
}


//-------------------------------------------------
void setConfig() {
  // Проверка прав администратора
  if (!HTTP_isAuth()) {
    //TODO
    return;
  }

  if (server.hasArg("name")) strcpy(EC_config.net.name, server.arg("name").c_str());
  if (server.hasArg("password")) strcpy(EC_config.net.password, server.arg("password").c_str());
  if (server.hasArg("ssid")) strcpy(EC_config.net.ssid, server.arg("ssid").c_str());
  if (server.hasArg("pass")) strcpy(EC_config.net.pass, server.arg("pass").c_str());
  if (server.hasArg("dhcp")) EC_config.net.dhcp = true; else EC_config.net.dhcp = false;
  if (server.hasArg("ip0")) EC_config.net.ip[0] = atoi(server.arg("ip0").c_str());
  if (server.hasArg("ip1")) EC_config.net.ip[1] = atoi(server.arg("ip1").c_str());
  if (server.hasArg("ip2")) EC_config.net.ip[2] = atoi(server.arg("ip2").c_str());
  if (server.hasArg("ip3")) EC_config.net.ip[3] = atoi(server.arg("ip3").c_str());
  if (server.hasArg("msk0")) EC_config.net.msk[0] = atoi(server.arg("msk0").c_str());
  if (server.hasArg("msk1")) EC_config.net.msk[1] = atoi(server.arg("msk1").c_str());
  if (server.hasArg("msk2")) EC_config.net.msk[2] = atoi(server.arg("msk2").c_str());
  if (server.hasArg("msk3")) EC_config.net.msk[3] = atoi(server.arg("msk3").c_str());
  if (server.hasArg("gw0")) EC_config.net.gw[0] = atoi(server.arg("gw0").c_str());
  if (server.hasArg("gw1")) EC_config.net.gw[1] = atoi(server.arg("gw1").c_str());
  if (server.hasArg("gw2")) EC_config.net.gw[2] = atoi(server.arg("gw2").c_str());
  if (server.hasArg("gw3")) EC_config.net.gw[3] = atoi(server.arg("gw3").c_str());
  if (server.hasArg("host1")) strcpy(EC_config.net.host1, server.arg("host1").c_str());
  if (server.hasArg("host2")) strcpy(EC_config.net.host2, server.arg("host2").c_str());
  if (server.hasArg("deviceId")) EC_config.net.deviceId = strtoul(server.arg("deviceId").c_str(), 0, 0);
  if (server.hasArg("key")) strcpy(EC_config.net.key, server.arg("key").c_str());
  EC_save();
  String header = "HTTP/1.1 301 OK\r\nLocation: /config\r\nCache-Control: no-cache\r\n\r\n";
  server.sendContent(header);
  return;
}

//-------------------------------------------------
void getConfig() {
  // Проверка прав администратора
  if (!HTTP_isAuth()) {
    HTTP_gotoLogin();
    return;
  }

  String out =
    F("<html>" "\r\n"
      "<head>" "\r\n"
      "\t" "<meta charset = \"utf-8\"/>" "\r\n"
      "\t" "<title>") EC_STR(EC_config.net.name) F("</title>" "\r\n"
      "\t" "<style>" "\r\n"
      "\t\t" "body{ background-color: #dddddd; font-family: Arial, Helvetica, Sans-Serif; color: #000088; }" "\r\n"
      "\t\t" "#dhcp:checked ~ table .trIp{ display: none;}" "\r\n"
      "\t" "</style>" "\r\n"
      "</head>" "\r\n"
      "<body>" "\r\n"
      "\t" "<h1>Настройка параметров сети</h1>" "\r\n"
      "\t" "<ul>" "\r\n"
      "\t\t" "<li><a href='/'>Главная</a></li>" "\r\n"
      "\t\t" "<li><a href='/login'>Выход</a></li>" "\r\n"
      "\t\t" "<li><a href='/reboot'>Перезагрузка</a></li>" "\r\n"
      "\t" "</ul>" "\r\n"
      "\t" "<form action='/config'method='POST'>" "\r\n"
      "\t\t" "<h3>Параметры в режиме точки доступа</h3>" "\r\n"
      "\t\t" "<table>" "\r\n"
      "\t\t\t" "<tr><td>Название:</td><td><input name='name' value='") EC_STR(EC_config.net.name) F("' size=32 length=32></td></tr>" "\r\n"
      "\t\t\t" "<tr><td>Пароль:</td><td><input name='password' value='") EC_STR(EC_config.net.password) F("' size=32 length=32 type='password'></td></tr>" "\r\n"
      "\t\t" "</table>" "\r\n"
      "\t\t" "<h3>Параметры в режиме клиента</h3>" "\r\n"
      "\t\t" "<input id='dhcp' name='dhcp' type='checkbox' value='on' ") EC_CHECK(EC_config.net.dhcp) F("/>" "\r\n"
      "\t\t" "<label for='dhcp'>DHCP</label>" "\r\n"
      "\t\t" "<table>" "\r\n"
      "\t\t\t" "<tr><td>Имя сети:</td><td><input name='ssid' value='") EC_STR(EC_config.net.ssid) F("' size=32 length=32></td></tr>" "\r\n"
      "\t\t\t" "<tr><td>Пароль:</td><td><input name='pass' value='") EC_STR(EC_config.net.pass) F("' size=32 length=32 type='password'></td></tr>" "\r\n"
      "\t\t\t" "<tr class='trIp'><td>IP-адрес:</td><td><input name='ip0' value='") EC_BYTE(EC_config.net.ip[0]) F("' size=3 length=3> . <input name='ip1' value='") EC_BYTE(EC_config.net.ip[1]) F("' size=3 length=3> . <input name='ip2' value='") EC_BYTE(EC_config.net.ip[2]) F("' size=3 length=3> . <input name='ip3' value='") EC_BYTE(EC_config.net.ip[3]) F("' size=3 length=3></td></tr>" "\r\n"
      "\t\t\t" "<tr class='trIp'><td>IP-маска:</td><td><input name='msk0' value='") EC_BYTE(EC_config.net.msk[0]) F("' size=3 length=3> . <input name='msk1' value='") EC_BYTE(EC_config.net.msk[1]) F("' size=3 length=3> . <input name='msk2' value='") EC_BYTE(EC_config.net.msk[2]) F("' size=3 length=3> . <input name='msk3' value='") EC_BYTE(EC_config.net.msk[3]) F("' size=3 length=3></td></tr>" "\r\n"
      "\t\t\t" "<tr class='trIp'><td>IP-шлюз:</td><td><input name='gw0' value='") EC_BYTE(EC_config.net.gw[0]) F("' size=3 length=3> . <input name='gw1' value='") EC_BYTE(EC_config.net.gw[1]) F("' size=3 length=3> . <input name='gw2' value='") EC_BYTE(EC_config.net.gw[2]) F("' size=3 length=3> . <input name='gw3' value='") EC_BYTE(EC_config.net.gw[3]) F("' size=3 length=3></td></tr>" "\r\n"
      "\t\t" "</table>" "\r\n"
      "\t\t" "<h3>Подключение к MGT серверу</h3>" "\r\n"
      "\t\t" "<table>" "\r\n"
      "\t\t\t" "<tr><td>Адрес сервера 1:</td><td><input name='host1' value='") EC_STR(EC_config.net.host1) F("' size=32 length=32></td></tr>" "\r\n"
      "\t\t\t" "<tr><td>Адрес сервера 2:</td><td><input name='host2' value='") EC_STR(EC_config.net.host2) F("' size=32 length=32></td></tr>" "\r\n"
      "\t\t\t" "<tr><td>ID устройства : </td><td><input name='deviceId' value='") EC_DEVICE_ID F("' size=32 length=32></td></tr>" "\r\n"
      "\t\t\t" "<tr><td>Ключ авторизации : </td><td><input name='key' value='") EC_STR(EC_config.net.key) F("' size=32 length=32></td></tr>" "\r\n"
      "\t\t" "</table>" "\r\n"
      "\t\t" "<br>" "\r\n"
      "\t\t" "<input type = 'submit' value='Сохранить'>" "\r\n"
      "\t" "</form>" "\r\n"
      "</body>" "\r\n"
      "</html>" "\r\n");
  server.send(200, "text/html", out);
}

// Удалить все привязки к датчикам
static void unbindHandler() {
    deleteSensor();
    server.send(200, "text/html", "");
}

// Исторические данные
static void historyHandler() {
    if (server.hasArg("val")) {
        EC_config.app.history = atoi(server.arg("val").c_str());
        EC_save();
    }
    server.send(200, "text/html", "");
}

// Перезагрузка
void rebootHandler(void) {
  String out =
    F("<html>" "\r\n"
      "<head>" "\r\n"
      "\t" "<meta charset='utf-8'/>" "\r\n"
      "\t" "<meta http-equiv='refresh' content='15;URL=/'>" "\r\n"
      "\t" "<title>") EC_STR(EC_config.net.name) F("</title>" "\r\n"
      "\t" "<style> body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; } </style>" "\r\n"
      "</head>" "\r\n"
      "<body>" "\r\n"
      "\t" "<h1>Перезагрузка контроллера</h1>" "\r\n"
      "\t" "<p><a href=\"/\">Через 15 сек будет переадресация на главную</a>" "\r\n"
      "</body>" "\r\n"
      "</html>");
  server.send(200, "text/html", out);
  delay(1000);
  ESP.reset();
}

// Старт WEB сервера
void HTTP_begin(void) {
  server.on("/", mainHandler);
  server.on("/config", HTTP_GET, getConfig);
  server.on("/config", HTTP_POST, setConfig);
  server.on("/login", loginHandler);
  server.on("/unbind", unbindHandler);
  server.on("/history", historyHandler);
  server.on("/reboot", rebootHandler);
  //server.onNotFound(notFoundHandler);
  //here the list of headers to be recorded
  const char * headerkeys[] = {"User-Agent", "Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  //ask server to track these headers
  server.collectHeaders(headerkeys, headerkeyssize);

  server.begin();
  debugLog(F("HTTP server started ...\n"));
}
