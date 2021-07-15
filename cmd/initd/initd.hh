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
 * @brief InitKit Scheduler Service global state.
 */

#ifndef INITD_HH_
#define INITD_HH_

#include "ev.h"
#include "idb.hh"
#include "jsm.hh"
#include "dlm.hh"

class Initd {
	struct ev_loop *evloop;
	Debugger idb;
	JSM jsm;
	DLM dlm;

	/* Set up signal handling. */
	void init_signals();

	static void signal_cb(struct ev_loop *evloop, ev_signal *watch,
			      int revents);

    public:
	/* Low-level initialisation of the Scheduler Service. */
	void init();
	/* Main loop. */
	void loop();
};

extern Initd initd;

#endif
