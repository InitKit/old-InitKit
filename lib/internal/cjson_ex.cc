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
 * @file cjson_ex.cc
 * @brief Extra functionality for cJSON.
 */

#include <stdio.h>
#include <stdlib.h>

#include "cjson_ex.hh"
#include "cxxutil.hh"

int
parse_json_file(const char *path, cJSON *&obj)
{
	long len = 0;
	Auto<char *, FreeLikeDeleter, free> data;
	FileStar f;

	f = fopen(path, "rb");
	if (!f)
		return -errno;
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);

	printf("Data: %p\n", data.operator char *());
	data = (char *)malloc(len + 1);
	if (!data)
		return -ENOMEM;

	fread(data, 1, len, f);
	data[len] = '\0';
	f.release();

	obj = cJSON_Parse(data);
	if (!obj)
		return -EINVAL;
	return 0;
}