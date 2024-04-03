#include "menu.h"

MenuItem::MenuItem(const char* text, fptr callback):
text(text),
callback(callback)
{
 /* text = text;
  callback = callback;*/
}

const char* MenuItem::getText()
{
  return text;
}

fptr MenuItem::getCallback()
{
  return callback;
}

Menu::Menu()
{
  index = 0;
  n_items = 0;
  menuPantalla = NULL;
  isLock = false;
}

void Menu::lock()
{
  isLock = true;
}

void Menu::unlock()
{
  isLock = false;
}

void Menu::begin(Pantalla &pantalla)
{
    menuPantalla = &pantalla;
    menuPantalla->begin();
}

void Menu::addItem(const char* text, fptr callback)
{
  if(n_items < 10){
    items[n_items] = new MenuItem(text, callback);
    n_items++;
  }
  
}

void Menu::up()
{
  if(index < n_items-1 && !isLock){
  index ++;
  if(menuPantalla != NULL)
    menuPantalla->println(items[index]->getText());
  }
}

void Menu::down()
{
  if(index > 0 && !isLock){
  index--;
  if(menuPantalla != NULL)
  menuPantalla->println(items[index]->getText());
  }
}

void Menu::enter()
{
  fptr callback = items[index]->getCallback();

  if(callback != NULL) callback();
}

/*void Menu::display()
{
  
}*/

const char *Menu::ObtenerTexto() {
  if (index < n_items) {
    return items[index]->getText();
  }
  return "";
}


size_t Menu::write(uint8_t) {
  // Implementación de write según tus necesidades
  return 0;
}

int Menu::available() {
  // Implementación de available según tus necesidades
  return 0;
}

int Menu::read() {
  // Implementación de read según tus necesidades
  return -1;
}

int Menu::peek() {
  // Implementación de peek según tus necesidades
  return -1;
}

void Menu::flush() {
  // Implementación de flush según tus necesidades
}
