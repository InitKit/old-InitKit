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
 * @file filename.h
 * @brief A brief description of the file's purpose.
 *
 * A lengthier description of the general purpose of the file, any subtleties to
 * which the programmer's attention ought to be drawn, etc.
 */

#include "idb_parse.hh"
#include "initd.hh"

initd_t initd;

int
main()
{
	idb_parser_t *parser = idb_parser_t::create();
	parser->parse("Hello World IMPORT\n");
}