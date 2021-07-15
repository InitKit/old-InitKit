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
 * @file cstr.hh
 * @brief C String wrapper class - avoids dynamic allocation.
 */

#ifndef CSTR_HH_
#define CSTR_HH_

class CStr {
    char * str;
    bool m_dynamic; /* is it heap-allocated? */
};

#endif /* CSTR_HH_ */
