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
 * @file dlm.cc
 * @brief Description Loading Module
 */

#include "cJSON.h"
#include "cjson_ex.hh"
#include "dlm.hh"

int
DLM::init(const char *dbstabpath)
{
	m_dbstabpath = dbstabpath;
	return reloaddbstab();
}

int
DLM::reloaddbstab()
{
	cJSON *dbsjson, *dbsentjson;
	int r;

	r = parse_json_file(m_dbstabpath, dbsjson);
	if (r < 0)
		return r;

	dbsentjson = dbsjson->child;
	while (dbsentjson) {
		dbsentjson = dbsentjson->next;
	}

	return r;
}