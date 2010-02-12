#include <stdlib.h>
#include <curses.h>

#include "hunt.h"

player_t PLAYER;

void init_hunt() {
  /* curses magic */
  atexit((void(*)(void))endwin);
  initscr();
}

void setup_player() {
  printf("Enter your codename: ");
  scanf("%s", PLAYER.name);
}

int main(int argc, const char* argv[]){
  
  setup_player();

  return 0;
}
