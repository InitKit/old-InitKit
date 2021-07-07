project(InitKit)
cmake_minimum_required(VERSION 3.9)
cmake_policy(VERSION 3.9)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

set(PACKAGE_NAME InitKit)
set(PACKAGE_VERSION 1.0-alpha)
set(PACKAGE_STRING "${PACKAGE_NAME} version ${PACKAGE_VERSION}")

set(DISTRIBUTION ${CMAKE_SYSTEM})

include(FindPkgConfig)
include(GNUInstallDirs)
include(CMakeDependentOption)
include(CMakePushCheckState)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)
include(LemFlex)

list(APPEND CMAKE_REQUIRED_DEFINITIONS "-D_GNU_SOURCE -D__BSD_VISIBLE")

macro(check_type_size_in type headers var)
  cmake_push_check_state()
  list(APPEND CMAKE_REQUIRED_DEFINITIONS "-D_GNU_SOURCE -D__BSD_VISIBLE")
  set(CMAKE_EXTRA_INCLUDE_FILES ${headers})
  check_type_size(${type} ${var})
  cmake_push_check_state(RESET)
endmacro()

# If ${var} is set to anything, set ${var2} to true
macro(set_to_true var var2)
  if(${var})
    message("${var} is true")
    set(${var2} TRUE)
  endif()
endmacro()

#-------------------------------------------------------------------------------
# default features
#-------------------------------------------------------------------------------

set(DEFAULT_RUNSTATE_DIR "/var/run")

if(CMAKE_SYSTEM_NAME MATCHES ".*Linux")
  set(PLATFORM_Linux TRUE)
  set(DEFAULT_USE_CGroups ON)
  set(DEFAULT_RUNSTATE_DIR "/run")
  add_definitions("-D_GNU_SOURCE")
elseif(CMAKE_SYSTEM_NAME MATCHES "kFreeBSD.*|FreeBSD")
  set(PLATFORM_BSD TRUE)
  set(PLATFORM_FreeBSD TRUE)
elseif(CMAKE_SYSTEM_NAME MATCHES "kNetBSD.*|NetBSD.*")
  set(PLATFORM_BSD TRUE)
  set(PLATFORM_NetBSD TRUE)
elseif(CMAKE_SYSTEM_NAME MATCHES "kOpenBSD.*|OpenBSD.*")
  set(PLATFORM_BSD TRUE)
  set(PLATFORM_OpenBSD TRUE)
elseif(CMAKE_SYSTEM_NAME MATCHES "DragonFly.*")
  set(PLATFORM_BSD TRUE)
  set(PLATFORM_DragonFlyBSD TRUE)
elseif(CMAKE_SYSTEM_NAME MATCHES "HP-UX")
  set(PLATFORM_HPUX TRUE)
  # make _r functions available
  add_definitions(-D_REENTRANT=1)
elseif(APPLE)
  set(PLATFORM_BSD TRUE)
endif()

if(PLATFORM_BSD)
  set(DEFAULT_USE_KQueue YES)
else()
  set(DEFAULT_USE_KQueue NO)
endif()

#
# compiler settings
#

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  string(APPEND CMAKE_CXX_FLAGS "-Wno-c++17-compat-mangling")
endif()


#-------------------------------------------------------------------------------
# checks
#-------------------------------------------------------------------------------

find_package(Threads REQUIRED)
pkg_check_modules(EditLine IMPORTED_TARGET libedit)

if(EditLine_FOUND)
  set(DEFAULT_USE_EditLine true)
endif()

check_include_file(asm/types.h HAVE_asm_types_h)

check_type_size_in("struct cmsgcred" "sys/socket.h" HAVE_struct_cmsgcred)
check_type_size_in("struct ucred" "sys/socket.h"
  HAVE_struct_ucred_in_sys_socket_h)

check_symbol_exists(waitid "sys/wait.h" HAVE_waitid)

#-------------------------------------------------------------------------------
# host programs
#-------------------------------------------------------------------------------

find_program(Mandoc mandoc)

if(Mandoc)
  set(DEFAULT_USE_Docs TRUE)
endif()

#-------------------------------------------------------------------------------
# actual building commands
#-------------------------------------------------------------------------------

add_library(initkit INTERFACE)
target_include_directories(initkit INTERFACE
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/common>
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/head>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/head>)

configure_file(head/InitKit/ik_config.h.in head/InitKit/ik_config.h)

add_subdirectory(vendor/cJSON)
add_subdirectory(vendor/lemon)
add_subdirectory(vendor/tvision)
add_subdirectory(vendor/libev-ik)
add_subdirectory(lib/internal)
add_subdirectory(cmd/initd)
add_subdirectory(cmd/initadm)

#-------------------------------------------------------------------------------
# display enabled options
#-------------------------------------------------------------------------------

function(FShow pref flag defval descr)
    list(APPEND options ${flag})
    option(${flag} ${descr} ${${defval}})

    if(${flag})
        message("${pref}  ${descr}: ${${flag}}")
    else()
        message("${pref}  ${descr}: OFF")
    endif()
endfunction(FShow)

FShow("" RUNSTATE_DIR "${DEFAULT_RUNSTATE_DIR}"
  "System runtime state directory) (E.g. /var/run)")

message("Feature settings (Use flags):")
FShow("" USE_Docs DEFAULT_USE_Docs "Build documentation")

message("  Advanced process tracking:")
FShow("    ->" USE_CGroups
  DEFAULT_USE_CGroups "GNU/Linux Control Groups")
FShow("    ->" USE_KQueue
  DEFAULT_USE_KQueue "Kernel Queues")


foreach(option options)
  if(${option})
    list(APPEND M4_Defs "-D${option}=${${option}}")
  endif()
endforeach()
