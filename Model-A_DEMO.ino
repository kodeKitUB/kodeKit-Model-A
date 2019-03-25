/*
*
* Official code for kodeKit NM Demo
* Created by Augustin Winther 
* NOTE!
* D3 PWM is disabled when using the tone();
*/

/*
*
*
*/


#include <TroykaDHT.h>
#include <pitches.h>
#include <themes.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

//LCD Pins
#define LCD_RST 7
#define LCD_CE NULL
#define LCD_DC 3
#define LCD_DIN 5
#define LCD_CLK 4
#define LCD_BL 6
Adafruit_PCD8544 lcd = Adafruit_PCD8544(LCD_CLK, LCD_DIN, LCD_DC, LCD_CE, LCD_RST);

//Joystick Pins
#define JOY_A 12
#define JOY_B 13
#define JOY_C A0
#define JOY_D A1
#define JOY_K A2
#define JOY_X A3
#define JOY_Y A4

//RGB Pins
#define RGB_R 9
#define RGB_G 10
#define RGB_B 11

//BUZZER_S Pin
#define BUZZER_S 8

//Sesnor pins
#define LYD_DO 2
#define DHT_OUT A5

DHT dht(DHT_OUT, DHT11);

int LCD_contrast = 60;
int LCD_backlight = 100;
int LCD_menuItem = 1;
int LCD_page = 1;
int LCD_lastMenuItem = 1;
int LCD_lastPage = 1;

int redVal = 0;
int greenVal = 0;
int blueVal = 0;
bool flowOn = 0;

float humi = dht.getHumidity();
float temp = dht.getTemperatureC();

int clapCount = 0;
bool clapEnabled = 0;
unsigned long prevMillis = 0;
unsigned long currMillis = 0;

int randInt = 0;
int oldRand = 0;

const uint8_t PROGMEM kodekitLogo[] = { 
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00011000,B11000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B01100000,B00110000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000001,B10000000,B00001100,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000110,B00000000,B00000011,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00011000,B00000000,B00000000,B11000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B01100000,B00000000,B00000000,B00110000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B01100000,B00000000,B00000000,B00110000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B01011000,B00000000,B00000000,B11010001,B00000000,B00000000,B00010000,B00000010,B00010010,B00000000,B00000000,
B01000110,B00000000,B00000011,B00010001,B00000000,B00000000,B00010000,B00000010,B00110010,B01000000,B00000000,
B01000001,B10000000,B00001100,B00010001,B00000000,B00000000,B00010000,B00000010,B00100000,B01000000,B00000000,
B01000000,B01100000,B00110001,B10010001,B00010001,B11000001,B11110001,B11000010,B01000010,B01110000,B00000000,
B01000000,B10011000,B11000001,B10010001,B00100010,B00100011,B00010010,B00100010,B10000010,B01000000,B00000000,
B01000000,B10000111,B00000000,B10010001,B01000010,B00100010,B00010010,B00100011,B10000010,B01000000,B00000000,
B01011101,B10000010,B00010000,B11010001,B11000010,B00100010,B00010011,B11100010,B10000010,B01000000,B00000000,
B01010001,B00000010,B00100000,B01010001,B01100010,B00100010,B00010010,B00000010,B01000010,B01000000,B00000000,
B01001001,B01000010,B00100000,B10010001,B00100010,B00100010,B00010010,B00000010,B00100010,B01000000,B00000000,
B01000101,B00100010,B00100000,B10010001,B00010010,B00100011,B00010010,B00100010,B00110010,B01100000,B00000000,
B01000001,B00010010,B01100000,B10010001,B00011001,B11000001,B11110001,B11000010,B00010010,B00110000,B00000000,
B01000001,B01110010,B01100000,B10010000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111,B11100000,
B01100011,B01000010,B00100001,B00110000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00011000,B00000010,B00110000,B11000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000110,B00000010,B00010011,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000001,B10000010,B00001100,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B01100010,B00110000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00011010,B11000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
};

void setup() 
{
  //Pin setup
  pinMode(JOY_A, INPUT_PULLUP);
  pinMode(JOY_B, INPUT_PULLUP);
  pinMode(JOY_C, INPUT_PULLUP);
  pinMode(JOY_D, INPUT_PULLUP);
  pinMode(LCD_BL, OUTPUT);
  analogWrite(LCD_BL, LCD_backlight);
  
  pinMode(LYD_DO, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LYD_DO), clapIncr, CHANGE);
  
  Serial.begin(9600);
  
  //Display Setup
  lcd.begin();      
  lcd.setContrast(LCD_contrast);
  
  lcd.clearDisplay();
  lcd.drawBitmap(0,0, kodekitLogo, 84, 48, 1);
  lcd.display();
  
  delay(3000);
  
  lcd.clearDisplay(); 
  lcd.display();
  drawMenu();
  
  //Sensor setup
  dht.begin();

}

void loop() 
{
  //Reads Temprature and Humodity
  dht.read();
  temp = dht.getTemperatureC();
  humi = dht.getHumidity();
  
  navMenu();
  rgbFlow();
  drawMenu();
}

void drawMenu() 
{
  if (LCD_page == 1) //Meny
  {    
    lcd.setTextSize(1);
    lcd.clearDisplay();
    lcd.setTextColor(BLACK, WHITE);
    lcd.setCursor(30, 0);
    lcd.print("MENY");
    lcd.drawFastHLine(0,10,83,BLACK);
   
    //******************//
    if (LCD_menuItem == 1) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 15);
    lcd.print("> RGB Lys");
   
    //******************//   
    if (LCD_menuItem == 2) 
    {
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 25);
    lcd.print("> Buzzer");
    
    //******************//
    if (LCD_menuItem == 3) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }  
    lcd.setCursor(0, 35);
    lcd.print("> Display");
    lcd.display();
  }

/**************************************/  
  if (LCD_page == 10) //Meny2
  {    
    lcd.setTextSize(1);
    lcd.clearDisplay();
    lcd.setTextColor(BLACK, WHITE);
    lcd.setCursor(30, 0);
    lcd.print("MENY");
    lcd.drawFastHLine(0,10,83,BLACK);
   
    //******************//
    if (LCD_menuItem == 1) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 15);
    lcd.print("> Buzzer");
   
    //******************//   
    if (LCD_menuItem == 2) 
    {
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 25);
    lcd.print("> Display");
    
    //******************//
    if (LCD_menuItem == 3) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }  
    lcd.setCursor(0, 35);
    lcd.print("> Temp Sensor");
    lcd.display();
  }
  
/**************************************/  
  if (LCD_page == 20) //Meny3
  {    
    lcd.setTextSize(1);
    lcd.clearDisplay();
    lcd.setTextColor(BLACK, WHITE);
    lcd.setCursor(30, 0);
    lcd.print("MENY");
    lcd.drawFastHLine(0,10,83,BLACK);
   
    //******************//
    if (LCD_menuItem == 1) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 15);
    lcd.print("> Display");
   
    //******************//   
    if (LCD_menuItem == 2) 
    {
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 25);
    lcd.print("> Temp Sensor");
    
    //******************//
    if (LCD_menuItem == 3) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }  
    lcd.setCursor(0, 35);
    lcd.print("> Lyd Sensor");
    lcd.display();
  }
  
  /**************************************/
  else if (LCD_page== 2) //RGB
  {
    lcd.setTextSize(1);
    lcd.clearDisplay();
    
    //******************//
    if (LCD_menuItem == 1) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 0);
    lcd.print("< Tilbake");
   
    //******************//
    if (LCD_menuItem == 2) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 10);
    lcd.print("R < ");
    lcd.setCursor(19, 10);
    lcd.print(redVal);
    lcd.setCursor(37, 10);
    lcd.print(">");
   
    //******************//
    if (LCD_menuItem == 3) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 20);
    lcd.print("G < ");
    lcd.setCursor(19, 20);
    lcd.print(greenVal);
    lcd.setCursor(37, 20);
    lcd.print(">");
    
    //******************//
    if (LCD_menuItem == 4) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 30);
    lcd.print("B < ");
    lcd.setCursor(19, 30);
    lcd.print(blueVal);
    lcd.setCursor(37, 30);
    lcd.print(">");
    lcd.display();
   
  }
  
  /**************************************/
  else if (LCD_page == 3) //BUZZER_S menu
  {
    lcd.setTextSize(1);
    lcd.clearDisplay();
    
    //******************//
    if (LCD_menuItem == 1) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 0);
    lcd.print("< Tilbake");
   
    //******************//
    if (LCD_menuItem == 2) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 10);
    lcd.print("Mario Theme");
   
    //******************//
    if (LCD_menuItem == 3) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 20);
    lcd.print("Pirates theme");
    
    //******************//
    if (LCD_menuItem == 4) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 30);
    lcd.print("Crazy Frog");
    lcd.display();
  }
  
  /**************************************/
  else if (LCD_page == 4) //Display menu
  {
    lcd.setTextSize(1);
    lcd.clearDisplay();
    
    //******************//
    if (LCD_menuItem == 1) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 0);
    lcd.print("< Tilbake");
   
    //******************//
    if (LCD_menuItem == 2) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 10);
    lcd.print("Contrast");
    lcd.setCursor(60, 10);
    lcd.print(LCD_contrast);
    
    //******************//
    if (LCD_menuItem == 3) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 20);
    lcd.print("Backlight");
    lcd.setCursor(60, 20);
    float backlightVolt = LCD_backlight * 0.0196;
    lcd.print(backlightVolt);
    lcd.display();
  }
  
  /**************************************/
  else if (LCD_page == 5) //Temp meny
  {
    lcd.setTextSize(1);
    lcd.clearDisplay();
    
    //******************//
    if (LCD_menuItem == 1) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 0);
    lcd.print("< Tilbake");
   
    //******************//
    if (LCD_menuItem == 2) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 15);
    lcd.print("Temp:");
    lcd.setCursor(36, 15);
    lcd.print(temp);
    lcd.setCursor(66, 15);
    lcd.print("C");
    
    //******************//
    if (LCD_menuItem == 3) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 25);
    lcd.print("Fukt:");
    lcd.setCursor(36, 25);
    lcd.print(humi);
    lcd.setCursor(66, 25);
    lcd.print("%");
    lcd.display();
  }
  
  /**************************************/
  else if (LCD_page == 6) //Lyd meny
  {
    lcd.setTextSize(1);
    lcd.clearDisplay();
    
    //******************//
    if (LCD_menuItem == 1) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(0, 0);
    lcd.print("< Tilbake");
   
    //******************//
    if (LCD_menuItem == 2) 
    { 
      lcd.setTextColor(WHITE, BLACK);
    }
    else 
    {
      lcd.setTextColor(BLACK, WHITE);
    }
    lcd.setCursor(18, 15);
    lcd.print("Teller");
    lcd.setCursor(35, 25);
    lcd.print(clapCount);
    lcd.display();
  }
}

void navMenu() 
{
  //Menu Navigation
  if ((!digitalRead(JOY_C) && LCD_page == 1 && LCD_menuItem != 3) ||
      (!digitalRead(JOY_C) && LCD_page == 2 && LCD_menuItem != 4) ||
      (!digitalRead(JOY_C) && LCD_page == 3 && LCD_menuItem != 4) ||
      (!digitalRead(JOY_C) && LCD_page == 4 && LCD_menuItem != 3) ||
      (!digitalRead(JOY_C) && LCD_page == 5 && LCD_menuItem != 1) ||
      (!digitalRead(JOY_C) && LCD_page == 6 && LCD_menuItem != 1) ||
      (!digitalRead(JOY_C) && LCD_page == 10 && LCD_menuItem != 3) ||
      (!digitalRead(JOY_C) && LCD_page == 20 && LCD_menuItem != 3))
  {
    LCD_menuItem ++; //Moves down the menu
    drawMenu();
    delay(150);
  }
  else if (!digitalRead(JOY_A) && LCD_menuItem != 1) 
  {
    LCD_menuItem --; //Moves up the menu
    drawMenu();
    delay(150);
  }
  else if (!digitalRead(JOY_B) && LCD_page == 1 && LCD_menuItem == 1) 
  {
    LCD_lastMenuItem = LCD_menuItem;
    LCD_lastPage = LCD_page;
    
    LCD_page = 2; //Changes to RGB Menu
    analogWrite(RGB_R, redVal);
    analogWrite(RGB_G, greenVal);
    analogWrite(RGB_B, blueVal);
    LCD_menuItem = 1;
    drawMenu();
    delay(150);
  }
  else if ((!digitalRead(JOY_B) && LCD_page == 1 && LCD_menuItem == 2) ||
           (!digitalRead(JOY_B) && LCD_page == 10 && LCD_menuItem == 1)) 
  {
    LCD_lastMenuItem = LCD_menuItem;
    LCD_lastPage = LCD_page;
    
    LCD_page = 3; //Changes to BUZZER_S Menu
    LCD_menuItem = 1;
    drawMenu();
    delay(150);
  }
  else if ((!digitalRead(JOY_B) && LCD_page == 1 && LCD_menuItem == 3) ||
           (!digitalRead(JOY_B) && LCD_page == 10 && LCD_menuItem == 2) ||
           (!digitalRead(JOY_B) && LCD_page == 20 && LCD_menuItem == 1)) 
  {
    LCD_lastMenuItem = LCD_menuItem;
    LCD_lastPage = LCD_page;
    
    LCD_page = 4; //Changes to Display Menu
    LCD_menuItem = 1;
    drawMenu();
    delay(150);
  }
  else if ((!digitalRead(JOY_B) && LCD_page == 10 && LCD_menuItem == 3) ||
           (!digitalRead(JOY_B) && LCD_page == 20 && LCD_menuItem == 2)) 
  {
    LCD_lastMenuItem = LCD_menuItem;
    LCD_lastPage = LCD_page;
    
    LCD_page = 5; //Changes to Temp Menu
    LCD_menuItem = 1;
    drawMenu();
    delay(150);
  }
  else if (!digitalRead(JOY_B) && LCD_page == 20 && LCD_menuItem == 3) 
  {
    LCD_lastMenuItem = LCD_menuItem;
    LCD_lastPage = LCD_page;
    clapEnabled = 1;
    
    LCD_page = 6; //Changes to Lyd Menu
    LCD_menuItem = 1;
    drawMenu();
    delay(150);
  }
  
  else if (!digitalRead(JOY_C) && LCD_page == 1 && LCD_menuItem == 3) 
  {
    LCD_page = 10; //Scrolls down
    drawMenu();
    delay(150);
  }
  else if (!digitalRead(JOY_C) && LCD_page == 10 && LCD_menuItem == 3) 
  {
    LCD_page = 20; //Scrolls down
    drawMenu();
    delay(150);
  }
  else if (!digitalRead(JOY_A) && LCD_page == 10 && LCD_menuItem == 1) 
  {
    LCD_page = 1; //Scrolls up
    drawMenu();
    delay(150);
  }
  else if (!digitalRead(JOY_A) && LCD_page == 20 && LCD_menuItem == 1) 
  {
    LCD_page = 10; //Scrolls up
    drawMenu();
    delay(150);
  }
  
  //RGB CONTROL
  else if (!digitalRead(JOY_B) && LCD_page == 2 && LCD_menuItem == 2) //Increase RGB_R
  {
    rgbColor("red", 1);
    drawMenu();
    delay(1);
  }
  else if (!digitalRead(JOY_D) && LCD_page == 2 && LCD_menuItem == 2) //Decrease RGB_R
  {
    rgbColor("red", 0);
    drawMenu();
    delay(1);
  }
  else if (!digitalRead(JOY_B) && LCD_page == 2 && LCD_menuItem == 3) //Increase RGB_G
  {
    rgbColor("green", 1);
    drawMenu();
    delay(1);
  }
  else if (!digitalRead(JOY_D) && LCD_page == 2 && LCD_menuItem == 3) //Decrease RGB_G
  {
    rgbColor("green", 0);
    drawMenu();
    delay(1);
  }
  else if (!digitalRead(JOY_B) && LCD_page == 2 && LCD_menuItem == 4) //Increase RGB_B
  {
    rgbColor("blue", 1);
    drawMenu();
    delay(1);
  }
  else if (!digitalRead(JOY_D) && LCD_page == 2 && LCD_menuItem == 4) //Decrease RGB_B
  {
    rgbColor("blue", 0);
    drawMenu();
    delay(1);
  }
  
  //BUZZER_S CONTROL
  else if (!digitalRead(JOY_B) && LCD_page == 3 && LCD_menuItem == 2) //Play mario theme
  {
    playSong("Mario");
    drawMenu();
    delay(150);
  }
  else if (!digitalRead(JOY_B) && LCD_page == 3 && LCD_menuItem == 3) //Play pirates theme
  {
    playSong("Pirates");
    drawMenu();
    delay(150);
  }
  else if (!digitalRead(JOY_B) && LCD_page == 3 && LCD_menuItem == 4) //Play crazy theme
  {
    playSong("Crazy");
    drawMenu();
    delay(150);
  }
  
  //DISPLAY CONTROL
  else if (!digitalRead(JOY_B) && LCD_page == 4 && LCD_menuItem == 2) //Increase Contrast
  {
    displayChange("contrast", 1);
    drawMenu();
    delay(2);
  }
  else if (!digitalRead(JOY_D) && LCD_page == 4 && LCD_menuItem == 2) //Decrease Contrast
  {
    displayChange("contrast", 0);
    drawMenu();
    delay(2);
  }
  else if (!digitalRead(JOY_B) && LCD_page == 4 && LCD_menuItem == 3) //Increase Backlight
  {
    displayChange("backlight", 1);
    drawMenu();
    delay(2);
  }
  else if (!digitalRead(JOY_D) && LCD_page == 4 && LCD_menuItem == 3) //Decrease Backlight
  {
    displayChange("backlight", 0);
    drawMenu();
    delay(2);
  }
  
  //Back button
  else if (((!digitalRead(JOY_D) || (!digitalRead(JOY_B)) && LCD_page != 1 && LCD_menuItem == 1)))
  {
    LCD_menuItem = LCD_lastMenuItem; //Goes back to Main meny
    LCD_page = LCD_lastPage;
    clapEnabled = 0; //Diables clapping
    setColor(0,0,0);
    drawMenu();
    delay(150);
  }
}

void rgbColor(String color, bool increase)
{
  if (color == "red" && increase && redVal < 255 )
  {
    flowOn = 0;
    redVal += 5;
    analogWrite(RGB_R, redVal);
  }
  
  if (color == "red" && !increase && redVal > 0 )
  {
    flowOn = 0;
    redVal -= 5;
    analogWrite(RGB_R, redVal);
  }
  
  if (color == "green" && increase && greenVal < 255 )
  {
    flowOn = 0;
    greenVal += 5;
    analogWrite(RGB_G, greenVal);
  }
  
  if (color == "green" && !increase && greenVal > 0 )
  {
    flowOn = 0;
    greenVal -= 5;
    analogWrite(RGB_G, greenVal);
  }
  
  if (color == "blue" && increase && blueVal < 255 )
  {
    flowOn = 0;
    blueVal += 5;
    analogWrite(RGB_B, blueVal);
  }
  
  if (color == "blue" && !increase && blueVal != 0 )
  {
    flowOn = 0;
    blueVal -= 5;
    analogWrite(RGB_B, blueVal);
  }
}

void playSong(String song)
{
  if (song == "Mario")
  {
    for (int thisNote = 0; thisNote < (sizeof(MarioUW_note)/sizeof(int)); thisNote++) {
      
      int noteDuration = 1000 / MarioUW_duration[thisNote];//convert duration to time delay
      tone(BUZZER_S, MarioUW_note[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.80;
      delay(pauseBetweenNotes);
      
      if (!digitalRead(JOY_A) || 
          !digitalRead(JOY_B) ||
          !digitalRead(JOY_C) ||
          !digitalRead(JOY_D))
      {
        thisNote = 100;
      }
      
      noTone(BUZZER_S);
    }
  }
  
  if (song == "Pirates")
  {
    for (int thisNote = 0; thisNote < (sizeof(Pirates_note)/sizeof(int)); thisNote++) {
  
      int noteDuration = 1000 / Pirates_duration[thisNote];//convert duration to time delay
      tone(BUZZER_S, Pirates_note[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.05; //Here 1.05 is tempo, increase to play it slower
      delay(pauseBetweenNotes);
      
      if (!digitalRead(JOY_A) || 
          !digitalRead(JOY_B) ||
          !digitalRead(JOY_C) ||
          !digitalRead(JOY_D))
      {
        thisNote = 100;
      }
      
      noTone(BUZZER_S);
    }
  }
  
  if (song == "Crazy")
  {
    for (int thisNote = 0; thisNote < (sizeof(CrazyFrog_note)/sizeof(int)); thisNote++) {
    
      int noteDuration = 1000 / CrazyFrog_duration[thisNote]; //convert duration to time delay
      tone(BUZZER_S, CrazyFrog_note[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;//Here 1.30 is tempo, decrease to play it faster
      delay(pauseBetweenNotes);
      
      if (!digitalRead(JOY_A) || 
          !digitalRead(JOY_B) ||
          !digitalRead(JOY_C) ||
          !digitalRead(JOY_D))
      {
        thisNote = 100;
      }
      
      noTone(BUZZER_S);
    }
  }
}

void rgbFlow()
{
  if (flowOn)
  {
    //DO SOMETHING
  }
}

void displayChange(String setting, bool increase)
{
  if (setting == "contrast" && increase && LCD_contrast < 100)
  {
    LCD_contrast ++;
    lcd.setContrast(LCD_contrast);
  }
  if (setting == "contrast" && !increase && LCD_contrast > 0)
  {
    LCD_contrast --;
    lcd.setContrast(LCD_contrast);
  }
  if (setting == "backlight" && increase && LCD_backlight < 170)
  {
    LCD_backlight += 5;
    analogWrite(LCD_BL, LCD_backlight);
  }
  if (setting == "backlight" && !increase && LCD_backlight > 0)
  {
    LCD_backlight -= 5;
    analogWrite(LCD_BL, LCD_backlight);
  }
}

void clapIncr()
{
  currMillis = millis();
  
  if ((currMillis - prevMillis  >= 150) && clapEnabled)
  {
    prevMillis = currMillis;
    newColor();
    clapCount ++; 
  }
}

void newColor()
{
  int colors[6][3] = {
    {200, 0, 0},
    {0, 200, 0},
    {0, 0, 200},
    {200, 200, 0},
    {80, 0, 80},
    {0, 255, 255}
  }; //Detta har tommy laga
  
  randInt = random(0,5);
  
  while (randInt == oldRand)
  {
    randInt = random(0,5);
  }
  
  oldRand = randInt;
  setColor(colors[randInt][0], colors[randInt][1], colors[randInt][2]);
}

void setColor(int red, int green, int blue)
{
  analogWrite(RGB_R, red);
  analogWrite(RGB_G, green);
  analogWrite(RGB_B, blue);  
}
