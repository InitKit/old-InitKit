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
 * @file idb.h
 * @brief InitKit Debugger definitions.
 */

#ifndef IDB_HH_
#define IDB_HH_

#include "idb_parse.hh"

class Debugger {
	IDB_Parser *parser;
	/* Read in one command. Return 1 if exit requested.*/
	int read();

    public:
	void enter();
};

#endif /* IDB_HH_ */
