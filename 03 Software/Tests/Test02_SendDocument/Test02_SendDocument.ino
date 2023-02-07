#include <WiFiClientSecure.h>
#include <AsyncTelegram2.h>
#include <map>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "FS.h"
#include "SPIFFS.h"

#include "MyCredentials.h"
/* The second file in the same folder as this sketch named "MyCredentials.h" contains:
const char* ssid  =  "xxxxxxxxx";     // SSID WiFi network
const char* pass  =  "xxxxxxxxx";     // Password  WiFi network
const char* token =  "xxxxxx:xxxxxxxxxxxxx";  // Telegram token

int64_t userid = 123456789;

I included MyCredentials.h to prevent the information from being uploaded to github (MyCredentials.h is in gitignore)
*/

// Timezone definition
#define MYTZ "CET-1CEST,M3.5.0,M10.5.0/3"

#define FORMAT_SPIFFS_IF_FAILED false
#define LOG_FILE "/templog.csv"
#define SEND_LOG_CALLBACK  "sendlog"
#define STATUS_CALLBACK    "status"
#define CLEAR_LOG_CALLBACK "clearlog"
#define SENSOR_OFFSET -6.6 // 18.1-24.7


// The secure wifi client
WiFiClientSecure client;
#ifdef ESP8266
#include <ESP8266WiFi.h>
  Session   session;
  X509List  certificate(telegram_cert);
#endif

// The Telegram bot
AsyncTelegram2 myBot(client);
InlineKeyboard inlineKeyboard; 

Adafruit_BME280 bme; // I2C

// Logdata, with times and measured temperatures
std::map<time_t, float> TemperatureLog;

// Callback functions definition for inline keyboard buttons
void onSendLog(const TBMessage &queryMsg){
  // Write logdata to CSV file
  Serial.println("\nCreating csv file");
  File file = SPIFFS.open(LOG_FILE, FILE_WRITE);
  file.print("\"Time\",\"Temperature\"\n");
  
  struct tm * localTime;
  for (auto const& datapoint : TemperatureLog) {
      localTime = localtime(& (datapoint.first) );
      file.printf("%04d-%02d-%02d %02d:%02d:%02d,%.6f\n", 
        localTime->tm_year+1900, localTime->tm_mon+1, localTime->tm_mday,
        localTime->tm_hour, localTime->tm_min, localTime->tm_sec, 
        datapoint.second ); 
  }
  
  file.close();
  
  Serial.println("\nSending csv file");
  file = SPIFFS.open(LOG_FILE, "r");
  if (file) {
    myBot.sendDocument(queryMsg, file, file.size(), AsyncTelegram2::DocumentType::CSV, file.name());
    file.close();
    myBot.sendMessage(queryMsg, "Log file sent", inlineKeyboard);          
  }
  else
    Serial.println("Can't open the file. Upload \"data\" folder to filesystem");
};

void onStatus(const TBMessage &queryMsg){
  float tempC = 3.0+SENSOR_OFFSET;
  String message = "Current temperature " + String(tempC, 3) + "°C";
  myBot.editMessage(queryMsg, message.c_str(), inlineKeyboard);    
}

void onClearLog(const TBMessage &queryMsg){
  TemperatureLog.clear();
  Serial.println("Logfile cleared");
  myBot.editMessage(queryMsg, "Log file cleared", inlineKeyboard);          
}

// General setup function
void setup() {
  // initialize the Serial
  Serial.begin(115200);

  bme.begin(0x76);   

  WiFi.setAutoConnect(true);
  WiFi.mode(WIFI_STA);

  // connects to access point
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());

  if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
      Serial.println("SPIFFS Mount Failed");
      return;
  }

  listDir("/", 0);
  

  // Sync time with NTP
  configTzTime(MYTZ, "time.google.com", "time.windows.com", "pool.ntp.org");
  client.setCACert(telegram_cert);

  // Add inline keyboard
  inlineKeyboard.addButton("Send logfile",  SEND_LOG_CALLBACK,  KeyboardButtonQuery, onSendLog);
  inlineKeyboard.addButton("Clear logfile", CLEAR_LOG_CALLBACK, KeyboardButtonQuery, onClearLog);
  inlineKeyboard.addRow();
  inlineKeyboard.addButton("Update status", STATUS_CALLBACK,    KeyboardButtonQuery, onStatus);

  // Set the Telegram bot properies
  myBot.setUpdateTime(1000);
  myBot.setTelegramToken(token);

  // Check if all things are ok
  Serial.print("\nTest Telegram connection... ");
  myBot.begin() ? Serial.println("OK") : Serial.println("NOK");
  myBot.addInlineKeyboard(&inlineKeyboard);

  myBot.setFormattingStyle(AsyncTelegram2::FormatStyle::HTML /* MARKDOWN */);

  // Send a welcome message to user when ready
  char welcome_msg[128];
  snprintf(welcome_msg, sizeof(welcome_msg),
          "BOT @%s online.\n/help for command list.",
          myBot.getBotName());

  myBot.sendTo(userid, welcome_msg);
}

// General loop function
void loop() {
  printHeapStats();

  static uint32_t lastMeasurement = 0;
  static uint32_t logInterval = 1000*3;
  if ( millis() - lastMeasurement > logInterval ) {
    lastMeasurement = millis();
    time_t now;
    time(&now); // Get current time
    float tempC = 3.0+SENSOR_OFFSET;
    TemperatureLog[now]=tempC;
    Serial.printf("Temperature: %.3f°C\n", tempC);
    if( TemperatureLog.size()>10 ) logInterval = 1000*60*3; // Go to lower frequency after some samples, for debugging.
  }

  // a variable to store telegram message data
  TBMessage msg;

  // if there is an incoming message...
  if (myBot.getNewMessage(msg)) {
    Serial.printf("Message from chatID: %d", msg.chatId);
    MessageType msgType = msg.messageType;

    // Received a text message
    if (msgType == MessageText){
      String msgText = msg.text;
      Serial.print("Text message received: ");
      Serial.println(msgText);

      // Send a csv file passing the stream
      if (msgText.indexOf("/log") > -1) onSendLog(msg);
        
      else if (msgText.indexOf("/clear") > -1) onClearLog(msg);

      else {
        myBot.sendMessage(msg, "Welcome to the temperature logger\nchoose a button", inlineKeyboard);
      }
    }
  }
}

// List all files saved in the selected filesystem
void listDir(const char * dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\r\n", dirname);
  File root = SPIFFS.open(dirname, "r");
  if (!root) {
    Serial.println("- failed to open directory\n");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println(" - not a directory\n");
    return;
  }
  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.printf("  DIR : %s\n", file.name());
      if (levels)
        listDir(file.name(), levels - 1);
    }
    else
      Serial.printf("  FILE: %s\tSIZE: %d\n", file.name(), file.size());
    file = root.openNextFile();
  }
}

void printValues() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
}

void printHeapStats() {
  static uint32_t infoTime;
  struct tm sysTime;
  if (millis() - infoTime > 10000) {
    infoTime = millis();
    time_t now = time(nullptr);
    sysTime = *localtime(&now);
    //heap_caps_print_heap_info(MALLOC_CAP_DEFAULT);
    Serial.printf("%02d:%02d:%02d - Total free: %6d - Max block: %6d\n",
      sysTime.tm_hour, sysTime.tm_min, sysTime.tm_sec,
      heap_caps_get_free_size(0), heap_caps_get_largest_free_block(0) );
  }
}
