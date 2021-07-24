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
 * @file cjson_ex.h
 * @brief Extra functionality for cJSON.
 */

#ifndef CJSON_EX_HH_
#define CJSON_EX_HH_

#include <iostream>
#include <string>

#include "cJSON.h"

#pragma region JSON - Schema validation.

/** Internal representation of a JSON schema, created from a cJSON object. */
class Schema;

/**
 * Create a \c Schema from a cJSON object.
 */
Schema *create_schema(cJSON *schemacj);

#pragma endregion

#pragma region Miscellaneous convenience functions

/**
 * Try to parse a JSON file into a cJSON object.
 * 
 * @returns 0 on success, and sets \p obj to the parsed JSON object
 * @returns -EINVAL if the file is not good JSON
 * @returns -ENOMEM if there is an out-of-memory condition
 * @returns -errno for any other file reading error
 */
int parse_json_file(const char *path, cJSON *&objjc);

#pragma endregion

#endif /* CJSON_EX_HH_ */
