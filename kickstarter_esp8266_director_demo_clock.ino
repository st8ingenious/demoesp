#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h>
#include <SPI.h>

//COLOR DEFINITIONS
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFE0
#define WHITE 0xFFFF
#define GREY 0xFFDF //0xEF7D 
int buttonState = 0;
const int  buttonPin = 0;

char* zzero[]={
  "00", "01", "02", "03", "04", "05", "06", "07", "08", "09"};

#define cs   15
#define dc   2
#define rst  5 

long previousMillis = 0;
int interval = 1000;

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);

int nhour=0;
int nmin=0;
int nsec=0;
unsigned long epoch =0;
boolean first=false;
boolean newv=false;
boolean notif=false;
 byte c=0;

const unsigned char cloud [] PROGMEM = {
0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0xf, 0xe0, 0x0, 0x0, 0x7e, 0x1f, 0xf8, 0x0, 
0x1, 0xff, 0x3f, 0xfc, 0x0, 0x3, 0xff, 0xff, 0xfc, 0x0, 0x7, 0xff, 0xff, 0xfe, 0x0, 
0x7, 0xff, 0xff, 0xfe, 0x60, 0x7, 0xff, 0xff, 0xff, 0xf0, 0x7, 0xff, 0xff, 0xff, 0xf8, 
0x7, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xfe, 
0x7f, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0x7f, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xfe, 
0x1f, 0xff, 0xff, 0xff, 0xfc, 0x7, 0xff, 0xff, 0xff, 0xf8, 0x0, 0xff, 0xff, 0xfc, 0x0, 
0x0, 0x7f, 0x8f, 0xe0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 

};


const unsigned char thermo [] PROGMEM = {
0x0, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 
0x24, 0x66, 0xe7, 0xc3, 0xc3, 0xe7, 0xff, 0x3c, 0x3c, 
 
};

void setup() {
   pinMode(buttonPin, INPUT_PULLUP);
  
uint16_t time = millis();
 time = millis() - time;
 
//Serial.begin(115200);

  tft.initR(INITR_BLACKTAB); 
  tft.setRotation(1);

  tft.fillScreen(CYAN);
 epoch=1473657060;     //set the time
 
}


void loop(){
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
epoch++;
    drawTime();
  }  
}


void drawTime(){
nhour=(epoch  % 86400L) / 3600+3;
nmin=(epoch  % 3600) / 60;
nsec=(epoch % 60);

  tft.setTextColor(WHITE,CYAN);
  tft.setTextSize(3); 

  tft.setCursor(13, 24);
  if (nhour >= 0 && nhour < 10) {
    tft.print(zzero[nhour]);
  }
  else{
    tft.print(nhour);
  }
  tft.setCursor(48, 24);
  tft.print(":");

  tft.setCursor(65, 24);  
  if (nmin >= 0 && nmin < 10){
    tft.print(zzero[nmin]);
  }
  else{
    tft.print(nmin);
  }

  tft.setCursor(99, 24);
  tft.print(":");

  tft.setCursor(115, 24);  
  if (nsec >= 0 && nsec <10){
    tft.print(zzero[nsec]);
  }
  else{
    tft.print(nsec);
  }
  if (!notif){
 buttonState = digitalRead(buttonPin);
if (buttonState == LOW){
  notif=true;
}
 delay(2000);   
  }else{
if (!newv){
  if (!first){
    first=true;
  tft.setTextSize(1); 
 tft.fillRect(0, 80, 160, 50, WHITE);
  tft.setTextColor(BLACK);
  tft.setCursor(0, 90);
tft.println(" New update");
tft.println(" with weather ");
tft.print(" forecast");
tft.setTextSize(2); 
tft.fillRect(95, 85, 50, 40, GREEN);
tft.setTextColor(WHITE);
 tft.setCursor(107, 99);
 tft.print("OK");

  }else{
          buttonState = digitalRead(buttonPin);
if (buttonState == LOW){
  c=1;
}
    if (c==1){
      tft.fillScreen(BLACK);
      delay(2000);
 tft.setTextSize(3); 
tft.setCursor(14, 44);
tft.setTextColor(WHITE);
tft.print("AlarmIO");
tft.setTextSize(2); 
tft.setCursor(24, 70);
 tft.print("Booting..");
for (int x=0;x<141;x++){
tft.setCursor(x, 78);
tft.print(".");
delay(8);
}
delay(2000);
 newv=true;
 epoch=epoch+4;
 tft.fillScreen(CYAN);
  }
 
  }
  
}else{
tft.setTextSize(2); 
tft.drawBitmap(19, 56, cloud, 40 , 23, GREY,CYAN); 
 tft.setCursor(99, 64);
 tft.print("22");
 tft.drawBitmap(125, 58, thermo, 8 , 24, WHITE,CYAN);
    tft.setCursor(10, 86); 
   tft.setCursor(13, 88);
   tft.setTextColor(WHITE,CYAN);
tft.print("better take");
tft.setCursor(13, 105);
tft.print("an umbrella");
 buttonState = digitalRead(buttonPin);
if (buttonState == LOW){
 first=false;
 newv=false;
  c=0;
  tft.fillScreen(CYAN);
  delay(1000);
    }
  }

  }
}


