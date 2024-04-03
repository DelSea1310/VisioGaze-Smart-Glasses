#include "menu.h"

#define bajar 13
#define subir 11

#define red 15
#define yellow 14
#define green 16

hw_timer_t *timer = NULL;
//int nofunciona = 0;
//int sifunciono = 0;

Menu menu;
Pantalla oled;

//volatile es un modificador, que se va a modificar dentro de la interrupción
//errores en tiempo de compilación VS en tiempo de ejecución
volatile unsigned long lastTime = 0;
volatile boolean bUp, bDown, bEnter;

volatile boolean bOption0 = true;
volatile boolean bOption1 = true;
volatile boolean bOption2 = true;


void setup() {
  //Serial.begin(115200);

  oled.begin();
  menu.begin(oled);

  menu.addItem("option1", option0);
  menu.addItem("option2", option1);
  menu.addItem("option3", option2);

  pinMode(2, OUTPUT);
  pinMode(12, INPUT_PULLUP);
  pinMode(subir, INPUT_PULLUP);
  pinMode(bajar, INPUT_PULLUP);

  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  attachInterrupt(12, enter, FALLING);
  attachInterrupt(subir, up, FALLING);
 attachInterrupt(bajar, down, FALLING);


  oled.println("Hola, bienvenido al menu");
  /*oled.println("Presiona 1 si quieres subir en el menu");
  oled.println("Presiona 0 si quieres bajar en el menu");

  oled.println("-----------------------------------------");
  oled.println("1. Mostrar hora");
  oled.println("2. Reproducir musica");
  oled.println("3. Identificar rostro");
*/
bUp = bDown = bEnter = false;

timer = timerBegin(0, 80, true);

timerAttachInterrupt(timer,blink, true);
timerAlarmWrite(timer, 1000000, true);
timerAlarmEnable(timer);

timerStop(timer);
timerStart(timer);
timerRestart(timer);

}

void loop() {
  /*
  if(nofunciona == 1)
  {
  menu.up();
  nofunciona = 0;
  }
  if(sifunciono == 1)
  {
  menu.down();
  sifunciono = 0;
  }
  
while(bOption0 == true){
}

while(bOption1 == true){
}

while(bOption2 == true){
}*/
 if(bUp){
    menu.up();
    oled.clear();
    oled.println(menu.ObtenerTexto());
    bUp = false;
    
  }
   if(bDown){
    menu.down();
    oled.clear();
    oled.println(menu.ObtenerTexto());
    bDown = false;
  }

   if(bEnter){
    menu.enter();
    oled.clear();
    oled.println(menu.ObtenerTexto());
    bEnter = false;
  }
}

void ARDUINO_ISR_ATTR blink()
{
  digitalWrite(red, !digitalRead(red) );
}

//Acceder a la RAM es más rápido que a la FLASH
//MACRO, modificador
//se trata de que las interrupciones sean algo muy rápido, que no se quede allí
void ARDUINO_ISR_ATTR enter()

{

  //si el tiempo actual menos el último tiempo
  //vuelve a entrar al ciclo solo si han pasado 50 milisegundos o más después de haber presionado el botón
  //es para el efecto antirrebote
  if( (millis() - lastTime) > 250){
    //menu.enter();
    bEnter = true;
    lastTime = millis();
    
  }
}

void ARDUINO_ISR_ATTR up()
{
  //si el tiempo actual menos el último tiempo
  //vuelve a entrar al ciclo solo si han pasado 50 milisegundos o más después de haber presionado el botón
  //es para el efecto antirrebote
  if( (millis() - lastTime) > 250){
    //menu.up();
    //nofunciona = 1;
    bUp = true;
    lastTime = millis();
    

  }
}

void ARDUINO_ISR_ATTR down()
{
  //si el tiempo actual menos el último tiempo
  //vuelve a entrar al ciclo solo si han pasado 50 milisegundos o más después de haber presionado el botón
  //es para el efecto antirrebote
  if( (millis() - lastTime) > 250){
    //menu.down();
    //sifunciono = 1;
    bDown = true;
    lastTime = millis();
  }
}

void option0()
{

  if(bOption0){
   timerRestart(timer);
   timerStart(timer);
   menu.lock();
}
  else {
    timerStop(timer);
    menu.unlock();
  }

  bOption0 = !bOption0;

  if(bOption0 == true){
  digitalWrite(red, LOW);
  }

}

void option1()
{
  digitalWrite(yellow, !digitalRead(yellow));
}

void option2()
{
  digitalWrite(green, !digitalRead(green));
}

//timers
//velocidad de entrada, prescaler
//configurar los demás botones para que no se puedan ejecutar a la vez




