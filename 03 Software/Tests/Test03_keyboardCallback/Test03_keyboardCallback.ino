#include <AsyncTelegram2.h>

// Timezone definition
#include <time.h>
#define MYTZ "CET-1CEST,M3.5.0,M10.5.0/3"

#include <WiFi.h>
#include <WiFiClientSecure.h>

/*
const char* ssid  =  "xxxxxxxxx";     // SSID WiFi network
const char* pass  =  "xxxxxxxxx";     // Password  WiFi network
const char* token =  "xxxxxxxxxxx:xxxxxxxxxxxxxxxxxxxxxxxxxxxxx";  // Telegram token
*/
#include "MyCredentials.h"

#define CB_DOWNLOAD  "cbDownload"
#define CB_CLEAR_LOG "cbClearLog" 
#define CB_STATUS    "cbStatus"

const uint8_t LED = 4;

// Global variables
WiFiClientSecure client;  
AsyncTelegram2 myBot(client);
InlineKeyboard inlineKeyboard;

// Callback functions definition for inline keyboard buttons
void onDownload(const TBMessage &queryMsg){
  digitalWrite(LED, HIGH);
  //Serial.println("Download function to be implemented here");
  Serial.printf("Download function to be implemented here\nQueryId: %d ChatID: %d\n", queryMsg.callbackQueryID, queryMsg.chatId);
  //myBot.endQuery(queryMsg, "Light on", true);
}

void onClearLog(const TBMessage &queryMsg){
  digitalWrite(LED, LOW);
  //Serial.println("Clear logfile to be implemented here");
  Serial.printf("Clear logfile to be implemented here\nQueryId: %d ChatID: %d\n", queryMsg.callbackQueryID, queryMsg.chatId);
  //myBot.endQuery(queryMsg, "Light on", false);
}

void onStatus(const TBMessage &queryMsg){
  //Serial.println("Status update to be implemented here");
  Serial.printf("Status update to be implemented here\nQueryId: %d ChatID: %d\n", queryMsg.callbackQueryID, queryMsg.chatId);
  //myBot.endQuery(queryMsg, "Status", true);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED, OUTPUT);  
  // initialize the Serial
  Serial.begin(115200);

  // connects to access point
  WiFi.setAutoConnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  delay(500);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }

  // Sync time with NTP
  configTzTime(MYTZ, "time.google.com", "time.windows.com", "pool.ntp.org");
  client.setCACert(telegram_cert);

  // Set the Telegram bot properties
  myBot.setUpdateTime(1000);
  myBot.setTelegramToken(token);

  // Check if all things are ok
  Serial.print("Test Telegram connection... ");
  myBot.begin() ? Serial.println("OK") : Serial.println("NOK");
  Serial.print("Bot name: @");
  Serial.println(myBot.getBotName());

  // Add sample inline keyboard
  inlineKeyboard.addButton("Download logfile",  CB_DOWNLOAD,  KeyboardButtonQuery, onDownload);
  inlineKeyboard.addButton("Clear logfile",     CB_CLEAR_LOG, KeyboardButtonQuery, onClearLog);
  // add a new empty button row
  inlineKeyboard.addRow();
  inlineKeyboard.addButton("Update status",     CB_STATUS,    KeyboardButtonQuery, onStatus);
    
  // Add pointer to this keyboard to bot (in order to run callback function)
  myBot.addInlineKeyboard(&inlineKeyboard);
}

void loop() {

  // In the meantime LED_BUILTIN will blink with a fixed frequency
  // to evaluate async and non-blocking working of library
  static uint32_t ledTime = millis();
  if (millis() - ledTime > 200) {
    ledTime = millis();
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }

  //printHeapStats();
  
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

        if (tgReply.equalsIgnoreCase("/inline_keyboard1")) {          
          myBot.sendMessage(msg, "This is inline keyboard 1:", inlineKeyboard);          
        }        
        else {
          // write back feedback message and show a hint
          String text = "You write: \"";
          text += msg.text;
          text += "\"\nTry /inline_keyboard1 or /inline_keyboard2";
          myBot.sendMessage(msg, text);
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


void printHeapStats() {
  time_t now = time(nullptr);
  struct tm tInfo = *localtime(&now);
  static uint32_t infoTime;
  if (millis() - infoTime > 10000) {
    infoTime = millis();

  //heap_caps_print_heap_info(MALLOC_CAP_DEFAULT);
  Serial.printf("\n%02d:%02d:%02d - Total free: %6d - Max block: %6d",
    tInfo.tm_hour, tInfo.tm_min, tInfo.tm_sec, heap_caps_get_free_size(0), heap_caps_get_largest_free_block(0) );
  }
}
