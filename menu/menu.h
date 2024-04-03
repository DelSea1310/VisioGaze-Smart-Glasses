#include <Arduino.h>
#include "pantalla.h"

typedef void (*fptr)(void);

class MenuItem
{
private:
  const char* text;
  fptr callback;
public:
  MenuItem(const char* text, fptr callback);
  const char* getText();
  fptr getCallback();
};

class Menu  : public Stream
{
private:
  uint8_t index;
  uint8_t n_items;
  MenuItem* items[10];
  
  boolean isLock;
  Pantalla *menuPantalla;
public:
//constructor
  Menu();
  void begin(Pantalla &pantalla);
  void addItem(const char* text, fptr callback);
  void up();
  void down();
  void enter();
  void lock();
  void unlock();
  const char *ObtenerTexto();
  // Métodos virtuales requeridos por la clase Stream
  virtual size_t write(uint8_t);
  virtual int available();
  virtual int read();
  virtual int peek();
  virtual void flush();
};