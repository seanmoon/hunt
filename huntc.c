#include <stdlib.h>
#include <curses.h>

#include "hunt.h"

void init_hunt() {
    
  /* curses magic */
  atexit((void(*)(void))endwin);
  initscr();

}


int main(int argc, const char* argv[]){
  
  return 0;
}