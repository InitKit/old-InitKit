InitKit Architecture
====================

InitKit is a modular system designed according to the principles of the Unix
Way. Its design owes much to the X Desktop Group's *SystemD* service manager,
as well as the Solaris *SMF*, the Apple *LaunchD*, the AIX *SRC*, and the 
Enumerated in this page are some of the components of the system.

*System Entities* and the SEOM
----------------------------

A System Entity is some resource whose status may be tracked or polled, and
which may in addition be manipulable by requests to be started and stopped. The
SEOM is the model of objects and their interfaces to which System Entities are
abstracted; we conceptualise the System Entity in general as an interface,
particular kinds of entities as classes, while the entities themselves are
instances of particular subclasses.

The *Job Scheduling Module* (JSM)
---------------------------------

This is the heart of the InitKit system. The key concepts of the JSM are three,
called the *Holy Trinity of InitKit* because of their centrality to
understanding the system:

- Scheduler Entities: Descriptions of objects within the System Entities Object
  Model, including specifications of interrelations, called dependencies, to
  other objects;
- Jobs: Requests generated for the control of the objects underlying Scheduler
  Entities;
- and Transactions, plans on how to effect changes to the state of a Scheduler
  Entity, made up of collections of Jobs with ordering and requirement
  relationships between them as appropriate for their associated Scheduler
  Entity's dependencies.

The Job Scheduling Module utilises the *SEOM Provider Switch* (SPS).
The SPS generates appropriate commands to manipulate underlying System Entities
according to whether the entity has been asked to be brought up or down.

The *Process Supervision Module* (PSM)
--------------------------------------

This component is responsible for launching and supervising processes. It
implements the `Process`, `External Process`, and `Processes Group` System
Entity classes.

### Process

The most frequently found kind of System Entity, it denotes a resource whose
availability is a function of processes; e.g. the resource is deemed up when a
particular process is running, or when a particular process runs and exits. A
Process is always started directly by the PSM.

### External Process

These are similar to Processes, but are started externally, not by the PSM. They
are regarded as offline as soon as they exit.

### Processes Group

These form a tree, and contain Processes and External Processes. They describe
parameters like resource limitations. Specific features are generally
quite platform-specific as these are implemented differently on different
platforms (e.g. they are implemented in terms of CGroups on GNU/Linux).