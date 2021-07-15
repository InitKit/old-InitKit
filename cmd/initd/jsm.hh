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
 * @file jsm.h
 * @brief Job Scheduling Module (JSM) definitions
 * 
 * The Job Scheduling Module is a fairly self-contained module. These are the
 * interfaces to the module:
 * 
 * - Admission of SchedulerEntities.
 * - Notification of service state changes.
 * - Administrative requests (including requests to describe how a hypothetical
 *   request would alter the state of all services; i.e. to 'dry-run' a
 *   transaction; and complex requests, e.g. the replacement of a virtual
 *   service's provider.)
 *
 * These are its outputs:
 *
 * - Service control commands, i.e. start and stop.
 * - Transaction and other status updates.
 *
 * The Job Scheduling Module is an event-based system with a transactional
 * impurity, designed after the order of the X Desktop Group's systemd. As it
 * handles a similar set of dependency modes as does systemd, it is quite
 * complicated. This is why it is designed to be highly self-contained and
 * modular. For example, consider how the Scheduler class sends output commands
 * and updates to a SchedulerDelegate object.
 *
 * A characteristic of this design is that the JSM can duplicate its object
 * graph (encapsulated within the Scheduler object) and then test how service
 * states would change as a result of one or more administrative requests, or as
 * a result of unscheduled failures. A mock SchedulerDelegate simply immediately
 * responds to requests, e.g. on receiving a 'Start X' requests, notifies the
 * Scheduler 'X went up'. This makes testing straightforward, and makes trivial
 * implementing a 'dry run' functionality to let the administrator see how an
 * administrative request would change service states.
 */

#ifndef JSM_HH_
#define JSM_HH_

#include <list>
#include <memory>

/**
 * A SchedulerEntity is an object within the dependency graph.
 */
class SchedulerEntity {
};

class Job {
};

class Transaction {
};

class SchedulerDelegate {
};

class Scheduler {
	SchedulerDelegate *delegate;
	std::list<std::unique_ptr<SchedulerEntity> > entities;

    public:
};

class JSM : public SchedulerDelegate {
	Scheduler * sched;
	public:
};

#endif
