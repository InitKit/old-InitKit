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

#include <algorithm>

#include "cJSON.h"
#include "cjson_ex.hh"
#include "dlm.hh"

template <typename CompareTo, typename T2> struct IsEqual {
	IsEqual(CompareTo &s) : m_s(s)
	{
	}

	bool operator()(std::shared_ptr<T2> &rhs)
	{
		return (*rhs) == m_s;
	}

	CompareTo &m_s;
};

int
DLM::init(const char *dbstabpath)
{
	m_dbstabpath = dbstabpath;
	return reloaddbstab();
}

int
DLM::reloaddbstab()
{
	cJSON *dbstabjson, *dbsentjson;
	int r;
	DBSEntVec newdbs;

	r = parse_json_file(m_dbstabpath, dbstabjson);
	if (r < 0)
		return r;

	//olddbs = std::move(m_dbsentries);
	//m_dbsentries.clear();

	for (dbsentjson = dbstabjson->child; dbsentjson;
	     dbsentjson = dbsentjson->next) {
		const char *name;
		cJSON *cmdjson, *descjson, *prijson;
		DBSEntVec::iterator it;

		name = dbsentjson->string;
		cmdjson =
			cJSON_GetObjectItemCaseSensitive(dbsentjson, "command");
		descjson = cJSON_GetObjectItemCaseSensitive(dbsentjson,
							    "description");
		prijson = cJSON_GetObjectItemCaseSensitive(dbsentjson,
							   "priority");

		if (!cJSON_IsString(cmdjson) || !cJSON_IsNumber(prijson))
			fprintf(stderr,
				"dbstab entry %s has missing or invalid"
				"command or priority property\n",
				name);

		it = std::find_if(m_dbsentries.begin(), m_dbsentries.end(),
				  IsEqual<const char *, DBSEntry>(name));

		if (it != m_dbsentries.end() &&
		    (*it)->m_priority == prijson->valueint &&
		    (*it)->command == cmdjson->valuestring)
			/* existing entry with same properties; retain */;
		else {
			/* no entry exists with same properties; create new. */
			std::shared_ptr<DBSEntry> newent =
				std::make_shared<DBSEntry>();
			newent->name = name;
			newent->command = cmdjson->valuestring;
			if (cJSON_IsString(descjson))
				newent->description = descjson->valuestring;
			newent->m_priority = prijson->valueint;
			newdbs.emplace_back(std::move(newent));
		}
	}

	m_dbsentries.clear();
	m_dbsentries = std::move(newdbs);

	return r;
}