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
 * @file idb.cc
 * @brief Debugger implementation.
 */

#include "idb.hh"
#include "idb_parse.hh"
#include "idb_parse.l.h"

void
Debugger::enter()
{
	parser = IDB_Parser::create();
	printf("Welcome to the InitKit Debugger.\n");
	printf("Type `exit` to leave the debugger.\n");
	while (read() == 0)
		;
	delete (parser);
}