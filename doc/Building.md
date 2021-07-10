Building InitKit
================

InitKit uses the industry-standard combination of the  [CMake] build automation
framework with the [GIT] source code management suite. These products make
building and contributing to InitKit a straightforward experience.

There are three steps to building and installing InitKit from source: installing
dependencies, checking out the source tree and its submodules, running CMake,
then running Make to install it.

[CMake]: https://cmake.org
[GIT]: https://git-scm.com

Dependencies
------------

Installing dependencies is a different process on each platform. The required
software and libraries are:

 - GIT;
 - CMake;
 - Make, or at your preference Ninja;
 - ISO-standard C and C++ compilers, compliant with the C99 and C++0x standards,
 e.g. HP C/aC++ A0.06.25; IBM XLC++ 13.1; Apple LLVM/Clang 3.0; GNU Compiler
 Collection 4.8;
 - The Fast Lexical Analyser FLEX.
 - NetBSD EditLine (or GNU ReadLine; only the ReadLine interface is consumed).

For example, to install dependencies on FreeBSD:

`# pkg install git cmake flex libedit`

On Open SuSE Linux (Leap 15.3):

```# zypper in -t pattern devel_C_C++
# zypper in cmake git flex libedit libedit-devel
```

Source tree checkout
--------------------

Checking out the source code is straightforward:

```$ git checkout https://github.com/InitKit/InitKit.git
$ cd InitKit
$ git submodule update --init --recursive
```

To update an already checked-out source tree, run in the source tree directory:

```$ git pull
$ git submodule update --recursive
```

Invoking CMake
--------------

First, create a `build` subdirectory, and `$ cd build` into that folder. Run
`$ cmake ..` to instruct CMake to prepare Makefiles, then run `$ make` to build
InitKit and its dependencies.

Installation
------------

Run `# make install` to install InitKit.