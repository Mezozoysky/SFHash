cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

if("${CMAKE_VERSION}" VERSION_LESS "3.0")
    project(SHXX CXX C)
else()
    cmake_policy(SET CMP0028 NEW)
    project(SHXX LANGUAGES CXX C)
endif()

###
# Global project defines
###
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQURED TRUE)
# set(CMAKE_VERBOSE_MAKEFILE TRUE)

#set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Project build type")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")

# Project cmake modules path
#list(INSERT CMAKE_MODULE_PATH  0 "${PROJECT_SOURCE_DIR}/../cmake/modules/")

###
# Project config data
###
set(SHXX_BITS 0)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(SHXX_BITS 64)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(SHXX_BITS 32)
else()
    message(FATAL_ERROR "Unsupported void pointer size: ${CMAKE_SIZEOF_VOID_P}")
endif()

set(SHXX_VERSION_MAJOR 0)
set(SHXX_VERSION_MINOR 1)
set(SHXX_VERSION_PATCH 0)
set(SHXX_VERSION "${SHXX_VERSION_MAJOR}.${SHXX_VERSION_MINOR}.${SHXX_VERSION_PATCH}")
message(STATUS "SHXX version: ${SHXX_VERSION}")
set(SHXX_GEN_PATH "${CMAKE_BINARY_DIR}/generated-sources/")
message(STATUS "SHXX generated sources directory: ${SHXX_GEN_PATH}")

set(SHXX_CONFIG_PATH "${SHXX_GEN_PATH}/SHXX/Config.hpp")
configure_file(
    "${PROJECT_SOURCE_DIR}/Config.hpp.in"
    "${SHXX_CONFIG_PATH}"
    )

install(
    FILES "${SHXX_CONFIG_PATH}"
    DESTINATION include/SHXX/
    )

###
# Global project options
###
option(BUILD_SHARED_LIBS "Build shared libs/use dynamic linking" OFF)

option(SHXX_BUILD_ENGINE "Build Engine library" ON)
option(SHXX_BUILD_UT "Build Unit tests" ON)
option(SHXX_BUILD_EXAMPLES "Build examples" ON)
option(SHXX_USE_BUNDLED_XXHASH "Use xxHash from submodule as subdirectory" ON)

###
# Define targets
###
# xxHash
if(SHXX_USE_BUNDLED_XXHASH)
    set(XXHASH_BUILD_ENABLE_INLINE_API ON)
    set(XXHASH_BUILD_XXHSUM ON)
    add_subdirectory(${PROJECT_SOURCE_DIR}/../xxHash/cmake_unofficial/ ${PROJECT_SOURCE_DIR}/../xxHash/ EXCLUDE_FROM_ALL)
else()
    find_package(xxHash 0.7.0
        COMPONENTS xxhash
        CONFIG REQUIRED)
endif()
# SHXX
add_subdirectory(shxx)
# SHXX examples
if(SHXX_BUILD_EXAMPLES)
    #add_subdirectory(examples/)
endif()

###
# Handle cmake config
###
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
# set cmake config paths
set(SHXX_VERSION_CONFIG ${PROJECT_BINARY_DIR}/SHXXConfigVersion.cmake)
set(SHXX_PROJECT_CONFIG ${PROJECT_BINARY_DIR}/SHXXConfig.cmake)
set(SHXX_TARGETS_CONFIG ${PROJECT_BINARY_DIR}/SHXXTargets.cmake)
set(SHXX_CONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME}/)
# create cmake config
write_basic_package_version_file(${SHXX_VERSION_CONFIG}
                                 VERSION ${SHXX_VERSION}
                                 COMPATIBILITY AnyNewerVersion
                                 )
configure_package_config_file(${PROJECT_SOURCE_DIR}/SHXXConfig.cmake.in
                              ${SHXX_PROJECT_CONFIG}
                              INSTALL_DESTINATION ${SHXX_CONFIG_INSTALL_DIR}
                              )
if("${CMAKE_VERSION}" VERSION_LESS "3.0")
    export(TARGETS shxx
        FILE ${SHXX_TARGETS_CONFIG}
        NAMESPACE SHXX::
        )
else()
    export(EXPORT SHXXTargets
        FILE ${SHXX_TARGETS_CONFIG}
        NAMESPACE SHXX::
        )
endif()
# install cmake config
install(FILES ${SHXX_PROJECT_CONFIG} ${SHXX_VERSION_CONFIG}
        DESTINATION ${SHXX_CONFIG_INSTALL_DIR}
        )
install(EXPORT SHXXTargets
        DESTINATION ${SHXX_CONFIG_INSTALL_DIR}
        NAMESPACE SHXX::
        )

###
# Install misc files
###
#install(DIRECTORY ../cmake/modules
        #DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${CMAKE_PROJECT_NAME}/cmake/
        #)
install(FILES ../README.md ../LICENSE
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${CMAKE_PROJECT_NAME}/
        )
