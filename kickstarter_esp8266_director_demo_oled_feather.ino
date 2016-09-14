
    #include <SPI.h>
    #include <Wire.h>
    #include <Adafruit_GFX.h>
    #include <Adafruit_SSD1306.h>
     
     
    #define OLED_RESET 3
    Adafruit_SSD1306 display(OLED_RESET);
    #if (SSD1306_LCDHEIGHT != 32)
    #error("Height incorrect, please fix Adafruit_SSD1306.h!");
    #endif
     
    void setup() {
     
      display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
      display.clearDisplay();
    }
     
    void loop() {
       display.clearDisplay();
       display.setTextSize(1);
      display.setTextColor(WHITE);
          display.setCursor(0,0);
          display.println("Fridge Controller v4");
          display.println("---------------------");
            display.println("");
          display.println("IN: 7C     OUT: 24C");
          display.display();   
      delay(5000);
      display.clearDisplay();
       display.display(); 
          delay(2000);
          display.clearDisplay();
       display.setTextSize(1);
      display.setTextColor(WHITE);
          display.setCursor(0,0);
          display.println("Fridge Controller v5");
          display.println("---------------------");
            display.println("");
          display.println("IN: 6C    OUT: 24C");
          display.display(); 
     delay(10000);
    }
   
