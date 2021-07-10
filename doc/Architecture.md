InitKit Architecture
====================

InitKit is a modular system designed according to the principles of the Unix
Way. Its design owes much to the X Desktop Group's *SystemD* service manager,
as well as the Solaris *SMF*, the Apple *LaunchD*, the AIX *SRC*, and the 
Enumerated in this page are some of the components of the system.

*System Entities* (SEs), *Supervisors*, and the *SEOM*
-----------------------------------------------------

A System Entity is some resource whose status may be tracked or polled, and
which may in addition be manipulable by requests to be started and stopped. The
SEOM is the model of objects and their interfaces to which SEs are
abstracted; we conceptualise the Ein general as an interface,
particular kinds of entities as classes, while the entities themselves are
instances of particular subclasses.

SEs are named by URIs. For example, a local Process resource may be named
`process:/rpcbind`. A concept of *parametric SEs* exists also; these are not SEs
themselves, but are templates which may be *instantiated* by referencing them;
the instance name is denoted by an `@` symbol followed by an *instance name* at
the end of the SE URI, e.g. `process:/console-login@ttyv1`.

An SE class is implemented by a Supervisor. The Supervisor must
provide status updates on the resources it deals with. The particular strategy
of how it tracks the status of these resources is up to the Supervisor. As soon
as a state change occurs, the Supervisor must inform the JSM.

A Supervisor should also respond to *start* and *stop* requests. These should
try to either make available or make go away a particular SE. It is not
necessary that the Supervisor actually do anything with this; e.g. for a device
supervisor, this would be clearly impossible to achieve. 

*System Entity Descriptions* (SEDs)
-----------------------------------

These are descriptions, either complete or fragmentary, of a System Entity. The
native format is JSON, but other formats may be implemented by appropriate
binaries. Any description or fragment must bear a *name* (i.e. an SE URI);
descriptions are composed together according to the rules of the *Description
Backing-store Switch* (see below).

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

The JSM also maintains some other core components of the InitKit system:

### The *System Entity Descriptions Cache* (SEDC)

A cache of System Entity Descriptions; descriptions of all the properties of a
particular SE.

### The *Class Provider Switch* (CPS)

The table of System Entity classes handled by a particular instance of InitKit.
A CPS entry includes instructions on how to launch a particular SE's supervisor;
generally, this is the name of a *Process* SE. Entries may also include schemata
for additional properties.

### The *Description Backing-store Switch* (DBS)

This is the table of backing-stores used to source (fragmentary or whole) System
Entity Descriptions. Entries take the form of a path to a binary (which is run
and passed an IPC channel to the JSM) and potential command-line arguments to
add to the invocation of that binary. Entries are ranked in priority;
lower-priority entries' properties are superseded by those of higher-priority
entries.

A special set of entries at the lowest priority are added for each SEOM Provider
Switch entry; these specify that an SE Class' Supervisor is itself a backing
store, and they have no command but instead instead instruct the JSM to ask the
Supervisor to enumerate any entries it can describe. This is of particular
import in the case of the Device SE class, for example.

At present, the JSM will synchronously wait on each DBS entries' command to
complete execution, by which point it is expected that the command has sent
along the IPC channel all the descriptions it has found within this backing
store.

The *Process Supervision Module* (PSM)
--------------------------------------

This component is responsible for launching and supervising processes. It is a
special kind of *Supervisor* which provides an extended interface (including the
ability to e.g. start a process with a set of file descriptors handed over to
it.)

The `Process`, `External Process`, and `Processes Group` System Entity classes
are implemented by the PSM.

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