# Copyright (c) DreamWorks Animation LLC
#
# All rights reserved. This software is distributed under the
# Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
#
# Redistributions of source code must retain the above copyright
# and license notice and the following restrictions and disclaimer.
#
# *     Neither the name of DreamWorks Animation nor the names of
# its contributors may be used to endorse or promote products derived
# from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# IN NO EVENT SHALL THE COPYRIGHT HOLDERS' AND CONTRIBUTORS' AGGREGATE
# LIABILITY FOR ALL CLAIMS REGARDLESS OF THEIR BASIS EXCEED US$250.00.
#
#[=======================================================================[.rst:

FindOpenVDB
-----------

Find OpenVDB include dirs, libraries and settings

Use this module by invoking find_package with the form::

  find_package(OpenVDB
    [version] [EXACT]      # Minimum or EXACT version
    [REQUIRED]             # Fail with error if OpenVDB is not found
    [COMPONENTS <libs>...] # OpenVDB libraries by their canonical name
                           # e.g. "openvdb" for "libopenvdb",
                           # "pyopenvdb" for the python plugin
                           # "openvdb_houdini" for the houdini plugin
    )

IMPORTED Targets
^^^^^^^^^^^^^^^^

``OpenVDB::openvdb``
  The core openvdb library target.
``OpenVDB::pyopenvdb``
  The openvdb python library target.
``OpenVDB::openvdb_houdini``
  The openvdb houdini library target.
``OpenVDB::openvdb_ax``
  The openvdb_ax library target.

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``OpenVDB_FOUND``
  True if the system has the OpenVDB library.
``OpenVDB_VERSION``
  The version of the OpenVDB library which was found.
``OpenVDB_INCLUDE_DIRS``
  Include directories needed to use OpenVDB.
``OpenVDB_LIBRARIES``
  Libraries needed to link to OpenVDB.
``OpenVDB_LIBRARY_DIRS``
  OpenVDB library directories.
``OpenVDB_DEFINITIONS``
  Definitions to use when compiling code that uses OpenVDB.
``OpenVDB_{COMPONENT}_FOUND``
  True if the system has the named OpenVDB component.
``OpenVDB_USES_BLOSC``
  True if the OpenVDB Library has been built with blosc support
``OpenVDB_USES_LOG4CPLUS``
  True if the OpenVDB Library has been built with log4cplus support
``OpenVDB_USES_EXR``
  True if the OpenVDB Library has been built with openexr support
``OpenVDB_ABI``
  Set if this module was able to determine the ABI number the located
  OpenVDB Library was built against. Unset otherwise.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``OpenVDB_INCLUDE_DIR``
  The directory containing ``openvdb/version.h``.
``OpenVDB_${COMPONENT}_INCLUDE_DIR``
  Individual component include directories for OpenVDB
``OpenVDB_{COMPONENT}_LIBRARY``
  Individual component libraries for OpenVDB

Hints
^^^^^

Instead of explicitly setting the cache variables, the following variables
may be provided to tell this module where to look.

``OPENVDB_ROOT``
  Preferred installation prefix.
``OPENVDB_INCLUDEDIR``
  Preferred include directory e.g. <prefix>/include
``OPENVDB_LIBRARYDIR``
  Preferred library directory e.g. <prefix>/lib
``OPENVDB_{COMPONENT}_ROOT``
  Preferred installation prefix of a specific component.
``OPENVDB_{COMPONENT}_INCLUDEDIR``
  Preferred include directory of a specific component e.g. <prefix>/include
``OPENVDB_{COMPONENT}_LIBRARYDIR``
  Preferred library directory of a specific component e.g. <prefix>/lib
``SYSTEM_LIBRARY_PATHS``
  Paths appended to all include and lib searches.

#]=======================================================================]

cmake_minimum_required(VERSION 3.3)
# Monitoring <PackageName>_ROOT variables
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

# Include utility functions for version information
include(${CMAKE_CURRENT_LIST_DIR}/OpenVDBUtils.cmake)

mark_as_advanced(
  OpenVDB_INCLUDE_DIR
  OpenVDB_LIBRARY
)

set(_OPENVDB_COMPONENT_LIST
  openvdb
  pyopenvdb
  openvdb_ax
  openvdb_houdini
)

if(OpenVDB_FIND_COMPONENTS)
  set(OPENVDB_COMPONENTS_PROVIDED TRUE)
  set(_IGNORED_COMPONENTS "")
  foreach(COMPONENT ${OpenVDB_FIND_COMPONENTS})
    if(NOT ${COMPONENT} IN_LIST _OPENVDB_COMPONENT_LIST)
      list(APPEND _IGNORED_COMPONENTS ${COMPONENT})
    endif()
  endforeach()

  if(_IGNORED_COMPONENTS)
    message(STATUS "Ignoring unknown components of OpenVDB:")
    foreach(COMPONENT ${_IGNORED_COMPONENTS})
      message(STATUS "  ${COMPONENT}")
    endforeach()
    list(REMOVE_ITEM OpenVDB_FIND_COMPONENTS ${_IGNORED_COMPONENTS})
  endif()
else()
  set(OPENVDB_COMPONENTS_PROVIDED FALSE)
  set(OpenVDB_FIND_COMPONENTS openvdb)
endif()

# always make sure openvdb is picked up as a component i.e.
# find_package(OpenVDB COMPONENTS pyopenvdb) results in both
# openvdb and pyopenvdb targets
if(NOT openvdb IN_LIST OpenVDB_FIND_COMPONENTS)
  list(APPEND OpenVDB_FIND_COMPONENTS openvdb)
endif()

# Append OPENVDB_ROOT or $ENV{OPENVDB_ROOT} if set (prioritize the direct cmake var)
set(_OPENVDB_ROOT_SEARCH_DIR "")

if(OPENVDB_ROOT)
  list(APPEND _OPENVDB_ROOT_SEARCH_DIR ${OPENVDB_ROOT})
else()
  set(_ENV_OPENVDB_ROOT $ENV{OPENVDB_ROOT})
  if(_ENV_OPENVDB_ROOT)
    list(APPEND _OPENVDB_ROOT_SEARCH_DIR ${_ENV_OPENVDB_ROOT})
  endif()
endif()

# Additionally try and use pkconfig to find OpenVDB

find_package(PkgConfig)
pkg_check_modules(PC_OpenVDB QUIET OpenVDB)

# This CMake module supports being called from external packages AND from
# within the OpenVDB repository for building openvdb components with the
# core library build disabled. Determine where we are being called from:
#
# (repo structure = <root>/cmake/FindOpenVDB.cmake)
# (inst structure = <root>/lib/cmake/OpenVDB/FindOpenVDB.cmake)

get_filename_component(_DIR_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

if(${_DIR_NAME} STREQUAL "cmake")
  # Called from root repo for openvdb components
elseif(${_DIR_NAME} STREQUAL "OpenVDB")
  # Set the install variable to track directories if this is being called from
  # an installed location and from another package. The expected installation
  # directory structure is:
  #  <root>/lib/cmake/OpenVDB/FindOpenVDB.cmake
  #  <root>/include
  #  <root>/bin
  get_filename_component(_IMPORT_PREFIX ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)
  get_filename_component(_IMPORT_PREFIX ${_IMPORT_PREFIX} DIRECTORY)
  get_filename_component(_IMPORT_PREFIX ${_IMPORT_PREFIX} DIRECTORY)
  set(_OPENVDB_INSTALL ${_IMPORT_PREFIX})
  list(APPEND _OPENVDB_ROOT_SEARCH_DIR ${_OPENVDB_INSTALL})
endif()

unset(_DIR_NAME)
unset(_IMPORT_PREFIX)

# ------------------------------------------------------------------------
#  Search for OpenVDB include DIR
# ------------------------------------------------------------------------

set(_OPENVDB_INCLUDE_SEARCH_DIRS "")
list(APPEND _OPENVDB_INCLUDE_SEARCH_DIRS
  ${OPENVDB_INCLUDEDIR}
  ${_OPENVDB_ROOT_SEARCH_DIR}
  ${PC_OpenVDB_INCLUDE_DIRS}
  ${SYSTEM_LIBRARY_PATHS}
)

foreach(COMPONENT ${OpenVDB_FIND_COMPONENTS})
  # Add in extra component paths
  set(_VDB_COMPONENT_SEARCH_DIRS ${_OPENVDB_INCLUDE_SEARCH_DIRS})
  list(APPEND _VDB_COMPONENT_SEARCH_DIRS
    ${OPENVDB_${COMPONENT}_ROOT}
    ${OPENVDB_${COMPONENT}_INCLUDEDIR}
  )
  # Look for a standard header files.
  if(${COMPONENT} STREQUAL "openvdb")
    find_path(OpenVDB_${COMPONENT}_INCLUDE_DIR openvdb/version.h
      NO_DEFAULT_PATH
      PATHS ${_VDB_COMPONENT_SEARCH_DIRS}
      PATH_SUFFIXES include
    )
  elseif(${COMPONENT} STREQUAL "pyopenvdb")
    find_path(OpenVDB_${COMPONENT}_INCLUDE_DIR pyopenvdb.h
      NO_DEFAULT_PATH
      PATHS ${_VDB_COMPONENT_SEARCH_DIRS}
      PATH_SUFFIXES include include/openvdb include/openvdb/python
    )
  elseif(${COMPONENT} STREQUAL "openvdb_houdini")
    # @note  Expects both houdini_utils and openvdb_houdini folders
    #   to be located in the same place
    find_path(OpenVDB_${COMPONENT}_INCLUDE_DIR openvdb_houdini/SOP_NodeVDB.h
      NO_DEFAULT_PATH
      PATHS ${_VDB_COMPONENT_SEARCH_DIRS}
      PATH_SUFFIXES include include/openvdb
    )
  elseif(${COMPONENT} STREQUAL "openvdb_ax")
    find_path(OpenVDB_${COMPONENT}_INCLUDE_DIR openvdb_ax/compiler/Compiler.h
      NO_DEFAULT_PATH
      PATHS ${_VDB_COMPONENT_SEARCH_DIRS}
      PATH_SUFFIXES include include/openvdb_ax
    )
  endif()
  unset(_VDB_COMPONENT_SEARCH_DIRS)
endforeach()

set(OpenVDB_INCLUDE_DIR ${OpenVDB_openvdb_INCLUDE_DIR}
  CACHE PATH "The OpenVDB core include directory")

OPENVDB_VERSION_FROM_HEADER("${OpenVDB_INCLUDE_DIR}/openvdb/version.h"
  VERSION OpenVDB_VERSION
  MAJOR   OpenVDB_MAJOR_VERSION
  MINOR   OpenVDB_MINOR_VERSION
  PATCH   OpenVDB_PATCH_VERSION
)

# ------------------------------------------------------------------------
#  Search for OPENVDB lib DIR
# ------------------------------------------------------------------------

set(_OPENVDB_LIBRARYDIR_SEARCH_DIRS "")

# Append to _OPENVDB_LIBRARYDIR_SEARCH_DIRS in priority order

list(APPEND _OPENVDB_LIBRARYDIR_SEARCH_DIRS
  ${OPENVDB_LIBRARYDIR}
  ${_OPENVDB_ROOT_SEARCH_DIR}
  ${PC_OpenVDB_LIBRARY_DIRS}
  ${SYSTEM_LIBRARY_PATHS}
)

# Build suffix directories

set(OPENVDB_PATH_SUFFIXES
  lib64
  lib
)

set(OPENVDB_PYTHON_PATH_SUFFIXES
  lib64/python
  lib64/python2.7
  lib64/python3
  lib/python
  lib/python2.7
  lib/python3
)

# Static library setup
if(UNIX AND OPENVDB_USE_STATIC_LIBS)
  set(_OPENVDB_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES})
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
endif()

set(OpenVDB_LIB_COMPONENTS "")

foreach(COMPONENT ${OpenVDB_FIND_COMPONENTS})
  set(LIB_NAME ${COMPONENT})

  # Add in extra component paths
  set(_VDB_COMPONENT_SEARCH_DIRS ${_OPENVDB_LIBRARYDIR_SEARCH_DIRS})
  list(APPEND _VDB_COMPONENT_SEARCH_DIRS
    ${OPENVDB_${COMPONENT}_ROOT}
    ${OPENVDB_${COMPONENT}_LIBRARYDIR}
  )

  if(${COMPONENT} STREQUAL "openvdb")
    find_library(OpenVDB_${COMPONENT}_LIBRARY ${LIB_NAME}
      NO_DEFAULT_PATH
      PATHS ${_VDB_COMPONENT_SEARCH_DIRS}
      PATH_SUFFIXES ${OPENVDB_PATH_SUFFIXES}
    )
  elseif(${COMPONENT} STREQUAL "pyopenvdb")
    set(_OPENVDB_ORIG_CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES})
    set(CMAKE_FIND_LIBRARY_PREFIXES ";lib")
    find_library(OpenVDB_${COMPONENT}_LIBRARY ${LIB_NAME}
      NO_DEFAULT_PATH
      PATHS ${_VDB_COMPONENT_SEARCH_DIRS}
      PATH_SUFFIXES ${OPENVDB_PYTHON_PATH_SUFFIXES}
    )
    set(CMAKE_FIND_LIBRARY_PREFIXES ${_OPENVDB_ORIG_CMAKE_FIND_LIBRARY_PREFIXES})
  elseif(${COMPONENT} STREQUAL "openvdb_houdini")
    find_library(OpenVDB_${COMPONENT}_LIBRARY ${LIB_NAME}
      NO_DEFAULT_PATH
      PATHS ${_VDB_COMPONENT_SEARCH_DIRS}
      PATH_SUFFIXES ${OPENVDB_PATH_SUFFIXES}
    )
  elseif(${COMPONENT} STREQUAL "openvdb_ax")
    find_library(OpenVDB_${COMPONENT}_LIBRARY ${LIB_NAME}
      NO_DEFAULT_PATH
      PATHS ${_VDB_COMPONENT_SEARCH_DIRS}
      PATH_SUFFIXES ${OPENVDB_PATH_SUFFIXES}
    )
  endif()

  list(APPEND OpenVDB_LIB_COMPONENTS ${OpenVDB_${COMPONENT}_LIBRARY})

  if(OpenVDB_${COMPONENT}_LIBRARY)
    set(OpenVDB_${COMPONENT}_FOUND TRUE)
  else()
    set(OpenVDB_${COMPONENT}_FOUND FALSE)
  endif()
  unset(_VDB_COMPONENT_SEARCH_DIRS)
endforeach()

if(UNIX AND OPENVDB_USE_STATIC_LIBS)
  set(CMAKE_FIND_LIBRARY_SUFFIXES ${_OPENVDB_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES})
  unset(_OPENVDB_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES)
endif()

# ------------------------------------------------------------------------
#  Cache and set OPENVDB_FOUND
# ------------------------------------------------------------------------

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OpenVDB
  FOUND_VAR OpenVDB_FOUND
  REQUIRED_VARS
    OpenVDB_INCLUDE_DIR
    OpenVDB_LIB_COMPONENTS
  VERSION_VAR OpenVDB_VERSION
  HANDLE_COMPONENTS
)

# ------------------------------------------------------------------------
#  Determine ABI number
# ------------------------------------------------------------------------

# Set the ABI number the library was built against. Uses vdb_print

if(_OPENVDB_INSTALL)
  OPENVDB_ABI_VERSION_FROM_PRINT(
    "${_OPENVDB_INSTALL}/bin/vdb_print"
    ABI OpenVDB_ABI
  )
else()
  # Try and find vdb_print from the include path
  OPENVDB_ABI_VERSION_FROM_PRINT(
    "${OpenVDB_INCLUDE_DIR}/../bin/vdb_print"
    ABI OpenVDB_ABI
  )
endif()

if(NOT OpenVDB_FIND_QUIET)
  if(NOT OpenVDB_ABI)
    message(WARNING "Unable to determine OpenVDB ABI version from OpenVDB "
      "installation. The library major version \"${OpenVDB_MAJOR_VERSION}\" "
      "will be inferred. If this is not correct, use "
      "add_definitions(-DOPENVDB_ABI_VERSION_NUMBER=N)"
    )
  else()
    message(STATUS "OpenVDB ABI Version: ${OpenVDB_ABI}")
  endif()
endif()

# ------------------------------------------------------------------------
#  Handle OpenVDB dependencies
# ------------------------------------------------------------------------

# Handle openvdb_houdini first to configure search paths

if(openvdb_houdini IN_LIST OpenVDB_FIND_COMPONENTS)
  include(OpenVDBHoudiniSetup)
endif()

# Add standard dependencies

find_package(IlmBase REQUIRED COMPONENTS Half)
find_package(TBB REQUIRED COMPONENTS tbb)
find_package(ZLIB REQUIRED)
find_package(Boost REQUIRED COMPONENTS iostreams system)

# Add deps for pyopenvdb
# @todo track for numpy

if(pyopenvdb IN_LIST OpenVDB_FIND_COMPONENTS)
  find_package(PythonInterp REQUIRED)
  find_package(PythonLibs REQUIRED)

  # Boost python handling - try and find both python and pythonXx (version suffixed).
  # Prioritize the version suffixed library, failing if neither exist.

  find_package(Boost ${MINIMUM_BOOST_VERSION}
    QUIET COMPONENTS python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}
  )

  if(TARGET Boost::python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR})
    set(BOOST_PYTHON_LIB "python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}")
    message(STATUS "Found boost_python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}")
  else()
    find_package(Boost ${MINIMUM_BOOST_VERSION}
      QUIET COMPONENTS python
    )
    if(TARGET Boost::python)
      set(BOOST_PYTHON_LIB "python")
      message(STATUS "Found non-suffixed boost_python, assuming to be python version "
        "\"${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}\" compatible"
      )
    else()
      message(FATAL_ERROR "Unable to find boost_python or "
        "boost_python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}."
      )
    endif()
  endif()
endif()

# Add deps for openvdb_ax

if(openvdb_ax IN_LIST OpenVDB_FIND_COMPONENTS)
  find_package(LLVM REQUIRED)
  if(NOT OpenVDB_FIND_QUIET)
    message(STATUS "Found LLVM: ${LLVM_DIR} (found version \"${LLVM_PACKAGE_VERSION}\")")
  endif()
  llvm_map_components_to_libnames(LLVM_LIBS all)
  find_package(Boost REQUIRED COMPONENTS random)
endif()

# Use GetPrerequisites to see which libraries this OpenVDB lib has linked to
# which we can query for optional deps. This basically runs ldd/otoll/objdump
# etc to track deps. We could use a vdb_config binary tools here to improve
# this process

include(GetPrerequisites)

set(_EXCLUDE_SYSTEM_PREREQUISITES 1)
set(_RECURSE_PREREQUISITES 0)
set(_OPENVDB_PREREQUISITE_LIST)

get_prerequisites(${OpenVDB_openvdb_LIBRARY}
  _OPENVDB_PREREQUISITE_LIST
  ${_EXCLUDE_SYSTEM_PREREQUISITES}
  ${_RECURSE_PREREQUISITES}
  ""
  "${SYSTEM_LIBRARY_PATHS}"
)

unset(_EXCLUDE_SYSTEM_PREREQUISITES)
unset(_RECURSE_PREREQUISITES)

# As the way we resolve optional libraries relies on library file names, use
# the configuration options from the main CMakeLists.txt to allow users
# to manually identify the requirements of OpenVDB builds if they know them.

set(OpenVDB_USES_BLOSC ${USE_BLOSC})
set(OpenVDB_USES_LOG4CPLUS ${USE_LOG4CPLUS})
set(OpenVDB_USES_EXR ${USE_EXR})

# Search for optional dependencies

foreach(PREREQUISITE ${_OPENVDB_PREREQUISITE_LIST})
  set(_HAS_DEP)
  get_filename_component(PREREQUISITE ${PREREQUISITE} NAME)

  string(FIND ${PREREQUISITE} "blosc" _HAS_DEP)
  if(NOT ${_HAS_DEP} EQUAL -1)
    set(OpenVDB_USES_BLOSC ON)
  endif()

  string(FIND ${PREREQUISITE} "log4cplus" _HAS_DEP)
  if(NOT ${_HAS_DEP} EQUAL -1)
    set(OpenVDB_USES_LOG4CPLUS ON)
  endif()

  string(FIND ${PREREQUISITE} "IlmImf" _HAS_DEP)
  if(NOT ${_HAS_DEP} EQUAL -1)
    set(OpenVDB_USES_EXR ON)
  endif()
endforeach()

unset(_OPENVDB_PREREQUISITE_LIST)
unset(_HAS_DEP)

if(OpenVDB_USES_BLOSC)
  find_package(Blosc REQUIRED)
endif()

if(OpenVDB_USES_LOG4CPLUS)
  find_package(Log4cplus REQUIRED)
endif()

if(OpenVDB_USES_EXR)
  find_package(IlmBase REQUIRED)
  find_package(OpenEXR REQUIRED)
endif()

if(UNIX)
  find_package(Threads REQUIRED)
endif()

# Set deps. Note that the order here is important. If we're building against
# Houdini 17.5 we must include OpenEXR and IlmBase deps first to ensure the
# users chosen namespaced headers are correctly prioritized. Otherwise other
# include paths from shared installs (including houdini) may pull in the wrong
# headers

set(_OPENVDB_VISIBLE_DEPENDENCIES
  Boost::iostreams
  Boost::system
  IlmBase::Half
)

set(_OPENVDB_DEFINITIONS)
if(OpenVDB_ABI)
  list(APPEND _OPENVDB_DEFINITIONS "-DOPENVDB_ABI_VERSION_NUMBER=${OpenVDB_ABI}")
endif()

if(OpenVDB_USES_EXR)
  list(APPEND _OPENVDB_VISIBLE_DEPENDENCIES
    IlmBase::IlmThread
    IlmBase::Iex
    IlmBase::Imath
    OpenEXR::IlmImf
  )
  list(APPEND _OPENVDB_DEFINITIONS "-DOPENVDB_TOOLS_RAYTRACER_USE_EXR")
endif()

if(OpenVDB_USES_LOG4CPLUS)
  list(APPEND _OPENVDB_VISIBLE_DEPENDENCIES Log4cplus::log4cplus)
  list(APPEND _OPENVDB_DEFINITIONS "-DOPENVDB_USE_LOG4CPLUS")
endif()

list(APPEND _OPENVDB_VISIBLE_DEPENDENCIES
  TBB::tbb
)
if(UNIX)
  list(APPEND _OPENVDB_VISIBLE_DEPENDENCIES
    Threads::Threads
  )
endif()

set(_OPENVDB_HIDDEN_DEPENDENCIES)

if(OpenVDB_USES_BLOSC)
  list(APPEND _OPENVDB_HIDDEN_DEPENDENCIES Blosc::blosc)
endif()

list(APPEND _OPENVDB_HIDDEN_DEPENDENCIES ZLIB::ZLIB)

# ------------------------------------------------------------------------
#  Configure imported targets
# ------------------------------------------------------------------------

set(OpenVDB_LIBRARIES
  ${OpenVDB_LIB_COMPONENTS}
)
set(OpenVDB_INCLUDE_DIRS ${OpenVDB_INCLUDE_DIR})

set(OpenVDB_DEFINITIONS)
list(APPEND OpenVDB_DEFINITIONS "${PC_OpenVDB_CFLAGS_OTHER}")
list(APPEND OpenVDB_DEFINITIONS "${_OPENVDB_DEFINITIONS}")
list(REMOVE_DUPLICATES OpenVDB_DEFINITIONS)

set(OpenVDB_LIBRARY_DIRS "")
foreach(LIB ${OpenVDB_LIB_COMPONENTS})
  get_filename_component(_OPENVDB_LIBDIR ${LIB} DIRECTORY)
  list(APPEND OpenVDB_LIBRARY_DIRS ${_OPENVDB_LIBDIR})
endforeach()
list(REMOVE_DUPLICATES OpenVDB_LIBRARY_DIRS)

# OpenVDB::openvdb

if(NOT TARGET OpenVDB::openvdb)
  add_library(OpenVDB::openvdb UNKNOWN IMPORTED)
  set_target_properties(OpenVDB::openvdb PROPERTIES
    IMPORTED_LOCATION "${OpenVDB_openvdb_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${OpenVDB_DEFINITIONS}"
    INTERFACE_INCLUDE_DIRECTORIES "${OpenVDB_INCLUDE_DIR}"
    IMPORTED_LINK_DEPENDENT_LIBRARIES "${_OPENVDB_HIDDEN_DEPENDENCIES}" # non visible deps
    INTERFACE_LINK_LIBRARIES "${_OPENVDB_VISIBLE_DEPENDENCIES}" # visible deps (headers)
    INTERFACE_COMPILE_FEATURES cxx_std_11
 )
endif()

# OpenVDB::pyopenvdb

if(OpenVDB_pyopenvdb_LIBRARY)
  if(NOT TARGET OpenVDB::pyopenvdb)
    add_library(OpenVDB::pyopenvdb UNKNOWN IMPORTED)
    set_target_properties(OpenVDB::pyopenvdb PROPERTIES
      IMPORTED_LOCATION "${OpenVDB_pyopenvdb_LIBRARY}"
      INTERFACE_INCLUDE_DIRECTORIES "${OpenVDB_pyopenvdb_INCLUDE_DIR};${PYTHON_INCLUDE_DIR}"
      INTERFACE_LINK_LIBRARIES "OpenVDB::openvdb;Boost::${BOOST_PYTHON_LIB};${PYTHON_LIBRARIES}"
      INTERFACE_COMPILE_FEATURES cxx_std_11
   )
  endif()
endif()

# OpenVDB::openvdb_houdini

if(OpenVDB_openvdb_houdini_LIBRARY)
  if(NOT TARGET OpenVDB::openvdb_houdini)
    add_library(OpenVDB::openvdb_houdini UNKNOWN IMPORTED)
    set_target_properties(OpenVDB::openvdb_houdini PROPERTIES
      IMPORTED_LOCATION "${OpenVDB_openvdb_houdini_LIBRARY}"
      INTERFACE_INCLUDE_DIRECTORIES "${OpenVDB_openvdb_houdini_INCLUDE_DIR}"
      INTERFACE_LINK_LIBRARIES "OpenVDB::openvdb;Houdini"
      INTERFACE_COMPILE_FEATURES cxx_std_11
   )
  endif()
endif()

# OpenVDB::openvdb_ax

if(OpenVDB_openvdb_ax_LIBRARY)
  if(NOT TARGET OpenVDB::openvdb_ax)
    add_library(OpenVDB::openvdb_ax UNKNOWN IMPORTED)
    set_target_properties(OpenVDB::openvdb_ax PROPERTIES
      IMPORTED_LOCATION "${OpenVDB_openvdb_ax_LIBRARY}"
      INTERFACE_INCLUDE_DIRECTORIES "${OpenVDB_openvdb_ax_INCLUDE_DIR}"
      INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${LLVM_INCLUDE_DIRS}"
      INTERFACE_LINK_LIBRARIES "OpenVDB::openvdb;Boost::random;${LLVM_LIBS}"
      INTERFACE_COMPILE_FEATURES cxx_std_11
   )
  endif()
endif()

unset(_OPENVDB_DEFINITIONS)
unset(_OPENVDB_VISIBLE_DEPENDENCIES)
unset(_OPENVDB_HIDDEN_DEPENDENCIES)