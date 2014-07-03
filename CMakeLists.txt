# Copyright (c) Monetas AG, 2014

cmake_minimum_required(VERSION 2.8)
project(OPENTXS_AUDITOR)

set(VERSION_MAJOR  0)
set(VERSION_MINOR  0)
set(VERSION_BUGFIX 1)
set(VERSION "0.0.1")

#-----------------------------------------------------------------------------
# Options for building

option(OPENTXS_AUDITOR_BUILD_VERBOSE       "Verbose build output." ON)
option(OPENTXS_AUDITOR_BUILD_TESTS         "Build the unit tests." ON)
option(RPM                                 "Build a RPM" OFF)
option(DEB                                 "Build a DEB" OFF)

if(OPENTXS_AUDITOR_BUILD_VERBOSE)
  set(CMAKE_VERBOSE_MAKEFILE true)
endif()


#-----------------------------------------------------------------------------
# Print system information

message(STATUS "CMake version:   ${CMAKE_VERSION}")
message(STATUS "System:          ${CMAKE_SYSTEM}")
message(STATUS "Processor:       ${CMAKE_SYSTEM_PROCESSOR}")

message(STATUS "Verbose:         ${OPENTXS_AUDITOR_BUILD_VERBOSE}")
message(STATUS "Testing:         ${OPENTXS_AUDITOR_BUILD_TESTS}")
message(STATUS "Build RPM:       ${RPM}")
message(STATUS "Build DEB:       ${DEB}")


#-----------------------------------------------------------------------------
# Collect all binaries into bin subdirectory

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)


#-----------------------------------------------------------------------------
# Check which compiler to use

if(${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
  include(CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG(-std=c++11 HAVE_STD11)
  if(HAVE_STD11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -Werror")
  else()
    message(FATAL_ERROR "No advanced standard C++ support (-std=c++11 not defined) for GCC version.")
  endif()
elseif(${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
  include(CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG(-std=c++11 HAVE_STD11)
  if(HAVE_STD11)
    if (APPLE)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
    else()
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
  else()
    message(FATAL_ERROR "No C++11 support for Clang version. Please upgrade Clang to a version supporting C++11.")
  endif()
endif()

set(PEDANTIC_CXX_FLAGS "-Wall -Werror -Wextra -pedantic")

message(STATUS "C++ Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ Flags:       ${CMAKE_CXX_FLAGS}")
message(STATUS "C++ link flags:  ${CMAKE_CXX_LINK_FLAGS}")


#-----------------------------------------------------------------------------
# System libraries used for linking.

if(UNIX AND NOT APPLE)
  list(APPEND OPENTXS_AUDITOR_SYSTEM_LIBRARIES rt)
  list(APPEND OPENTXS_AUDITOR_SYSTEM_LIBRARIES dl)
endif()


#-----------------------------------------------------------------------------
# Third party libraries

find_package(OpenSSL REQUIRED)


#-----------------------------------------------------------------------------
# Force out-of-source build

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
message(FATAL_ERROR "CMake generation is not allowed within the source directory!
Remove the CMakeCache.txt file and try again from another folder, e.g.:

   rm CMakeCache.txt
   mkdir build
   cd build
   cmake ..
")
endif()


#-----------------------------------------------------------------------------
# Default to Release build

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_CURRENT_BINARY_DIR}/lib)


#-----------------------------------------------------------------------------
# Unit Testing

if(OPENTXS_AUDITOR_BUILD_TESTS)
  include(CTest)
  enable_testing()

  set(GTEST_ROOT ${OPENTXS_AUDITOR_SOURCE_DIR}/deps/gtest)
  set(GTEST_FOUND ON)
  set(GTEST_INCLUDE_DIRS ${GTEST_ROOT}/include)
  set(GTEST_LIBRARIES gtest)
  set(GTEST_MAIN_LIBRARIES gtest_main)
  set(GTEST_BOTH_LIBRARIES ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
endif()


#-----------------------------------------------------------------------------
# Get submodules
execute_process(COMMAND git "submodule" "update" "--init" "--recursive")


#-----------------------------------------------------------------------------
add_subdirectory(deps)
add_subdirectory(src)
add_subdirectory(tests)


#-----------------------------------------------------------------------------
# Install
INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/bin/opentxs-auditor
        DESTINATION bin)

# Packaging
set(CPACK_GENERATOR "TGZ")
set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_PACKAGE_NAME "opentxs-auditor")
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "Lucas Betschart")
set(CPACK_PACKAGE_VENDOR "Monetas AG")
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Open Transactions Auditor")
set(CPACK_PACKAGE_DESCRIPTION "
Open-Transactions democratizes financial and monetary actions.
You can use it for issuing currencies/stock, paying dividends, creating asset accounts, sending/receiving digital cash, writing/depositing cheques, cashier's cheques, creating basket currencies, trading on markets, scripting custom agreements, recurring payments, escrow, etc.
This software audits the transactions stream for Open Transactions voting pool.
")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(OPEN_TRANSACTIONS_WEBSITE "http://opentransactions.org")

# RPM
if(RPM)
  set(CPACK_GENERATOR "${CPACK_GENERATOR};RPM")
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/opentxs-auditor.spec.in" "${CMAKE_CURRENT_BINARY_DIR}/opentxs-auditor.spec" @ONLY IMMEDIATE)
  set(CPACK_RPM_USER_BINARY_SPECFILE "${CMAKE_CURRENT_BINARY_DIR}/opentxs-auditor.spec")
endif(RPM)

#DEB
if(DEB)
  set(CPACK_GENERATOR "${CPACK_GENERATOR};DEB")
  set(CPACK_DEBIAN_PACKAGE_DEPENDS "opentxs")
  set(CPACK_DEBIAN_PACKAGE_PRIORITY "extra")
  set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
  set(CPACK_DEBIAN_PACKAGE_HOMEPAGE ${OPEN_TRANSACTIONS_WEBSITE})
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Lucas Betschart")
endif()

include(CPack)
