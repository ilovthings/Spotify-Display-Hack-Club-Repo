//Libleries
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <WiFi.h>
#include <SpotifyEsp32.h>
#include <SPI.h>
#include <HijelHID_BLEKeyboard.h>

//Inputs
#define B_pNp 10
#define B_n 19
#define B_prev 18

//Define pins
#define TFT_CS 7
#define TFT_RST 5
#define TFT_DC 2
#define TFT_SCLK 4
#define TFT_MOSI 6

//strings/variables
String LA = "";
String LT = "";
String LS = "";

int LP = -1;
unsigned long LSU = 0;


//internet
char* SSID = "Your wifi name";
char* PASSWORD = "password";

//spotify
const char* CLIENT_ID = "your ID";
const char* CLIENT_SECRET = "your secret";

Spotify sp(CLIENT_ID, CLIENT_SECRET);

//screen
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

//keyboard
HijelHID_BLEKeyboard keyboard("S.D.", "ESP32", 100);

//POT
#define POT 0
int LPOTV = 0;

void setup() {
Serial.begin(115200);

analogReadResolution(12);

//for the buttons
pinMode(B_pNp, INPUT_PULLUP);
pinMode(B_n, INPUT_PULLUP);
pinMode(B_prev, INPUT_PULLUP);
pinMode(POT, INPUT);

//For the TFT screen
tft.initR(INITR_BLACKTAB); // the type of screen
tft.setRotation(1); // this makes the screen landscape! remove this line for portrait
Serial.println("TFT Initialized!");
tft.fillScreen(ST77XX_BLACK); // make sure there is nothing in the buffer
tft.setTextSize(2);
tft.print("HELLO WORLD!!!");  // prints out the string

//For the wifi
WiFi.begin(SSID, PASSWORD); // Attempt to connect to wifi
Serial.print("Connecting to WiFi..."); // This will print into the console!
while(WiFi.status() != WL_CONNECTED) // Checking if the wifi has connected
{
    delay(500);
    Serial.print("."); // show a loading dot every second
}
Serial.printf("Connected! >:)"); // Wifi connected!

//I dont know if this really that important. jajaja
tft.setCursor(0,20); // make the cursor at the top left
tft.write(WiFi.localIP().toString().c_str()); // print out IP on the screen

//Spotify
sp.begin();
while(!sp.is_auth())
{
    delay(2000);
    sp.handle_client();
}
Serial.println("Connected to Spotify! >:)");

//bluetooth keyboard
keyboard.begin();
Serial.println("Bluetooth ready! >:)");

LPOTV = analogRead(POT);
}

void loop() {
  // put your main code here, to run repeatedly:
sp.handle_client(); 
//bluetooth again
if (keyboard.isConnected()) {
  //volume
  int potVal = analogRead(POT);
  if (abs(potVal - LPOTV) > 120) {
    if (potVal > LPOTV) {
      keyboard.write(KEY_MEDIA_VOLUME_UP);
    }
    else { 
      keyboard.write(KEY_MEDIA_VOLUME_DOWN);
    }
    LPOTV = potVal;
    delay(120);
  }
}

//buttons for tracks
if (!digitalRead(B_pNp)) {
  sp.start_resume_playback(); // Calling this method will pause/play the track
  delay(500);
}

if (!digitalRead(B_prev)) {
  sp.previous();              // goes to previous track
  delay(500);
}

if (!digitalRead(B_n)) {
  sp.skip();                  // skips current track
  delay(500);
}

//screen print
if (millis() - LSU > 2000) {
  String S = sp.current_playback_state();
  String CA = sp.current_artist_name();
  String CT = sp.current_track_name();
  
  //print Artist
  if (LA != CA && CA != "Something went wrong" && !CA.isEmpty()) {
    tft.fillScreen(ST77XX_BLACK);
    LT = "";
    LS = "";
    LP = -1;
    
    LA = CA;

    Serial.println("Artist: " + LA);

    tft.setTextSize(1);
    tft.setTextColor(ST77XX_GREEN);
    tft.setCursor(10,10);
    tft.print(LA);
  }

  //print Track
  if (LT != CT && CT != "Something went wrong" && CT != "null") {
    
    LT = CT;

    Serial.println("Track: " + LT);
    
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_WHITE);  
    tft.setCursor(10,40);
    tft.print(LT);  
  }

  //print 4 pause or play
  if (S != LS && S != "Something went wrong") {
    LS = S;
    
    tft.fillRect(110, 5, 20, 20, ST77XX_BLACK);

    tft.setTextSize(2);
    tft.setTextColor(ST77XX_GREEN);
    tft.setCursor(110,10);

    if (S == "playing") {
      tft.print(">");
      Serial.print("Playing!");
    }
    else {
      tft.print("||");
      Serial.print("Paused!");
    }
  }

  LSU = millis();

}

//print 4 track bar
int PMs = sp.current_progress_ms();
int DMs = sp.current_duration_ms();

if (DMs > 0) {
  int PW = map(PMs, 0, DMs, 0, 128);

  if (abs(PW - LP) > 2) {
    LP = PW;

    //backgroud bar
    tft.fillRect(0, 118, 128, 10, ST77XX_WHITE);
    //actually bar
    tft.fillRect(0, 118, PW, 10, ST77XX_GREEN);
  }
}

delay(10);
}

