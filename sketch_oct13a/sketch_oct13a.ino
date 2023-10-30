#include <LiquidCrystal.h>
#include <Keypad.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);  //  Объявляем объект библиотеки, указывая выводы дисплея (RS,E,D4,D5,D6,D7)

// [16; 25] - входы  IR сенсоров

#define beepPin 52

int Free = 0;
int FreePrev = 1;
int Counter = 0;
int keyboardModeNow = 0;
int detailMaxCount = 10;

const byte ROWS = 4; // 4 строки
const byte COLS = 4; // 4 столбца
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {8, 9, 10, 11};
byte colPins[COLS] = {12, 13, 14, 15};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void clearScreen()
{
  // экран
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Detail Counter");
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("Details:");
  lcd.setCursor(0, 1);
  lcd.print(0);
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("Details:");
  lcd.setCursor(0, 1);
  lcd.print(0);
}
void screenPrintDigit(int d)
{
  // экран
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("Details:");
  lcd.setCursor(0, 1);
  lcd.print(d);
}
void setup()
{
  // инфракрасные датчики - настройка пинов на чтение
  

  pinMode(InPin_00, INPUT);
  pinMode(InPin_01, INPUT);
  pinMode(InPin_02, INPUT);
  pinMode(InPin_03, INPUT);
  pinMode(InPin_04, INPUT);
  pinMode(InPin_05, INPUT);
  pinMode(InPin_06, INPUT);
  pinMode(InPin_07, INPUT);
  pinMode(InPin_08, INPUT);
  pinMode(InPin_09, INPUT);
  pinMode(beepPin, OUTPUT);
  digitalWrite(beepPin, LOW);

  lcd.begin(16, 2);
  clearScreen();
}

void loop()
{
  if (keyboardModeNow != 0 )
  {
    char key = keypad.getKey();
    if (key == 'A') // закончить установку значения
    {
      keyboardModeNow = 0;
    }
    else if (key == '0')
    {
      detailMaxCount = detailMaxCount * 10;
    }
    else if (key == '1')
    {
      detailMaxCount = detailMaxCount * 10 + 1;
    }
    else if (key == '2')
    {
      detailMaxCount = detailMaxCount * 10 + 2;
    }
    else if (key == '3')
    {
      detailMaxCount = detailMaxCount * 10 + 3;
    }
    else if (key == '4')
    {
      detailMaxCount = detailMaxCount * 10 + 4;
    }
    else if (key == '5')
    {
      detailMaxCount = detailMaxCount * 10 + 5;
    }
    else if (key == '6')
    {
      detailMaxCount = detailMaxCount * 10 + 6;
    }
    else if (key == '7')
    {
      detailMaxCount = detailMaxCount * 10 + 7;
    }
    else if (key == '8')
    {
      detailMaxCount = detailMaxCount * 10 + 8;
    }
    else if (key == '9')
    {
      detailMaxCount = detailMaxCount * 10 + 9;
    }
  }

  char key = keypad.getKey();
  if (key == '*' && keyboardModeNow == 0) // сброс
  {
    clearScreen();
    Counter = 0;
  }
  if (key == '#' && keyboardModeNow == 0)
  {
    keyboardModeNow = 1;
    detailMaxCount = 0;
  }
  Free =
    digitalRead(InPin_00) &&
    digitalRead(InPin_01) &&
    digitalRead(InPin_02) &&
    digitalRead(InPin_03) &&
    digitalRead(InPin_04) &&
    digitalRead(InPin_05) &&
    digitalRead(InPin_06) &&
    digitalRead(InPin_07) &&
    digitalRead(InPin_08) &&
    digitalRead(InPin_09);

  if (Free && !FreePrev)
  {
    // закончился пролёт детали
    Counter ++;
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(Counter);
    if (Counter > detailMaxCount)
    digitalWrite(beepPin, HIGH);
  }
  FreePrev = Free;
}
