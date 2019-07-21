# shxx library
project(shxx)

set(PROJECT_HEADERS_ROOT "${CMAKE_CURRENT_LIST_DIR}/include/")
set(PROJECT_SOURCES_ROOT "${CMAKE_CURRENT_LIST_DIR}/src")

set(PROJECT_HEADERS
    ${PROJECT_HEADERS_ROOT}/SHXX/SHash32.hpp
    )
set(PROJECT_SOURCES
    ${PROJECT_SOURCES_ROOT}/SHXX/SHash32.cpp
    )
#source_group(TREE "${PROJECT_HEADERS_ROOT}" FILES ${PROJECT_HEADERS})
#source_group(TREE "${PROJECT_SOURCES_ROOT}" FILES ${PROJECT_SOURCES})

### LIBRARY
add_library(${PROJECT_NAME} ${PROJECT_SOURCES})
add_library(SHXX::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        LINKER_LANGUAGE CXX
        OUTPUT_NAME ${PROJECT_NAME}
    )
#target_sources(${PROJECT_NAME}
    #PRIVATE
        #${PROJECT_SOURCES}
    #)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        xxHash::xxhash)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_HEADERS_ROOT}>
        $<BUILD_INTERFACE:${SHXX_GEN_PATH}>
        $<INSTALL_INTERFACE:include/>)
#target_compile_definitions(${PROJECT_NAME})
#target_compile_option(${PROJECT_NAME})

include(GNUInstallDirs)
install(
    TARGETS ${PROJECT_NAME}
    EXPORT SHXXTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
install(
    DIRECTORY ${PROJECT_HEADERS_ROOT}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

if(Smak_BUILD_UT)
    #add_subdirectory(unit_tests)
endif(Smak_BUILD_UT)
