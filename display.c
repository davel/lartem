#include <curses.h>
#include <panel.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "display.h"

#include "map.h"


WINDOW *win_bg, *win_msg, *win_main, *win_stat, *win_menu;
PANEL *pnl_bg, *pnl_msg, *pnl_main, *pnl_stat, *pnl_menu;


int colours[NUM_COLOURS];


void display_init()
{
	initscr();

	/* TODO: check the screen is big enough */

	atexit(display_end);

	noecho(); nonl(); cbreak();
	curs_set(1);

	nodelay(stdscr, FALSE);


	if(has_colors()) {
		start_color();

		init_pair(1, COLOR_BLACK, COLOR_WHITE);
		colours[COL_BLACK] = COLOR_PAIR(1);

		init_pair(2, COLOR_RED, COLOR_BLACK);
		colours[COL_RED] = COLOR_PAIR(2);
		colours[COL_ORANGE] = COLOR_PAIR(2) | A_BOLD;

		init_pair(3, COLOR_GREEN, COLOR_BLACK);
		colours[COL_GREEN] = COLOR_PAIR(3);
		colours[COL_BGREEN] = COLOR_PAIR(30) | A_BOLD;

		init_pair(4, COLOR_YELLOW, COLOR_BLACK);
		colours[COL_BROWN] = COLOR_PAIR(4);
		colours[COL_YELLOW] = COLOR_PAIR(4) | A_BOLD;

		init_pair(5, COLOR_BLUE, COLOR_BLACK);
		colours[COL_BLUE] = COLOR_PAIR(5) | A_BOLD;

		init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
		colours[COL_MAGENTA] = COLOR_PAIR(6);
		colours[COL_PINK] = COLOR_PAIR(6) | A_BOLD;

		init_pair(7, COLOR_CYAN, COLOR_BLACK);
		colours[COL_CYAN] = COLOR_PAIR(7);

		colours[COL_GREY] = COLOR_PAIR(0);
		colours[COL_WHITE] = COLOR_PAIR(0) | A_BOLD;
	} else {
		unsigned int i;

		for(i = 0; i < NUM_COLOURS; i++) {
			switch(i) {
			case COL_BLACK:
				colours[i] = A_REVERSE;
				break;
			case COL_WHITE:
				colours[i] = A_BOLD;
				break;
			default:
				colours[i] = A_NORMAL;
			}
		}
	}


	/* Create windows and panels */

	win_bg = newwin(LINES, COLS, 0, 0);
	pnl_bg = new_panel(win_bg);

	win_msg = newwin(1, COLS, 0, 0);
	pnl_msg = new_panel(win_msg);

	win_main = newwin(MAP_Y, MAP_X, 1, (COLS - MAP_X) >> 1);
	pnl_main = new_panel(win_main);

	win_stat = newwin(2, COLS, LINES - 3, 0);
	pnl_stat = new_panel(win_stat);

	win_menu = newwin(LINES - 4, COLS, 0, 0);
	pnl_menu = new_panel(win_menu);

	menu_hide();
}



void display_end()
{
	endwin();
}



void display_refresh()
{
	update_panels();
	doupdate();
}


int display_getch()
{
	return getch();
}



void msg_printf(const char *fmt, ...)
{
	va_list ap;
	char str[1024];
	int x, y;

	va_start(ap, fmt);
	vsnprintf(str, 1024, fmt, ap);
	va_end(ap);

	getyx(win_msg, y, x);
	if(x && (x + strlen(str)) + 10 >= COLS) {
		mvwaddstr(win_msg, 0, COLS - 10, "  --More--");
		display_refresh();

		while(getch() != ' ');

		werase(win_msg);
		wmove(win_msg, 0, 0);
	}

	waddstr(win_msg, str);
	waddstr(win_msg, "  ");

	top_panel(pnl_msg);
	display_refresh();
}



char *msg_getstr()
{
	char str[1024];

	echo();
	wgetnstr(win_msg, str, 1024);
	noecho();

	return strdup(str);
}



void msg_clear()
{
	werase(win_msg);
	wmove(win_msg, 0, 0);
}



void main_plot(unsigned int x, unsigned int y, unsigned int col, char ch)
{
	wattrset(win_main, colours[col]);
	mvwaddch(win_main, y, x, ch);
	wmove(win_main, y, x);
	top_panel(pnl_main);
}



void main_move()
{
	wmove(win_main, y, x);
}



void main_clear()
{
	werase(win_main);
}



void stat_printf(const char *fmt, ...)
{
	va_list ap;
	char str[1024];

	va_start(ap, fmt);
	vsnprintf(str, 1024, fmt, ap);
	va_end(ap);

	werase(win_stat);
	wmove(win_stat, 0, 0);
	waddstr(win_stat, str);

	display_refresh();
}



void menu_printf(const char *fmt, ...)
{
	va_list ap;
	char str[1024];

	va_start(ap, fmt);
	vsnprintf(str, 1024, fmt, ap);
	va_end(ap);

	waddstr(win_menu, str);
}



void menu_clear()
{
	werase(win_menu);
	wmove(win_menu, 0, 0);
}



void menu_show()
{
	top_panel(pnl_menu);
	display_refresh();
}


void menu_hide()
{
	bottom_panel(pnl_menu);
	display_refresh();
}
