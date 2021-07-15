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
 * @brief Entry point for the InitKit Scheduler Service
 */

#include <sys/signal.h>

#include <cassert>
#include <err.h>

#include "InitKit/ik_config.h"
#include "ev.h"
#include "idb_parse.hh"
#include "initd.hh"
#include "macros.h"

Initd initd;

#pragma region Callbacks

void
Initd::signal_cb(struct ev_loop *evloop, ev_signal *watch, int revents)
{
	if (watch->signum == SIGINT)
		initd.idb.enter();
}

#pragma endregion

#pragma region Initialisation

void
Initd::init_signals()
{
	sigset_t mask;
	struct sigaction sa_chld = {
		{ SIG_DFL },
		SA_NOCLDSTOP | SA_RESTART,
	};
	int signals[] = {
		SIGCHLD,
		SIGINT,
	};
	static ev_signal ev_signals[255] = {};

	/* Disable delivery of SIGCHLD for a stopped child. */
	assert(sigaction(SIGCHLD, &sa_chld, NULL) == 0);
	assert(sigemptyset(&mask) == 0);

	for (int i = 0; i < NELEMENTS(signals); i++) {
		ev_signal_init(&ev_signals[i], signal_cb, signals[i]);
		assert(sigaddset(&mask, signals[i]) == 0);
		ev_signal_start(evloop, &ev_signals[i]);
	}
}

void
Initd::init()
{
	int e;
	evloop = ev_default_loop(EVFLAG_NOSIGMASK);
	if (!evloop)
		err(EXIT_FAILURE, "Failed to create event loop");
	init_signals();
	e = dlm.init(IK_PKG_SYSCONFDIR "/system/dbstab");
	if (e < 0)
		err(EXIT_FAILURE, "Failed to load dbstab");
}

#pragma endregion

void Initd::loop()
{
	ev_run(evloop, 0);

}

int
main()
{
	initd.init();
	initd.loop();
}