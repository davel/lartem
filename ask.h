#ifndef ASK_H
#define ASK_H

struct option {
	char letter;
	const char *text;
};

int ask_opt(const char *, struct option *);
char *ask_str(const char *);

#endif
