![InitKit logo](doc/Logo.png)

*NetaScale Systems Ltd.*'s  **InitKit** is the standard Unix initialisation
system. It manages not only traditional process-based services but also anything
that may be described using the *SEOM* - the System Entities Object Model, a
flexible object-oriented abstraction of a system resource.

The core of the system is made up of the *Job Scheduling Module* and the
*Process Supervision Module*. The former is an enterprise-grade job scheduler
based on a parallelising graph-based transactional dependency system, and the
latter is a powerful and plugin-extendable process launch and control system,
which uses the most advanced features available on each platform to provide
sophisticated process supervision functionality.

By way of an update path for the [X Desktop Group](http://freedesktop.org)
*SystemD* service manager, a SystemD unit-file converter is provided.

InitKit is still under development. Anyone who wishes to contribute to the
project is invited to join, and anyone is welcome to inquire about how their
company may prepare to switch to InitKit.

The Unix Way In Action
----------------------

The design of InitKit owes much to the traditional design philosophy of the Unix
community the *Unix Way*. InitKit operationalises that philosophy in the
following ways:

- *The Modularity Principle*: InitKit is designed with a simple core of two
  daemons providing basic features.
- *The Polymorphism Principle*: The System Entities Object Model abstracts the
  concept of a system resource. New SEOM classes can describe how to manage or
  track any resource.
- *The Composition Principle*: The core daemons may be composed with other
  daemons that add new SEOM classes which they may track.
- *The Simplicity Principle*: InitKit's core daemons are designed to be
  fundamentally simple, so that enough of their functionality to run a system
  should be reimplementable without excessive bother.
- *The Extensibility Principle*: InitKit is designed without the arrogance of
  the man who says "I have envisaged all usecases." Its foundation on the SEOM
  is a clear commitment to customisation and extension.

Licencing
---------

InitKit is available as free, open-source software under the terms of the Affero
General Public Licence version 3.0. See [LICENSE.MD](LICENSE.MD) for full terms.

Documentation
-------------

 - [Architecture]: A must-read page. The design of the InitKit system explained.
 - [Building]: How to build and install InitKit from source.

[Architecture]: doc/Architecture.md
[Building]: doc/Building.md
