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
 * @file dbs.hh
 * @brief Description Loading Module
 */

#ifndef DLM_HH_
#define DLM_HH_

#include <memory>
#include <string>
#include <vector>

class DBSEntry {
	std::string name;

	/**
      * The command to execute. May include variables for expansion. Variables
      * permitted: $entryname
      */
	std::string command;

	std::string description;

	/**
      * Entry priority. If INT_MIN, the entry was deleted from the dbstab and is
      * no longer in the switch, but remains allocated as it has a reference
      * count greater than 1.
      */
	int m_priority;

    public:
	/* True is entry name matches string. */
	bool operator==(const char *&str)
	{
		return name == str;
	}
};

class DLM {
	typedef std::vector<std::shared_ptr<DBSEntry> > DBSEntVec;

	std::vector<std::shared_ptr<DBSEntry> > m_dbsentries;
	const char *m_dbstabpath;

    public:
	/**
     * Initialise the DLM: load the dbstab.
     */
	int init(const char *dbstabpath);

	/**
     * Reload the dbstab.
     */
	int reloaddbstab();
};

#endif /* DLM_HH_ */
