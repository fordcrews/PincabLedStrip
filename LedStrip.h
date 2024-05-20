#ifndef LedStrip_h
#define LedStrip_h

#include <Arduino.h>

#ifndef DEBUG_ON_WIFI
#define FASTLED_ALLOW_INTERRUPTS 0
#endif

#include <FastLED.h>
FASTLED_USING_NAMESPACE


//#define LED_TYPE    WS2811
//#define LED_TYPE    WS2812
#define LED_TYPE    WS2812B
//#define LED_TYPE    WS2813
//#define COLOR_ORDER RGB
#define COLOR_ORDER GRB

/*************   VALUE TO CHANGE  *******************/
//Defines the max number of ledstrip which is allowed per ledstrip.
#define MaxLedsPerStrip 1024
//Defines the number of ledstrip
#define NUMBER_LEDSTRIP 8
//#define NUMBER_LEDSTRIP 7

//Ports in configtool vs ports in wemos
//Configtool   =====   Wemos
//1            =====   D5
//4            =====   D6
//7            =====   D7
//10           =====   D8
//13           =====   D1
//16           =====   D4
//19           =====   D2
//22           =====   D3

#define DATA_PIN1  GPIO_NUM_5  
#define DATA_PIN2  GPIO_NUM_6  
#define DATA_PIN3  GPIO_NUM_7  
#define DATA_PIN4  GPIO_NUM_8  
#define DATA_PIN5  GPIO_NUM_1  
#define DATA_PIN6  GPIO_NUM_4  
#define DATA_PIN7  GPIO_NUM_2  

#if (NUMBER_LEDSTRIP == 8)
#define DATA_PIN8  GPIO_NUM_3  
#endif

// Define new GPIO pins for buttons
#define BUTTON_PIN1  GPIO_NUM_16  
#define BUTTON_PIN2  GPIO_NUM_17  
#define BUTTON_PIN3  GPIO_NUM_18 
#define BUTTON_PIN4  GPIO_NUM_21 

//Why 8 ports ? (example)
//
//PF right
//PF left
//Backpanel
//Flipper MX
//MagnaSave right
//MagnaSave left
//Undercab smart (or complex MX)
//Speaker ring (maybe using undercab complex MX ?)

//Define default Brightness settings - Those values now can be changed in cabinet.xml file like:
//
//<PerLedstripBrightness>160 255 255 0</PerLedstripBrightness> 
//Here first declared ledstrip will be lowered at 160, the two next ones will stay at full brightness, the last one will be disabled By default Wemos firmware create ledstrip at 255 brightness.
//
#define BRIGHTNESS 16 // Defines Brightness in RGB boot sequence - 16 its the minimum (1-15 strip don't iluminate at all)
#define BRIGHTNESS_PIN1 255 // Defines Brightness in pin 1 (0 to 255)
#define BRIGHTNESS_PIN2 255 // Defines Brightness in pin 2 (0 to 255)
#define BRIGHTNESS_PIN3 255 // Defines Brightness in pin 3 (0 to 255)
#define BRIGHTNESS_PIN4 255 // Defines Brightness in pin 4 (0 to 255)
#define BRIGHTNESS_PIN5 255 // Defines Brightness in pin 5 (0 to 255)
#define BRIGHTNESS_PIN6 255 // Defines Brightness in pin 6 (0 to 255)
#define BRIGHTNESS_PIN7 255 // Defines Brightness in pin 7 (0 to 255)
#if (NUMBER_LEDSTRIP == 8)
#define BRIGHTNESS_PIN8 255 // Defines Brightness in pin 8 (0 to 255)
#endif
/*************   END VALUE TO CHANGE  *******************/

class LedStrip {
  public:
    LedStrip(uint32_t numPerStrip);
    void begin(void);

    void reset();
    void addNewStrip(uint8_t index,uint16_t length);
    void setStripLength(uint16_t length);
    void setStripBrightness(uint8_t index,uint8_t brightness);
    void clearAll();
    void setPixels(uint32_t start_num,uint16_t len,int color);
    void setPixel(uint32_t num, int color);
    void setPixel(uint32_t num, uint8_t red, uint8_t green, uint8_t blue) {
      setPixel(num, color(red, green, blue));
    }
    CRGB& getPixel(uint32_t num);

    void show(void);
    int busy(void);

    int numPixels(void) {
      return stripTotalLen * 8;
    }
    int color(uint8_t red, uint8_t green, uint8_t blue) {
      return (red << 16) | (green << 8) | blue;
    }


  private:
    static uint16_t stripTotalLen;
    static uint16_t stripLen[NUMBER_LEDSTRIP];
    static uint16_t stripStartOffset[NUMBER_LEDSTRIP];
    static uint8_t stripIndex[NUMBER_LEDSTRIP*MaxLedsPerStrip];

};

#endif
