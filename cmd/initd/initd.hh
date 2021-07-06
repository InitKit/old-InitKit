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
 * @file initd.h
 * @brief InitKit Control Daemon global state.
 */

#ifndef INITD_HH_
#define INITD_HH_

#include "jss.hh"
#include "ev.h"

class Initd {
    struct ev_loop * evloop = EV_DEFAULT;

    public:
};

extern Initd initd;

#endif
