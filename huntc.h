#ifndef HUNT__HUNTC_H
#define HUNT__HUNTC_H

#include "hunt.h"
#define MAZE_WIN_HEIGHT    (MAZEHEIGHT + 2)
#define MAZE_WIN_WIDTH     (MAZEWIDTH + 2)
#define MAZE_WIN_XSTART      0
#define MAZE_WIN_YSTART      0
#define STATUS_WIN_HEIGHT   23
#define STATUS_WIN_WIDTH    13
#define STATUS_WIN_YSTART    0
#define STATUS_WIN_XSTART   67
#define MESSAGE_WIN_HEIGHT   2
#define MESSAGE_WIN_WIDTH   80
#define MESSAGE_WIN_YSTART  22 
#define MESSAGE_WIN_XSTART   0

WINDOW* status_win;
WINDOW* maze_win;
WINDOW* message_win;

#endif
