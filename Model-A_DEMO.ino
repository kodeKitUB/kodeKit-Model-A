/*
*
* Official code for kodeKit NM Demo
* Created by Augustin Winther 
*
*/

/*
*
* LCD_page1 = Meny
* LCD_page2 = RGB
* LCD_page3 = Buzzer
* LCD_page4 = Display
*
*/


#include <pitches.h>
#include <themes.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

//LCD Pins
#define LCD_RST 2
#define LCD_CE NULL
#define LCD_DC 3
#define LCD_DIN 4
#define LCD_CLK 5
#define LCD_BL 6
Adafruit_PCD8544 lcd = Adafruit_PCD8544(LCD_CLK, LCD_DIN, LCD_DC, LCD_CE, LCD_RST);

//Joystick Pins
#define BTN_A 7
#define BTN_B 8
#define BTN_C 12
#define BTN_D 13
#define JOY_K A0
#define JOY_X A1
#define JOY_Y A2

//RGB Pins
#define RGB_BLUE 9
#define RGB_GREEN 10
#define RGB_RED 11

//Buzzer Pin
#define BUZZER A5

//Sesnor pins
#define SOUND A3
#define DHT A4

int LCD_contrast = 60;
int LCD_backlight = 0;
int LCD_menuItem = 1;
int LCD_page= 1;

int redVal = 0;
int greenVal = 0;
int blueVal = 0;
bool flowOn = 0;

void setup() 
{
  //Pin setup
  pinMode(BTN_A, INPUT_PULLUP);
  pinMode(BTN_B, INPUT_PULLUP);
  pinMode(BTN_C, INPUT_PULLUP);
  pinMode(BTN_D, INPUT_PULLUP);
  pinMode(LCD_BL, OUTPUT);
  
  Serial.begin(9600);
  
  //Display Setup
  lcd.begin();      
  lcd.setContrast(LCD_contrast);
  lcd.clearDisplay(); 
  lcd.display();
  drawMenu();
}

void loop() 
{
  navMenu();
  rgbFlow();
}

void drawMenu() 
{
  if (LCD_page== 1) //Meny
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
  else if (LCD_page == 3) //Buzzer menu
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
    lcd.print(LCD_backlight);
    lcd.display();
  }
}

void navMenu() 
{
  //Menu Navigation
  if ((!digitalRead(BTN_C) && LCD_page == 1 && LCD_menuItem != 3) ||
      (!digitalRead(BTN_C) && LCD_page == 2 && LCD_menuItem != 4) ||
      (!digitalRead(BTN_C) && LCD_page == 3 && LCD_menuItem != 4))
  {
    LCD_menuItem ++; //Moves down the menu
    drawMenu();
    delay(150);
  }
  else if (!digitalRead(BTN_A) && LCD_menuItem != 1) 
  {
    LCD_menuItem --; //Moves up the menu
    drawMenu();
    delay(150);
  }
  else if (!digitalRead(BTN_B) && LCD_page == 1 && LCD_menuItem == 1) 
  {
    LCD_page = 2; //Changes to RGB Menu
    drawMenu();
    delay(150);
  }
  else if (!digitalRead(BTN_B) && LCD_page == 1 && LCD_menuItem == 2) 
  {
    LCD_page = 3; //Changes to Buzzer Menu
    drawMenu();
    delay(150);
  }
  else if (!digitalRead(BTN_B) && LCD_page == 1 && LCD_menuItem == 3) 
  {
    LCD_page = 4; //Changes to Display Menu
    drawMenu();
    delay(150);
  }
  
  //RGB CONTROL
  else if (!digitalRead(BTN_B) && LCD_page == 2 && LCD_menuItem == 2) //Increase RGB_RED
  {
    rgbColor("red", 1);
    drawMenu();
    delay(1);
  }
  else if (!digitalRead(BTN_D) && LCD_page == 2 && LCD_menuItem == 2) //Decrease RGB_RED
  {
    rgbColor("red", 0);
    drawMenu();
    delay(1);
  }
  else if (!digitalRead(BTN_B) && LCD_page == 2 && LCD_menuItem == 3) //Increase RGB_GREEN
  {
    rgbColor("green", 1);
    drawMenu();
    delay(1);
  }
  else if (!digitalRead(BTN_D) && LCD_page == 2 && LCD_menuItem == 3) //Decrease RGB_GREEN
  {
    rgbColor("green", 0);
    drawMenu();
    delay(1);
  }
  else if (!digitalRead(BTN_B) && LCD_page == 2 && LCD_menuItem == 4) //Increase RGB_BLUE
  {
    rgbColor("blue", 1);
    drawMenu();
    delay(1);
  }
  else if (!digitalRead(BTN_D) && LCD_page == 2 && LCD_menuItem == 4) //Decrease RGB_BLUE
  {
    rgbColor("blue", 0);
    drawMenu();
    delay(1);
  }
  
  //BUZZER CONTROL
  else if (!digitalRead(BTN_B) && LCD_page == 3 && LCD_menuItem == 2) //Play mario theme
  {
    playSong("Mario");
    drawMenu();
    delay(150);
  }
  else if (!digitalRead(BTN_B) && LCD_page == 3 && LCD_menuItem == 3) //Play pirates theme
  {
    playSong("Pirates");
    drawMenu();
    delay(150);
  }
  else if (!digitalRead(BTN_B) && LCD_page == 3 && LCD_menuItem == 4) //Play crazy theme
  {
    playSong("Crazy");
    drawMenu();
    delay(150);
  }
  
  //DISPLAY CONTROL
  else if (!digitalRead(BTN_B) && LCD_page == 3 && LCD_menuItem == 2) //Increase Contrast
  {
    displayChange("contrast", 1);
    drawMenu();
    delay(2);
  }
  else if (!digitalRead(BTN_D) && LCD_page == 3 && LCD_menuItem == 2) //Decrease Contrast
  {
    displayChange("contrast", 0);
    drawMenu();
    delay(2);
  }
  else if (!digitalRead(BTN_B) && LCD_page == 3 && LCD_menuItem == 3) //Increase Backlight
  {
    displayChange("backlight", 1);
    drawMenu();
    delay(2);
  }
  else if (!digitalRead(BTN_D) && LCD_page == 3 && LCD_menuItem == 3) //Decrease Backlight
  {
    displayChange("backlight", 0);
    drawMenu();
    delay(2);
  }
  
  
  //Back button
  else if ( !digitalRead(BTN_D) && LCD_page != 1 && LCD_menuItem == 1) 
  {
    LCD_page = 1; //Goes back to Main meny
    drawMenu();
    delay(150);
  }
}

void rgbColor(String color, bool increase)
{
  if (color == "red" && increase && redVal != 255 )
  {
    flowOn = 0;
    redVal ++;
    analogWrite(RGB_RED, redVal);
  }
  
  if (color == "red" && !increase && redVal != 0 )
  {
    flowOn = 0;
    redVal --;
    analogWrite(RGB_RED, redVal);
  }
  
    if (color == "green" && increase && greenVal != 255 )
  {
    flowOn = 0;
    greenVal ++;
    analogWrite(RGB_GREEN, greenVal);
  }
  
  if (color == "green" && !increase && greenVal != 0 )
  {
    flowOn = 0;
    greenVal --;
    analogWrite(RGB_GREEN, greenVal);
  }
  
    if (color == "blue" && increase && blueVal != 255 )
  {
    flowOn = 0;
    blueVal ++;
    analogWrite(RGB_BLUE, blueVal);
  }
  
  if (color == "blue" && !increase && blueVal != 0 )
  {
    flowOn = 0;
    blueVal --;
    analogWrite(RGB_BLUE, blueVal);
  }
}

void playSong(String song)
{
  if (song == "Mario")
  {
    for (int thisNote = 0; thisNote < (sizeof(MarioUW_note)/sizeof(int)); thisNote++) {
      
      if (!digitalRead(BTN_A) || 
      !digitalRead(BTN_B) ||
      !digitalRead(BTN_C) ||
      !digitalRead(BTN_D))
      {
        thisNote = 100;
      }

      int noteDuration = 1000 / MarioUW_duration[thisNote];//convert duration to time delay
      tone(BUZZER, MarioUW_note[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.80;
      delay(pauseBetweenNotes);
      noTone(BUZZER); //stop music on pin 8 
    }
  }
  
  if (song == "Pirates")
  {
    for (int thisNote = 0; thisNote < (sizeof(Pirates_note)/sizeof(int)); thisNote++) {
      
      if (!digitalRead(BTN_A) || 
      !digitalRead(BTN_B) ||
      !digitalRead(BTN_C) ||
      !digitalRead(BTN_D))
      {
        thisNote = 100;
      }

      int noteDuration = 1000 / Pirates_duration[thisNote];//convert duration to time delay
      tone(BUZZER, Pirates_note[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.05; //Here 1.05 is tempo, increase to play it slower
      delay(pauseBetweenNotes);
      noTone(BUZZER); //stop music on pin 4
    }
  }
  
  if (song == "Crazy")
  {
    for (int thisNote = 0; thisNote < (sizeof(CrazyFrog_note)/sizeof(int)); thisNote++) {
      
      if (!digitalRead(BTN_A) || 
      !digitalRead(BTN_B) ||
      !digitalRead(BTN_C) ||
      !digitalRead(BTN_D))
      {
        thisNote = 100;
      }
    
      int noteDuration = 1000 / CrazyFrog_duration[thisNote]; //convert duration to time delay
      tone(BUZZER, CrazyFrog_note[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;//Here 1.30 is tempo, decrease to play it faster
      delay(pauseBetweenNotes);
      noTone(BUZZER);
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
    lcd.display();
  }
  if (setting == "contrast" && !increase && LCD_contrast > 0)
  {
    LCD_contrast --;
    lcd.display();
  }
  if (setting == "backlight" && increase && LCD_backlight < 170)
  {
    LCD_backlight ++;
    lcd.display();
  }
  if (setting == "backlight" && !increase && LCD_backlight > 0)
  {
    LCD_backlight --;
    lcd.display();
  }
}
