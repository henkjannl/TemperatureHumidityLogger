# ESP cheat sheet

# ESP32 I/O table
https://randomnerdtutorials.com/esp32-pinout-reference-gpios

The pins highlighted in <span style="background-color:lime">green</span> are OK to use. The ones highlighted in <span style="background-color:yellow">yellow</span> are OK to use, but you need to pay attention because they may have unexpected behavior mainly at boot. The pins highlighted in <span style="background-color:#ff6666">red</span> are not recommended to use as inputs or outputs.

Note: all pins in the table below are broken out at the MH-ET LIVE Minikit board

|GPIO | Input                                                    | Output                                                | Function  | Notes
|:---:|:--------------------------------------------------------:|:-----------------------------------------------------:|-----------|---------
| 0   | <span style="background-color:yellow"> pulled up</span>  | <span style="background-color:yellow">OK</span>       |           | outputs PWM signal at boot
| 1   | <span style="background-color:#ff6666"> TX pin </span>   | <span style="background-color:yellow">OK</span>       | UART0 TXD | debug output at boot
| 2   | <span style="background-color:lime"> OK</span>           | <span style="background-color:lime">OK</span>         |           | connected to on-board LED
| 3   |<span style="background-color:yellow"> OK</span>          | <span style="background-color:#ff6666"> RX pin</span> | UART0 RXD | HIGH at boot
| 4   | <span style="background-color:lime"> OK</span>           | <span style="background-color:lime"> OK</span>        |           | 
| 5   | <span style="background-color:lime"> OK</span>           | <span style="background-color:lime"> OK</span>        | VSPI CS0  | outputs PWM signal at boot
| 6   | <span style="background-color:#ff6666"> x</span>         | <span style="background-color:#ff6666"> x</span>      |           | connected to the integrated SPI flash
| 7   | <span style="background-color:#ff6666"> x</span>         | <span style="background-color:#ff6666"> x</span>      |           | connected to the integrated SPI flash
| 8   | <span style="background-color:#ff6666"> x</span>         | <span style="background-color:#ff6666"> x</span>      |           | connected to the integrated SPI flash
| 9   | <span style="background-color:#ff6666"> x</span>         | <span style="background-color:#ff6666"> x</span>      | UART1 TXD | connected to the integrated SPI flash
| 10  | <span style="background-color:#ff6666"> x</span>         | <span style="background-color:#ff6666"> x</span>      | UART1 RXD | connected to the integrated SPI flash
| 11  | <span style="background-color:#ff6666"> x</span>         | <span style="background-color:#ff6666"> x</span>      |           | connected to the integrated SPI flash
| 12  | <span style="background-color:yellow">OK</span>          | <span style="background-color:lime">OK</span>         | HSPI MISO | boot fail if pulled high
| 13  | <span style="background-color:lime">OK</span>            | <span style="background-color:lime">OK</span>         | HSPI MOSI |
| 14  | <span style="background-color:lime">OK</span>            | <span style="background-color:lime">OK</span>         | HSPI CLOCK | outputs PWM signal at boot
| 15  | <span style="background-color:lime">OK</span>            | <span style="background-color:lime">OK</span>         | HSPI CS0  | outputs PWM signal at boot
| 16  | <span style="background-color:lime">OK</span>            | <span style="background-color:lime">OK</span>         |           |
| 17  | <span style="background-color:lime">OK</span>            | <span style="background-color:lime">OK</span>         |           |
| 18  | <span style="background-color:lime">OK</span>            | <span style="background-color:lime">OK</span>         | VSPI CLOCK  |
| 19  | <span style="background-color:lime">OK</span>            | <span style="background-color:lime">OK</span>         | VSPI MISO |
| 21  | <span style="background-color:lime">OK</span>            | <span style="background-color:lime">OK</span>         | I²C<sub>0</sub> SDA  |
| 22  | <span style="background-color:lime">OK</span>            | <span style="background-color:lime">OK</span>         | I²C<sub>0</sub> SCL  |
| 23  | <span style="background-color:lime">OK</span>            | <span style="background-color:lime">OK</span>         | VSPI MOSI |
| 25  | <span style="background-color:lime">OK</span>            | <span style="background-color:lime">OK</span>         |           |
| 26  | <span style="background-color:lime">OK</span>            | <span style="background-color:lime">OK</span>         |           |
| 27  | <span style="background-color:lime">OK</span>            | <span style="background-color:lime">OK</span>         |           |
| 32  | <span style="background-color:lime">OK</span>            | <span style="background-color:lime">OK</span>         | ADC1/0    |
| 33  | <span style="background-color:lime">OK</span>            | <span style="background-color:lime">OK</span>         | ADC1/1    |
| 34  | <span style="background-color:lime">OK</span>            |                                                       | ADC1/2    |  <span style="background-color:yellow">input only</span>
| 35  | <span style="background-color:lime">OK</span>            |                                                       | ADC1/3    | <span style="background-color:yellow">input only</span>
| 36  | <span style="background-color:lime">OK</span>            |                                                       | ADC1/4    | <span style="background-color:yellow">input only</span>
| 39  | <span style="background-color:lime">OK</span>            |                                                       | ADC1/7    | <span style="background-color:yellow">input only</span>
 
# ESP8266 I/O table
https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/

The pins highlighted in <span style="background-color:lime">green</span> are OK to use. The ones highlighted in <span style="background-color:yellow">yellow</span> are OK to use, but you need to pay attention because they may have unexpected behavior mainly at boot. The pins highlighted in <span style="background-color:#ff6666">red</span> are not recommended to use as inputs or outputs.

| PIN | GPIO | Input                                                       | Output                                               | Notes
|:---:|:----:|:-----------------------------------------------------------:|:----------------------------------------------------:|-----------
| D0  | 16   | No interrupt                                                | No PWM or I<sup>2</sup>C support                     | <span style="background-color:#ff9900"> High at boot</span> <br> Used to wake up from deep sleep
| D1  |  5   | <span style="background-color:lime"> OK</span>              | <span style="background-color:lime"> OK </span>      | Often used as <span style="background-color:#336699">SCL</span> (I<sup>2</sup>C)
| D2  |  4   | <span style="background-color:lime"> OK</span>              | <span style="background-color:lime"> OK </span>      | Often used as <span style="background-color:#336699">SDA</span> (I<sup>2</sup>C)
| D3  |  0   | pulled up                                                   | <span style="background-color:lime"> OK </span>      | Connected to FLASH button<br>Boot fails if pulled LOW
| D4  |  2   | pulled up                                                   | <span style="background-color:lime"> OK </span>      | <span style="background-color:ff9900ff">HIGH at boot</span><br>Connected to on-board LED<br>Boot fails if pulled LOW
| D5  | 14   | <span style="background-color:lime"> OK</span>              | <span style="background-color:lime"> OK</span>       | <span style="background-color:#0066cc">SPI</span> SCLK
| D6  | 12   | <span style="background-color:lime"> OK</span>              | <span style="background-color:lime"> OK</span>       | <span style="background-color:#0066cc">SPI</span> MISO
| D7  | 13   | <span style="background-color:lime"> OK</span>              | <span style="background-color:lime"> OK</span>       | <span style="background-color:#0066cc">SPI</span> MOSI
| D8  | 15   | Pulled to GND                                               | <span style="background-color:yellow">OK</span>      | <span style="background-color:#0066cc">SPI</span> CS <br> Boot fails if pulled HIGH
| RX  |  3   | <span style="background-color:yellow">OK</span>             | <span style="background-color:#cc3333">RX pin</span> | <span style="background-color:ff9900">HIGH at boot</span>
| TX  |  1   | <span style="background-color:#cc3333">RX pin</span>        | <span style="background-color:yellow">OK</span>      | <span style="background-color:ff9900">HIGH at boot</span><br>Debug output at boot<br>Boot fails if pulled LOW
| A0  | ADC0 | <span style="background-color:lime"> Analog<br>input</span> | <span style="background-color:#cc3333"> x</span>     |



## Pointers

```c++
char v[6];          // array of 6 characters
char* p = &v[3];    // pointer to one of the characters
char  x = *p;       // *p is the object that p points to
char& c;            // c is a reference to a char in a function call
char* p = nullptr;  // points to nothing, can be compared: there is only one nullptr
const char* commands[] = {"On", "Off", "Timer" }; // array of array of characters
```

## Pointer to a function
```c++
void someFunction(int x) { printf( "%d\n", x ); };
 
int main() {
    void (*pointerToFunction)(int);
    pointerToFunction = &someFunction;
    pointerToFunction(3);
}
```

## Reference
```c++
// Unary suffix & means reference to, we don't need a prefix * to access the value
// this way we ensure the vector v is not copied
void sort(vector<double>& v) { 

// If we are sure we don't want to modify a value, we can use const
void sum(const vector<double>& v) { 
```

## For loop over a container

```c++
const char *colour[] = { "Blue", "Red", "Orange", "Yellow" };
for (auto& c : colour) std::cout << c << "\n";
```

## Struct with list

```c++
enum script_events {displayImage, playSound, closeCurtains, openCurtains, endOfShow};

typedef struct {
  float time;                  // Time the event starts
  enum script_events event;    // Type of event
  char filename[14];           // Filename for image or sound
} type_script;


//Compose the media show, to be extended with enum for sound or filename
static const type_script script[] = {
  {  0.0, displayImage, "/BLK.jpg"},
  {  0.5, openCurtains, ""        },
			:
  { 209.3, endOfShow,     ""       }
};

static const char* const MAIN[] = { "TIMER", "COLOR", "BRIGHTNESS" };

void loop()
{
  timeSec = (float) 0.001 * (millis()-timeOffset);
  // We have not yet come at the end of the show and the time of the next event has arrived
  if ( (script[eventIndex].event != endOfShow) && (timeSec >= script[eventIndex].time) ) {
```

## Creating a list using the standard library
```c++
#include <list>

typedef struct  {
    double x,y;
} tPoint;

int main()
{
	std::list<tPoint> points; 
  points.push_front({0,0});
  points.push_back({1,1});
  firstElement=points.front();
  numElements=points.size();
  
  for (auto const& i : points) {
      std::cout << i.x;
  }  
 ```

## String examples

### Function returning a char* 
```
char* mycharheap(int year)
{
    char* result = new char;
    sprintf(result, "Year: %u",year);
    return result;
}
```

A general form of format specifier is

```
%[flags][width][.precision][length]specifier
```
Given below is a description of each of the parts of format specifier:

| specifier | meaning 
|-----------|---------
| % sign    | This is a leading % sign
| flags     | They can have the following values:
|           | –      Left justifies the result within the field. By default, right justified
|           | +      The sign of the result attached to the beginning of the value including positive results
|           | Space  In the absence of a sign, space is attached to the beginning of the result
|           | #      Specify an alternative form of conversion
|           | 0      Used for integer and floating-point numbers. Act as leading zeros in the absence of space.
| Width     | Specifies minimum field width in the form of a * or an integer value. This is optional.
| Precision | Specifies precision with a ‘.’ followed by a * or an integer or nothing. This is also optional.
| Length    | The optional argument that specified the size of the argument.
| Specifier | This is a conversion format specifier.

Various Format Specifiers used in C++ are as follows:

| Specifier | Description                                                       |
|:---------:|-------------------------------------------------------------------|
| %   | Prints a %                                                              |
| c   | Prints single character                                                 |
| s   | Prints a string                                                         |    
| d/i | Converts signed integer to decimal representation                       |
| o   | Converts unsigned integer to octal representation                       |
| x/X | Converts unsigned integer to hexadecimal representation                 |
| u   | Converts unsigned integer to decimal representation                     |
| f/F | Converts floating-point number to decimal representation                |
| e/E | Converts floating-point number to decimal exponent notation             |
|	a/A | Converts floating-point number to a hexadecimal exponent                |
|	g/G | Converts floating-point number to decimal or decimal exponent notation  |
|	n   | Number of characters written so far by this function call               |
|	p   | A pointer pointing to Implementation defined character sequence         |


### Print to a string

```c++
char data[100];
char* myBlog = "https://arduinobasics.blogspot.com";
int year = 2019;
sprintf(data, "Year: %u, Blog Link: %s",year,myBlog);
```

### Pass string value to function

Alternative 1:
```c++
void drawString(const char *string) {
  ...
}

int main() {
  char text[25];
  sprintf(text, "%02d:%02d:%02d", h,m,s);
  drawString(text);
}
```

Alternative 2:
```c++
void drawString(const String& string)
```

## Class definition

```c++
class Line {
   public:
      Line();  
      void setLength( double len );
      double getLength( void );
  private:
      double length;
};
 
Line::Line(void) {
   cout << "Object is being created" << endl;
}

void Line::setLength( double len ) {
   length = len;
}

double Line::getLength( void ) {
   return length;
}
```

## Main sections of the program

```c++
//====================================================================
//                             Libraries
//====================================================================
#include <FS.h>
#include <math.h>
#include "SPIFFS.h"

//====================================================================
//                             Defines
//====================================================================
#define PI 3.1415926535
```


## Switch case
```c++
switch (script[eventIndex].event) {

  case openCurtains:
	printf("%.3f Open curtains\n", timeSec);
	StepperMove(curtains, timeSec, 3, -CURTAIN_STROKE); 
	break;
}
```

## Short if then else

```c++
x = (val == 10) ? 20 : 15;
```

# Location of Arduino libraries
Way to locate the libraries directory of Arduino is right-clicking the application and choosing ```Open file location``` or ```File``` > ```Preferences``` > ```preferences.txt```
Possible locations:

### Asus:

| Library  | Location
|----------|----------------------
| packages | C:\Users\henkj\OneDrive\Documents\Arduino\libraries
| arduino  | C:\Users\henkj\AppData\Local\Arduino15
| esp32    | C:\Users\henkj\AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.4\libraries
  
### HP:

| Library             | Location
|---------------------|----------------------
| Installed packages  | C:\Users\hjvanderpol\OneDrive\Documents\Arduino\libraries
| ESP native packages | C:\Users\hjvanderpol\AppData\Local\Arduino15\packages
| ESP NOW 8266        | C:\Users\hjvanderpol\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4\tools\sdk\include
| arduino packages    | C:\Program Files (x86)\Arduino\libraries


# Bodmer graphics library TFT_eSPI
Modify compilation settings for a specific setup:
 - In ```User_Setup_Select.h``` select if settings need to be retrieved from ```User_Setup.h``` or from one of the predefined configurations such as ```Setup12_M5Stack.h```
 - Potentially mention the screen size when initializing the TFT_eSPI object ```TFT_eSPI tft = TFT_eSPI(320,240);```

For PlatformIO, the library can be found relative to the project directory:

```Project directory\.pio\libdeps\mhetesp32minikit\TFT_eSPI```

Conversion of colors from RGB to 565 can be done by cloning

```C:\Users\henkj\OneDrive\03 HenkJan\14 InternetOfThings\04 ESP32\WashingMachineAlarm\05 User interface\Color converter RGB565.ods```

## Bodmer font sizes:

for(int font=0; font<10; font++)
  Serial.printf("Font %d Width 'XXX' %d Height %d\n" , font, tft.textWidth("XXX", font), tft.fontHeight(font));

| Font  | Width 'XXX' | Height |
|:-----:|:-----------:|:------:|
|    0  |   18 |   0 
|    1  |   18 |   8 
|    2  |   24 |  16 
|    3  |  114 |   0 
|    4  |   45 |  26 
|    5  |  114 |   0 
|    6  |   36 |  48 
|    7  |   36 |  48 
|    8  |   87 |  75 
|    9  |   18 | 107 
|   10  |   18 | 107 
|   11  |   18 | 107 
|   12  |   18 | 107 
|   13  |   18 | 107 
|   14  |   18 | 107 
|   15  |   18 | 239 
|   16  |   18 | 187 
|   17  |   18 |  85 
|   18  |   18 | 107 
|   19  |   18 | 107 

## Create own fonts in Bodmer TFT_eSPI

1. Download processing.ide from https://processing.org/[https://processing.org/]
1. Copy the desired .ttf file to ..\Arduino\libraries\TFT_eSPI\Tools\Create_Smooth_Font\Create_font\data
2. Open ...\Arduino\libraries\TFT_eSPI\Tools\Create_Smooth_Font\Create_font\Create_font.pde with the processing IDE
3. Replace the font filename in line 130: String fontName = "big_noodle_titling";  // Manually crop the filename length later after creation if needed
4. Change the font size if needed in line 137: int  fontSize = 40;
5. Run the program in the Processing IDE
6. Locate the resulting .vlw file in ...\Arduino\libraries\TFT_eSPI\Tools\Create_Smooth_Font\Create_font\FontFiles
7. Convert the .vlw file into a byte string using https://tomeko.net/online_tools/file_to_hex.php?lang=en[https://tomeko.net/online_tools/file_to_hex.php?lang=en]
8. Create a header file in the sketch directory with as first line const uint8_t  YourFontName[] PROGMEM = {
9. Add the bytestring to the header file
10. Add }; after the bytestring
11. In the main sketch, use the font with   tft.loadFont(YourFontName);
Good luck!

# M5 Stack

## M5 Stack library is located in 
C:\Users\hjvanderpol\Documents\Arduino\libraries

## Logging to serial
```c++
Serial.printf("%d > %s\r\n", i, option);
```

# Calling a function with pointers to variables
Function definition:
```c++
void getAcceleration(int16_t* x, int16_t* y, int16_t* z);
```

Variables and function call:
```c++
  int16_t x,y,z;         // raw gyro values

  getAcceleration(&x, &y, &z);
  print(x);
```

# Platform IO

[https://docs.platformio.org/en/latest/platforms/espressif32.html]

## Set monitor baudrate 

In ```platform.ini```:
```
monitor_speed = 115200
```

## Emoticons in Telegram

```c++
const char EMOTICON_BATH[]                = {0xf0, 0x9f, 0x9b, 0x81, 0x0};
const char EMOTICON_BED[]                 = {0xf0, 0x9f, 0x9b, 0x8f, 0x0};
const char EMOTICON_BULLSEYE[]            = {0xf0, 0x9f, 0x8e, 0xaf, 0x0};
const char EMOTICON_CALENDAR[]            = {0xf0, 0x9f, 0x93, 0x85, 0x0};
const char EMOTICON_CAMERA[]              = {0xf0, 0x9f, 0x93, 0xb7, 0x0};
const char EMOTICON_CHECKERED_FLAG[]      = {0xf0, 0x9f, 0x8f, 0x81, 0x0};
const char EMOTICON_CHECKMARK[]           = {0xe2, 0x9c, 0x85, 0x0};
const char EMOTICON_CLOCK[]               = {0xe2, 0x8f, 0xb0, 0x0};
const char EMOTICON_ALARM_CLOCK[]         = {0xe2, 0x8f, 0xb0, 0x0};
const char EMOTICON_CROSSMARK[]           = {0xe2, 0x9d, 0x8c, 0x0};
const char EMOTICON_DOWN_ARROW[]          = {0xe2, 0xac, 0x87, 0xef, 0xb8, 0x8f, 0x0};
const char EMOTICON_FLAME[]               = {0xf0, 0x9f, 0x94, 0xa5, 0x0};
const char EMOTICON_FOOTSTEPS[]           = {0xf0, 0x9f, 0x91, 0xa3, 0x0};
const char EMOTICON_GEAR[]                = {0xe2, 0x9a, 0x99, 0xef, 0xb8, 0x8f, 0x0};
const char EMOTICON_GLASSES[]             = {0xf0, 0x9f, 0x91, 0x93, 0x0};
const char EMOTICON_HAMMER_WRENCH[]       = {0xf0, 0x9f, 0x9b, 0xa0, 0x0};
const char EMOTICON_HOURGLASS[]           = {0xe2, 0x8c, 0x9b, 0xef, 0xb8, 0x8f, 0x0};
const char EMOTICON_HOUSE[]               = {0xf0, 0x9f, 0x8f, 0xa0, 0x0};
const char EMOTICON_ISLAND[]              = {0xf0, 0x9f, 0x8f, 0x96, 0x0};
const char EMOTICON_LAMP[]                = {0xf0, 0x9f, 0x92, 0xa1, 0x0};
const char EMOTICON_MAGIC_STICK[]         = {0xf0, 0x9f, 0xaa, 0x84, 0x0};
const char EMOTICON_OFFICE[]              = {0xf0, 0x9f, 0x8f, 0xa2, 0x0};
const char EMOTICON_PIN[]                 = {0xf0, 0x9f, 0x93, 0x8d, 0x0};
const char EMOTICON_POINTING_FINGER[]     = {0xf0, 0x9f, 0x91, 0x89, 0x0};
const char EMOTICON_RED_QUESTION_MARK[]   = {0xe2, 0x9d, 0x93, 0x0};
const char EMOTICON_RUNNER[]              = {0xf0, 0x9f, 0x8f, 0x83, 0x0};
const char EMOTICON_SHOWER[]              = {0xf0, 0x9f, 0x9a, 0xbf, 0x0};
const char EMOTICON_SMILEY[]              = {0xf0, 0x9f, 0x98, 0x80, 0x0};
const char EMOTICON_STHETOSCOPE[]         = {0xf0, 0x9f, 0xa9, 0xba, 0x0};
const char EMOTICON_STOPWATCH[]           = {0xe2, 0x8f, 0xb1, 0x0};
const char EMOTICON_THERMOMETER[]         = {0xf0, 0x9f, 0x8c, 0xa1, 0x0};
const char EMOTICON_TRIANGLE_DOWN[]       = {0xf0, 0x9f, 0x94, 0xbd, 0x0};
const char EMOTICON_TRIANGLE_UP[]         = {0xf0, 0x9f, 0x94, 0xbc, 0x0};
const char EMOTICON_UP_ARROW[]            = {0xe2, 0xac, 0x86, 0xef, 0xb8, 0x8f, 0x0};
const char EMOTICON_WARNING[]             = {0xe2, 0x9a, 0xa0, 0xef, 0xb8, 0x8f, 0x0};
```

