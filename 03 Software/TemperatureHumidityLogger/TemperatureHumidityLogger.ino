#include <AsyncTelegram2.h>

// Timezone definition
#include <time.h>
#define MYTZ "CET-1CEST,M3.5.0,M10.5.0/3"

#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include "FS.h"
#include "SPIFFS.h"
#include <map>

#define VERSION "1.0.1"

/* 
1.0.0 Initial release
1.0.1 Clear logfile behind OK/Cancel submenu

To do:
- After downloading CSV file, send new keyboard instead of updating previous message
- Structure with sensor data should also include CSV header and line
- Temperature calibration via Telegram
- Also calibrations for other signals?
- Report version if requested under debug button
- Include over the air update via Telegram
*/
 
/*
MyCredentials.h is in gitignore and should have the following content:

const char* token =  "aaaaaaaaaa:bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";  // Telegram token
int64_t userid = 12345678; // User who receives a message after startup

std::map<String, String > ACCESS_POINTS { 
  {"SSID-1", "Password-1" }, 
  {"SSID-2", "Password-2" }, 
  {"SSID-3", "Password-3" } };
*/
#include "MyCredentials.h"

/*
  ELECTRICAL CONNECTIONS
  BME280   ESP32    
  VCC      3V3
  GND      GND
  SCL      IO22
  SDA      IO21
*/
// Messages for he callback functions
#define CB_DOWNLOAD         "cbDownload"
#define CB_CLEAR_LOG_MENU   "cbClearLogMenu" 
#define CB_CLEAR_LOG_OK     "cbClearLogOK" 
#define CB_CLEAR_LOG_CANCEL "cbClearLogCancel" 
#define CB_STATUS           "cbStatus"
#define CB_DEBUG            "cbDebug"

// Temperature and logging
#define TEMPERATURE_OFFSET -2.1         // Added to raw signal of thermometer
#define LOG_INTERVAL 10                 // Number of minutes between log intervals
#define LOG_FILE "/logfile.csv"         // Name of the logfile

// Emoticons to spice up the Telegram messages
const char EMOTICON_DROPLETS[]    = { 0xf0, 0x9f, 0x92, 0xa6, 0x00 };
const char EMOTICON_TEMPERATURE[] = { 0xf0, 0x9f, 0x8c, 0xa1, 0x00 };
const char EMOTICON_PRESSURE[]    = { 0xf0, 0x9f, 0x8c, 0xaa, 0x00 };
const char EMOTICON_WELCOME[]     = { 0xf0, 0x9f, 0x99, 0x8b, 0xe2, 0x80, 0x8d, 0xe2, 0x99, 0x80, 0xef, 0xb8, 0x8f, 0x00 };

// Structure containing the sensor data
struct sensorData_t {
  public:
    float temperature;
    float pressure;
    float humidity;
  
    void readSensor( Adafruit_BME280 &bme) {
      try {
        temperature = bme.readTemperature() + TEMPERATURE_OFFSET;
        pressure = bme.readPressure();
        humidity = bme.readHumidity();
      } 
      catch (const std::exception& e) {
        Serial.println("Error reading BME280");
        temperature = 999;
        pressure = 999;
        humidity = 999;
      }
    };
};

// Global variables
WiFiMulti wifiMulti;
WiFiClientSecure client;  
AsyncTelegram2 myBot(client);
InlineKeyboard inlineKeyboard, clearLogMenu;
Adafruit_BME280 bme; // I2C
sensorData_t sensorData;

std::map<int, String > dayOfWeek { 
  {0, "SUN" }, 
  {1, "MON" }, 
  {2, "TUE" },
  {3, "WED" }, 
  {4, "THU" }, 
  {5, "FRI" },
  {6, "SAT" } };

void newCSVfile() {
  File file = SPIFFS.open(LOG_FILE, FILE_WRITE);
  if(!file){
      Serial.println("newCSVfile: Failed to open file for writing");
      return;
  }

  char msg[100] = "Date,Time,DateTime,Temperature [°C],Humidity [%%],Pressure [hPa],Day of week\n";
  Serial.print(msg);

  if(file.print(msg)){
      Serial.println("New CSV file created");
  } else {
      Serial.println("Create new CSV file unsuccessful");
  }
  file.close();
};

String convertToHexString( String input ) {
  String result = "{ ";
  for( int i=0; i<input.length(); i++ ) {
    result += String("0x") + String( (int) input[i], HEX ) + ", ";
  }
  result+="0x00 };";
  result.toLowerCase();
  Serial.println(input + ": " + result);
  return result;
}

// Callback functions definition for inline keyboard buttons
void onDownload(const TBMessage &queryMsg){
  Serial.println("Sending csv file from filesystem");
  File file = SPIFFS.open(LOG_FILE, "r");
  if (file) {
    myBot.sendDocument(queryMsg, file, file.size(), AsyncTelegram2::DocumentType::CSV, file.name());
    file.close();
  }
  else
    Serial.println("Can't open the file");
  
}

void onClearLogMenu(const TBMessage &queryMsg){
  Serial.println("Pull up clear logfile menu");
  //myBot.endQuery(queryMsg, "New logfile created", false);
  myBot.editMessage(queryMsg.chatId, queryMsg.messageID, "Do you really want to clear the logfile?", clearLogMenu);
}

void onClearLogOK(const TBMessage &queryMsg){
  Serial.println("Clear logfile");
  newCSVfile();
  myBot.editMessage(queryMsg.chatId, queryMsg.messageID, "The logfile was cleared.", inlineKeyboard);
}

void onClearLogCancel(const TBMessage &queryMsg){
  Serial.println("Clear logfile cancelled");
  myBot.editMessage(queryMsg.chatId, queryMsg.messageID, "Clearing of logfile was cancelled.", inlineKeyboard);
}

void onStatus(const TBMessage &queryMsg){
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);
    
  sensorData.readSensor(bme);
  char msg[100];
  snprintf(msg, sizeof(msg), "%02d:%02d %s %.1f°C %s %.1f%% %s %.1f hPa", 
    timeinfo->tm_hour, timeinfo->tm_min, 
    EMOTICON_TEMPERATURE, sensorData.temperature, 
    EMOTICON_DROPLETS, sensorData.humidity, 
    EMOTICON_PRESSURE, sensorData.pressure/100 ); 
  Serial.println(msg);
  
  myBot.editMessage(queryMsg.chatId, queryMsg.messageID, String(msg), inlineKeyboard);
  Serial.println(msg);
}

void onDebug(const TBMessage &queryMsg){
  String msg = String("Version ") + String(VERSION) +"\n" +
               "WiFi connected to" + WiFi.SSID();
  myBot.editMessage(queryMsg.chatId, queryMsg.messageID, msg, inlineKeyboard);
  Serial.println(msg);  
};

void setup() {
  // initialize the Serial
  Serial.begin(115200);

  // Start the filesystem 
  SPIFFS.begin();
  
  // Start the BME280 temperature humidity pressure sensor
  try {
    bme.begin(0x76);   
  } catch (const std::exception& e) {
    Serial.println("Error initializing BME280");
  }

  WiFi.mode(WIFI_STA);

  // Add wifi access points 
  for (const auto &ap : ACCESS_POINTS ) {
    Serial.printf( "%s %s\n", ap.first.c_str(), ap.second.c_str() );
    wifiMulti.addAP( ap.first.c_str(), ap.second.c_str() );
  }

  Serial.println("Connecting Wifi...");
  if(wifiMulti.run() == WL_CONNECTED) {
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("WiFi not connected yet");
  }

  WiFi.setAutoReconnect(true);

  // Sync time with NTP
  configTzTime(MYTZ, "time.google.com", "time.windows.com", "pool.ntp.org");
  client.setCACert(telegram_cert);

  // Set the Telegram bot properties
  myBot.setUpdateTime(1000);
  myBot.setTelegramToken(token);
  myBot.setMyCommands("/start", "start conversation");

  // Check if all things are ok
  Serial.print("Test Telegram connection... ");
  myBot.begin() ? Serial.println("OK") : Serial.println("NOK");
  Serial.print("Bot name: @");
  Serial.println(myBot.getBotName());

  // Add sample inline keyboard
  inlineKeyboard.addButton("Download logfile",  CB_DOWNLOAD,       KeyboardButtonQuery, onDownload);
  inlineKeyboard.addButton("Clear logfile",     CB_CLEAR_LOG_MENU, KeyboardButtonQuery, onClearLogMenu);
  // add a new empty button row
  inlineKeyboard.addRow();
  inlineKeyboard.addButton("Update status",     CB_STATUS,         KeyboardButtonQuery, onStatus);
  inlineKeyboard.addRow();
  inlineKeyboard.addButton("Debug",             CB_DEBUG,          KeyboardButtonQuery, onDebug);
    
  // Add OK cancel menu 
  clearLogMenu.addButton("Cancel",  CB_CLEAR_LOG_CANCEL, KeyboardButtonQuery, onClearLogCancel);
  clearLogMenu.addButton("OK",      CB_CLEAR_LOG_OK,     KeyboardButtonQuery, onClearLogOK);

  // Add pointer to this keyboard to bot (in order to run callback function)
  myBot.addInlineKeyboard(&inlineKeyboard);
  myBot.addInlineKeyboard(&clearLogMenu);

  String text = String(EMOTICON_WELCOME) + " Welcome!";
  myBot.sendTo(userid, text.c_str(), inlineKeyboard.getJSON() );
}


void loop() {
  time_t rawtime;
  struct tm * timeinfo;
  static int prev_min = -1;
  static bool wificonnectReported = false;

  // Reconnect wifi if required
  if(wifiMulti.run() != WL_CONNECTED) {
    if (!wificonnectReported) {
      Serial.println("WiFi not connected!");
      wificonnectReported=true;
    } 
  } 
  else {
    wificonnectReported=false;
  }

  // Add a new line to the csv file every 10 minutes
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  if( ( timeinfo->tm_year > 80 ) and ( timeinfo->tm_min != prev_min ) and ( timeinfo->tm_min % LOG_INTERVAL == 0 ) ) {
    prev_min = timeinfo->tm_min;
    char msg[200];
    sensorData.readSensor(bme);
    snprintf( msg, sizeof(msg), "%04d-%02d-%02d,%02d:%02d,%04d-%02d-%02d,%02d:%02d,%.3f,%.3f,%.3f,%s\n", 
       1900 + timeinfo->tm_year, timeinfo->tm_mon + 1, timeinfo->tm_mday,                                        // Just the date
       timeinfo->tm_hour, timeinfo->tm_min,                                                                      // Just the time
       1900 + timeinfo->tm_year, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min,   // Date and time
       sensorData.temperature,                                                                                   // Temperature
       sensorData.humidity,                                                                                      // Humidity
       sensorData.pressure/100,                                                                                  // Pressure
       dayOfWeek[ timeinfo->tm_wday ] );                                                                         // Day of week

    Serial.println("Append to CSV file");
    Serial.println(msg);

    File file = SPIFFS.open(LOG_FILE, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open CSV for appending");
        newCSVfile();
        File file = SPIFFS.open(LOG_FILE, FILE_APPEND);
    }
    if(file.print(msg)){
        Serial.println("Message appended to CSV file");
    } else {
        Serial.println("Append to CSV file failed");
    }
    file.close();    
  }
  
  // a variable to store telegram message data
  TBMessage msg;

  // if there is an incoming message...
  if (myBot.getNewMessage(msg)) {
    // check what kind of message I received
    String tgReply;
    MessageType msgType = msg.messageType;
    
    switch (msgType) {
      case MessageText :
        // received a text message
        tgReply = msg.text;
        Serial.print("Text message received: ");
        Serial.println(tgReply);

        if (tgReply.equalsIgnoreCase("/start")) {          
          myBot.sendMessage(msg, "Welcome!", inlineKeyboard);          
        }        
        else {
          // write back feedback message and show a hint
          String text = String("const char EMOTICON[] = ") + convertToHexString( msg.text );
          myBot.sendMessage(msg, text.c_str(), inlineKeyboard);


          
        }
        break;
        
        /* 
        * Telegram "inline keyboard" provide a callback_data field that can be used to fire a callback fucntion
        * associated at every inline keyboard buttons press event and everything can be handled in it's own callback function. 
        * Anyway, is still possible poll the messagetype in the same way as "reply keyboard" or both.              
        */
        case MessageQuery:
          break;
        
        default:
          break;
    }
  }
}
