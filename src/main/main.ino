#include <LiquidCrystal.h>
#include <Keypad.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);  //  Объявляем объект библиотеки, указывая выводы дисплея (RS,E,D4,D5,D6,D7)

// [16; 25] - входы  IR сенсоров

// логические для подсчёта
bool Free = false;
bool FreePrev = true;
// текущее количество
int Counter = 0;
// максимальное количество до звукового сигнала
int detailMaxCount = 10;
// задержка после пролёта в мс
int delayAfterCountMsec = 0;
// текущий режим работы
bool counterInputMode = false;
bool delayInputMode = false;

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
    lcd.clear();
  // экран
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Detail Counter");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(detailMaxCount);
  lcd.print("#");
  lcd.print(delayAfterCountMsec);
  lcd.setCursor(0, 1);
  lcd.print(0);
  return;
}
void readMaxCountMode()
{
    char key = keypad.getKey();
    if (key == 'A') // закончить установку значения
    {
      counterInputMode = false;
      clearScreen();
      return;
    }
    if (key == '0' || key == '1' || key == '2' ||
    key == '3' || key == '4' || key == '5' ||
    key == '6' || key == '7' || key == '8' ||
    key == '9')
    {
      int currentDigit = atoi(&key);
      detailMaxCount = detailMaxCount * 10 + currentDigit;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("insert max count");
      lcd.setCursor(0, 1);
      lcd.print(detailMaxCount);
    }
    return;
}

void readDelayAfterCountMode()
{
    char key = keypad.getKey();
    if (key == 'B') // закончить установку значения
    {
      delayInputMode = false;
      clearScreen();
      return;
    }
    if (key == '0' || key == '1' || key == '2' ||
    key == '3' || key == '4' || key == '5' ||
    key == '6' || key == '7' || key == '8' ||
    key == '9')
    {
      int currentDigit = atoi(&key);
      delayAfterCountMsec = delayAfterCountMsec * 10 + currentDigit;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("insert delay ms");
      lcd.setCursor(0, 1);
      lcd.print(delayAfterCountMsec);
    }
    return;
}

void setup()
{
  // инфракрасные датчики - настройка пинов на чтение
  for (int i = 16; i < 26; i++)
  {
    pinMode(i, INPUT);
   } 
   // пищалка
  pinMode(52, OUTPUT);
  digitalWrite(52, LOW);
// инициализация дисплея один раз
  lcd.begin(16, 2);
  // очистка дисплея
  clearScreen();
}

void loop()
{
  if (counterInputMode != false )
  {
    readMaxCountMode();
    return;
  }
if (delayInputMode != false)
{
  readDelayAfterCountMode();
  return;
  }
  char key = keypad.getKey();
  if (key == '*') // сброс
  {
    digitalWrite(52, LOW);
    clearScreen();
    Counter = 0;
    Free = 0;
    FreePrev = 1;
    return;
  }
  // настройка количества
  if (key == 'A')
  {
    counterInputMode = true;
    detailMaxCount = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("insert max count");
    lcd.setCursor(0, 1);
    lcd.print(detailMaxCount);
    return;
  }

  // настройка задержки
  if (key == 'B')
  {
    delayInputMode = true;
    delayAfterCountMsec = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("insert delay ms");
    lcd.setCursor(0, 1);
    lcd.print(delayAfterCountMsec);
    return;
  }

  // режим подсчёта
  Free = true;
  for (int i = 16; i < 26; i++)
  {
    Free = Free && digitalRead(i);
  } 
  if (Free && !FreePrev)
  {
    // закончился пролёт детали
    Counter ++;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(detailMaxCount);
    lcd.print("#");
    lcd.print(delayAfterCountMsec);
    lcd.setCursor(0, 1);
    lcd.print(Counter);
    if (Counter > detailMaxCount)
    digitalWrite(52, HIGH);
    if (delayAfterCountMsec != 0)
    delay(delayAfterCountMsec);
  }
  FreePrev = Free;
}
