/*
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * 		PROPRIETARY NOTICE:
 *
 * The software contained on this media is unpublished proprietary information
 * constituting or derived under licence from NetaScale Advanced Executive (tm),
 * a product of NetaScale Systems, Ltd.
 *
 * 		Copyright Notice:
 *
 * Notice of copyright on this source code product does not indicate
 * publication.
 *
 * 	(c) 2008-2021 NetaScale Systems, Ltd.
 * 		All rights reserved.
 */
/**
 * @file idb_readline.cc
 * @brief EditLine-based command prompt for the InitKit Debugger.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <editline/readline.h>

#include "idb.hh"
#include "initd.hh"

int
Debugger::read()
{
	char *buf;
	while ((buf = readline(">> ")) != NULL) {
		if (!buf || strlen(buf) == 0)
			continue;
		else if (strcmp(buf, "exit") == 0)
			return 1;
		else if (strcmp(buf, "terminate") == 0)
			exit(EXIT_FAILURE);
		else if (strcmp(buf, "reloaddbs") == 0)
			initd.dlm.reloaddbstab();
		else if (strlen(buf) > 0)
			add_history(buf);

		parser->parse(buf);

		free(buf);
	}
	return 0;
}