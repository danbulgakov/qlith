project(qtpth)
cmake_minimum_required(VERSION 2.8)

include(ExternalProject)

set(THPTY_DIR "${CMAKE_CURRENT_BINARY_DIR}/thirdparty")

# External projects
externalproject_add(
    THPTY_PTH
    PREFIX ${THPTY_DIR}
    URL ftp://ftp.gnu.org/gnu/pth/pth-2.0.7.tar.gz
    CONFIGURE_COMMAND ./configure --prefix=<INSTALL_DIR>
    BUILD_COMMAND $(MAKE) install
    INSTALL_COMMAND ""
    BUILD_IN_SOURCE 1
)
externalproject_get_property(THPTY_PTH INSTALL_DIR)
set(THPTY_PTH_LIB_DIR ${INSTALL_DIR}/lib)
set(THPTY_PTH_INCLUDE_DIR ${INSTALL_DIR}/include)
set(THPTY_PTH_LIBRARY_NAME ${CMAKE_SHARED_LIBRARY_PREFIX}pth${CMAKE_SHARED_LIBRARY_SUFFIX})
set(THPTY_PTH_LIBRARY ${INSTALL_DIR}/lib/${THPTY_PTH_LIBRARY_NAME})
include_directories(${THPTY_PTH_INCLUDE_DIR})
message(${THPTY_PTH_LIBRARY})


# Library
set(QTPTH_LIBRARY_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
aux_source_directory(${QTPTH_LIBRARY_SOURCE_DIR} QTPTH_LIBRARY_SOURCE_FILES)
add_library(${PROJECT_NAME} SHARED ${QTPTH_LIBRARY_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${THPTY_PTH_LIBRARY})

# Tests
set(QTPTH_TESTS_NAME qtpthtests)
set(QTPTH_TESTS_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/test)
aux_source_directory(${QTPTH_TESTS_SOURCE_DIR} QTPTH_TESTS_SOURCE_FILES)

enable_testing(true)

