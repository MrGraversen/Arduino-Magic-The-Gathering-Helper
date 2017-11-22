#include <LiquidCrystal.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key = 0;
int adc_key_in = 0;

int mode = 0;

int life = 20;
int poison = 0;

bool released = false;
bool updated = true;

#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);
 if (adc_key_in > 1000) return btnNONE;
 if (adc_key_in < 50) return btnRIGHT;  
 if (adc_key_in < 250) return btnUP; 
 if (adc_key_in < 450) return btnDOWN; 
 if (adc_key_in < 650) return btnLEFT; 
 if (adc_key_in < 850) return btnSELECT;  
 return btnNONE;
}

void setup()
{
  lcd.begin(16, 2);
  randomSeed(analogRead(0));
  Serial.begin(9600);
}
 
void loop()
{
  lcd.setCursor(0, 0);
  lcd_key = read_LCD_buttons();

  switch (lcd_key)
  {
   case btnRIGHT:
     {
      if( released)
      {
        released = false;
        mode = mode + 1;
        lcd.print(fillLine(getModeText()));
        updated = true;
      }
      break;
     }
   case btnLEFT:
     {
      if (released)
      {
        released = false;
        mode = mode - 1;
        lcd.print(fillLine(getModeText()));
        updated = true;
      }
      break;
     }
   case btnUP:
     {
      if (released)
      {
        released = false;
        
        switch (mode)
        {
          case 0:
          {
            life = life + 1;
            updated = true;
            break;
          }
          case 1:
          {
            poison = poison + 1;
            updated = true;
            break;
          }
        }
      }
      break;
     }
   case btnDOWN:
     {
      if (released)
      {
        released = false;
        
        switch (mode)
        {
          case 0:
          {
            life = life - 1;
            if (life < 0) life = 0;
            updated = true;
            break;
          }
          case 1:
          {
            poison = poison - 1;
            if (poison < 0) poison = 0;
            updated = true;
            break;
          }
        }
      }
      break;
     }
   case btnSELECT:
     {
      if (released)
      {
        released = false;
        
        switch (mode)
        {
          case 2:
          {
            updated = true;
            break;
          }
          case 3:
          {
            updated = true;
            break;
          }
          case 4:
          {
            updated = true;
            break;
          }
        }
      }
      break;      
     }
     case btnNONE:
     {
      released = true;

      lcd.print(fillLine(getModeText()));
      
      if (updated)
      {
        printInfo();
        updated = false;
      }
            
      break;
     }
  }

  delay(5);
}

String fillLine(String text)
{
  int stringLength = text.length();

  for (int i = stringLength; i < 16; i++)
  {
    text.concat(" "); // Add whitespace
  }

  return text;
}

void printInfo()
{
  lcd.setCursor(0, 1);

  switch (mode)
  {
    case 0:
    {
      lcd.print(fillLine(String(life)));
      break;
    }
    case 1:
    {
      lcd.print(fillLine(String(poison)));
      break;
    }
    case 2:
    {
      lcd.print(fillLine(String(random(1, 7))));
      break;
    }
    case 3:
    {
      lcd.print(fillLine(String(random(1, 21))));
      break;
    }
    case 4:
    {
      lcd.print(fillLine(coin()));
      break;
    }
  }
}

String getModeText()
{
  if (mode < 0) mode = 0;
  if (mode > 4) mode = 4;
  
  switch (mode)
  {
    case 0: { return "LIFE"; break; }
    case 1: { return "POISON"; break; }
    case 2: { return "ROLL (6)"; break; }
    case 3: { return "ROLL (20)"; break; }
    case 4: { return "FLIP COIN"; break; }
  }
}

String coin()
{
  int r = random(1, 101);

  if (r > 50)
  {
    return "HEADS";
  }
  else
  {
    return "TAILS";
  }
}

