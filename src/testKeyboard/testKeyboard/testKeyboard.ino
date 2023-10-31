#include <Keypad.h> // Подключаем библиотеку 
const byte ROWS = 4; // 4 строки
const byte COLS = 4; // 4 столбца
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
}; 
byte rowPins[ROWS] = {8, 9, 10, 11};
byte colPins[COLS] = {12, 13, 14, 15};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void setup(){
  Serial.begin(9600);
}
void loop(){
  char key = keypad.getKey();
  if (key){
    Serial.println(key); // Передаем название нажатой клавиши в сериал порт
    tone(3, (int)key*10, 300); // Издаем звуковой сигнал длиной 300 миллисекунд 
  }
}
