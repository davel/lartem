#ifndef DISPLAY_H
#define DISPLAY_H


enum {
	COL_BLACK,
	COL_RED,
	COL_GREEN,
	COL_BROWN,
	COL_MAGENTA,
	COL_CYAN,
	COL_GREY,
	COL_ORANGE,
	COL_BGREEN,
	COL_YELLOW,
	COL_BLUE,
	COL_PINK,
	COL_WHITE,
	NUM_COLOURS
};


void display_init();
void display_end();

void display_refresh();
int display_getch();


void msg_printf(const char *, ...);
char *msg_getstr();
void msg_clear();

void main_plot(unsigned int, unsigned int, unsigned int, char);
void main_move(unsigned int, unsigned int);
void main_clear();

void stat_printf(const char *, ...);

void menu_printf(const char *, ...);
void menu_clear();
void menu_show();
void menu_hide();


#endif
