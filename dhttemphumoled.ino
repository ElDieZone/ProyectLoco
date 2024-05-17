
#include <DHT.h>
#include <DHT_U.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT   84
#define LOGO_WIDTH    52

int SENSOR = 2;
int TEMPERATURA;
int HUMEDAD;

DHT dht(SENSOR, DHT22);



void setup(){
  Serial.begin(9600);
  
  dht.begin(9660);
  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hola Loco");
   display.setTextSize(1);
  display.setCursor(35,25);
  display.println("empieza");
  display.display();
  delay(3000);

}


void loop(){
    
    TEMPERATURA = dht.readTemperature();
    HUMEDAD = dht.readHumidity();

    display.clearDisplay();
     display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("temperatura");
    display.setCursor(80,0);
    display.println("humedad");
    display.drawLine(70, 0, 70, 32, WHITE);
    display.drawLine(0, 10, 128, 10, WHITE);
    
    
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(20,15);
    display.println(TEMPERATURA);
    display.setCursor(90,15);
    display.println(HUMEDAD);
    display.display();
    
    delay(100);

    
    
        
  }

