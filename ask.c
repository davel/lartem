#include <stdlib.h>
#include <strings.h>

#include "ask.h"
#include "display.h"


int ask_opt(const char *question, struct option options[])
{
	int letters[26], i, j, k;

	for(i = 0; i < 26; i++) letters[i] = -1;

	menu_clear();

	menu_printf("%s\n\n", question);

	for(j = 0; options[j].text; j++) {
		if(!options[j].letter) {
			for(i = 0; i < 26 && letters[i] != -1; i++);
			if(i == 26) {
				/* TODO: error handling */

				exit(1);
			}

			letters[i] = j;
			options[j].letter = i + 97;
		}

		menu_printf("%c) %s\n", options[j].letter, options[j].text);
	}

	menu_show();

	do {
		k = display_getch();

		if(k == 32) k = -1;
		else if(k >= 65 && k <= 90) k = letters[k - 65];
		else if(k >= 97 && k <= 122) k = letters[k - 97];
		else k = -2;

	} while(k == -2);

	menu_hide();

	return k;
}



char *ask_str(const char *question, const char *def)
{
	char *str;

	msg_printf("%s [%s]", question, def);
	str = msg_getstr();
	msg_clear();

	if (strlen(str)==0) {
		free(str);
		return strdup(def);
	}

	return str;
}
