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
 * @file cjson_schema.cc
 * @brief JSON-Schema functionality - stub.
 */

#include "cjson_ex.hh"

class Subschema {
	Schema *m_schema;
	Subschema *m_parent;
};

class Schema {
	std::string id;
};

Schema *
create_schema(cJSON *schemacj)
{
}