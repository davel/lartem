#include <stdlib.h>

#include "role.h"

#include "ask.h"


const struct role roles[] = {
	{ "Sysadmin",
	  {
		"MCSA",
		"",
		"",
		"",
		"",
		"BOFH",
		"VAXorcist",
		"UNIX Guru"
	  }
	},

	{ "Programmer",
	  {
		  "VB Coder",
		  "Computer Science Graduate",
		  "Real Programmer",
		  "Fledgling hacker",
		  "",
		  "",
		  "Regexp Ninja",
		  "Red Eye Knight"
	  }
	}
};



int ask_role()
{
	struct option role_opts[NUM_ROLES + 1];
	unsigned int i;

	for(i = 0; i < NUM_ROLES; i++) {
		role_opts[i].letter = 0;
		role_opts[i].text = roles[i].name;
	}

	role_opts[NUM_ROLES].text = NULL;

	return ask_opt("Pick a role", role_opts);
}



const char *get_rank(unsigned int role, unsigned int rank)
{
	if(role >= NUM_ROLES || rank > 7) return "";

	return roles[role].rank[rank];
}
