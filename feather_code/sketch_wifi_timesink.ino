#include <WiFi.h>
#include <HTTPClient.h>

#define RXD2 16
#define TXD2 17

String SSID;
String PASSWORD;
//"Detkin IOT South" "s0uthSide" 
//"Detkin IOT North" "n0rthC0untry" 
//"Keterrer IOT" "theCl0ud";
const String GET_IP_ADDRESS = "https://www.trackip.net/ip";
const String GEOLOCATION_API_SERVER = "https://api.ip2location.io/?key=API_KEY&ip=";

const String WEATHER_API_KEY = "API_KEY";
const String WEATHER_API_SERVER = "https://api.openweathermap.org/data/2.5/weather?";

const String TIME_API_SERVER = "https://api.geotimezone.com/public/timezone?";

char ip_address[16];
char latitude[10] = "";
char longitude[10] = "";

/**
 * MOSI: 18
 * MISO: 19
 * SCK: 5
 * SS: 33
 */

const String weather_target = "id\":";
const String temp_target = "temp\":";
const String latitude_target = "latitude\":";
const String longitude_target = "longitude\":";
const String datetime_target = "datetime\":\"";

void send_string(String s) {
  for (int i = 0; i < s.length(); i++) {
    Serial2.print(s.charAt(i));
    delay(10);
  }
  Serial2.print('\n');
}

char wait_for_response() {
  while (!Serial2.available()){
    delay(1000); //try again in 1 second
  }
  char last = ' ';
  while (Serial2.available()){ //read all stall messages
    last = Serial2.read();
  }
  return last;
}

char wait_for_real_response() {
  char last = 's';
  while (1) {
    while (!Serial2.available()){
      delay(1000); //try again in 1 second
    }
    while (Serial2.available()){
      last = Serial2.read();
    }
    if (last == 0) {
      return last;
    }
  }
}


void send_wifi_networks() {
  wait_for_response();
  char num_networks = (char) WiFi.scanNetworks();
  Serial2.print(num_networks);
  wait_for_response(); //clear buffer
  char response = wait_for_response();
  while(1) {
    send_string(WiFi.SSID((int) response));
    char response2 = wait_for_response();
    if (response2 == response) {
      SSID = WiFi.SSID(response);
      break;
    } else {
      response = response2;
    }
  }
  WiFi.scanDelete();
}

void await_wifi_credentials() {
  while(!Serial2.available());
  PASSWORD = Serial2.readStringUntil('\0');
}

void setup() {
  Serial2.begin(9600, SERIAL_8N2, RXD2, TXD2);
  while (!Serial2);
  send_wifi_networks();
  while(WiFi.status() != WL_CONNECTED){
    await_wifi_credentials();
    int result = WiFi.begin(SSID, PASSWORD);
    int start_time = millis();
    while(WiFi.status() != WL_CONNECTED && (millis() - start_time < 10000)) {
      delay(1000);
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial2.print('S');
      break;
    } else {
      Serial2.print('F');
    }
  }
  delay(1000);
}

void refresh_time();
void refresh_weather();

void loop() {
  while (!Serial2.available()){
    delay(1000); //try again in 10 seconds
  }
  char action_character;
  while (Serial2.available()){
    action_character = Serial2.read();
  }
  switch (action_character) {
    case 'w':
      refresh_weather();
      break;
    case 't':
      refresh_time();
      break;
    default:
      break;
  }
}

byte parse_payload_temp(const String* payload) {
  int ind = 0;
  String substring = payload->substring(ind, ind + 6);
  while(!temp_target.equals(substring)) {
    ind++;
    substring = payload->substring(ind, ind + 6);
  }
  ind += 6;
  int end = ind + 1;
  while(!(payload->charAt(end) == '.')) {
    end++;
  }
  String temp_string = payload->substring(ind, end);
  int int_temp = temp_string.toInt();
  return (byte) int_temp;
}

char parse_payload_weather(const String* payload) {
  int ind = 0;
  String substring = payload->substring(ind, ind + 4);
  while(!weather_target.equals(substring)) {
    ind++;
    substring = payload->substring(ind, ind + 4);
  }
  ind+=4;
  switch (payload->charAt(ind)) {
    case '2':
      return 't'; //thunder
    case '3':
    case '5':
      return 'r'; //rain
    case '6':
      return 's'; //snow
    case '7':
      return 'a'; //air quality
    case '8':
      char last = payload->charAt(ind + 2);
      if (last == '0')
        return 'c'; //clear
      if (last == '1' || last == '2' || last == '3')
        return 'p'; //partly cloudy
      if (last == '4')
        return 'l'; //cloudy
      break;
  }
  return 'F'; //failure
}

void refresh_ip_address() {
  if(WiFi.status() != WL_CONNECTED) {
    strcpy(ip_address, "");
  }
  HTTPClient http;
  http.begin(GET_IP_ADDRESS.c_str());
  int httpResponseCode = http.GET();
  if (httpResponseCode == 200) {
    strcpy(ip_address, http.getString().c_str());
  } else {
    strcpy(ip_address, "");
  }
  http.end();
}

void refresh_lat_long(String* lat_long_ptr) {
  if(WiFi.status() != WL_CONNECTED) {
    *lat_long_ptr = "";
  }
  HTTPClient http;
  String path = GEOLOCATION_API_SERVER + String(ip_address);
  http.begin(path.c_str());
  int httpResponseCode = http.GET();
  if (httpResponseCode == 200) {
    *lat_long_ptr = http.getString();
  } else {
    *lat_long_ptr = "";
  }
  http.end();
}

void set_lat_long(const String* payload) { //latitude/longitude rounded to -1
  strcpy(latitude, "");
  strcpy(longitude, "");
  int ind = 0;
  String substring = payload->substring(ind, ind + 10);
  while(!latitude_target.equals(substring)) {
    ind++;
    substring = payload->substring(ind, ind + 10);
  }
  ind += 10;
  int end = ind + 1;
  while(!(payload->charAt(end) == '.')) {
    end++;
  }
  end += 6;
  strcpy(latitude, payload->substring(ind, end).c_str());

  ind = 0;
  substring = payload->substring(ind, ind + 11);
  while(!longitude_target.equals(substring)) {
    ind++;
    substring = payload->substring(ind, ind + 11);
  }
  ind += 11;
  end = ind + 1;
  while(!(payload->charAt(end) == '.')) {
    end++;
  }
  end += 6;
  strcpy(longitude, payload->substring(ind, end).c_str());
}

void refresh_weather() {
  if(WiFi.status() != WL_CONNECTED) {
    Serial2.print('F');
    return;
  }
  refresh_ip_address(); //refresh ip address
  if (strlen(ip_address) == 0) {
    Serial2.print('F');
    return;
  }
  String lat_long;
  refresh_lat_long(&lat_long);
  if (lat_long == "") {
    Serial2.print('F');
    return;
  }
  set_lat_long(&lat_long);
  if (strlen(latitude) == 0 || strlen(longitude) == 0) {
    Serial2.print('F');
    return;
  }

  HTTPClient http;
  String path = WEATHER_API_SERVER + "lat=" + String(latitude);
  path += "&lon=" + String(longitude);
  path += "&appid=" + WEATHER_API_KEY;
  path += "&units=imperial";
  http.begin(path.c_str());
  int httpResponseCode = http.GET();
  if (httpResponseCode == 200) {
    String payload = http.getString();
    Serial2.print((char) parse_payload_temp(&payload));
    Serial2.print(parse_payload_weather(&payload));
  } else {
    Serial2.print('F');
  }
  http.end();
}

void send_time(const String* payload) {
  int ind = 0;
  String substring = payload->substring(ind, ind + 11);
  while(!datetime_target.equals(substring)) {
    ind++;
    substring = payload->substring(ind, ind + 11);
  }
  ind+=22;
  int time;
  char c;

  String temp = payload->substring(ind, ind + 2);
  time = temp.toInt();
  c = (byte) time;
  Serial2.print(c);

  temp = payload->substring(ind + 3, ind + 5);
  time = temp.toInt();
  c = (byte) time;
  Serial2.print(c);

  temp = payload->substring(ind + 6, ind + 8);
  time = temp.toInt();
  c = (byte) ((time + 3) % 60);
  Serial2.print(c);
}

void refresh_time() {
  if(WiFi.status() != WL_CONNECTED) {
    Serial2.print('F');
    return;
  }
  refresh_ip_address(); //refresh ip address
  if (strlen(ip_address) == 0) {
    Serial2.print('F');
    return;
  }
  String lat_long;
  refresh_lat_long(&lat_long);
  if (lat_long.length() == 0) {
    Serial2.print('F');
    return;
  }
  set_lat_long(&lat_long);
  if (strlen(latitude) == 0 || strlen(longitude) == 0) {
    Serial2.print('F');
    return;
  }

  HTTPClient http;
  String path = TIME_API_SERVER + "latitude=" + String(latitude);
  path += "&longitude=" + String(longitude);
  http.begin(path.c_str());
  int httpResponseCode = http.GET();
  if (httpResponseCode == 200) {
    String payload = http.getString();
    send_time(&payload);
  } else {
    Serial2.print('F');
  }
  http.end();
}
