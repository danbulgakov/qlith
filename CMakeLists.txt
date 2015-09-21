project(qtpth)
cmake_minimum_required(VERSION 2.8)

include(ExternalProject)

set(THPTY_DIR "${CMAKE_CURRENT_BINARY_DIR}/thirdparty")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
add_definitions(-DLOG_LEVEL=4)

# Qt components
set(THPTY_QT_VERSION "4.8" CACHE STRING "Used Qt version")
set(QT_USE_QTTEST TRUE)
set(QT_DONT_USE_QTGUI TRUE)
find_package(Qt4 ${THPTY_QT_VERSION} REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
set(CMAKE_AUTOMOC TRUE)
include_directories(${QT_INCLUDE_DIRS})


# External projects
set(THPTY_PTH_NAME pth)
externalproject_add(
    ${THPTY_PTH_NAME}
    PREFIX ${THPTY_DIR}
    URL ftp://ftp.gnu.org/gnu/pth/pth-2.0.7.tar.gz
    CONFIGURE_COMMAND CFLAGS=-fPIC ./configure --prefix=<INSTALL_DIR>
    BUILD_COMMAND $(MAKE) install
    INSTALL_COMMAND ""
    BUILD_IN_SOURCE 1
)
externalproject_get_property(${THPTY_PTH_NAME} INSTALL_DIR)
set(THPTY_PTH_LIB_DIR ${INSTALL_DIR}/lib)
set(THPTY_PTH_INCLUDE_DIR ${INSTALL_DIR}/include)
set(THPTY_PTH_LIBRARY_NAME ${CMAKE_STATIC_LIBRARY_PREFIX}pth${CMAKE_STATIC_LIBRARY_SUFFIX})
set(THPTY_PTH_LIBRARY ${INSTALL_DIR}/lib/${THPTY_PTH_LIBRARY_NAME})
include_directories(${THPTY_PTH_INCLUDE_DIR})


set(THPTY_LIBRARIES
    ${THPTY_PTH_LIBRARY}
    ${QT_LIBRARIES}
)

# Library
set(QTPTH_LIBRARY_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
include_directories(${QTPTH_LIBRARY_SOURCE_DIR})
aux_source_directory(${QTPTH_LIBRARY_SOURCE_DIR} QTPTH_LIBRARY_SOURCE_FILES)
add_library(${PROJECT_NAME} SHARED ${QTPTH_LIBRARY_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${THPTY_LIBRARIES})

# Tests
enable_testing(true)
set(QTPTH_TESTS_NAME qtpthtests)
set(QTPTH_TESTS_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/test)
include_directories(${QTPTH_TESTS_SOURCE_DIR})
aux_source_directory(${QTPTH_TESTS_SOURCE_DIR} QTPTH_TESTS_SOURCE_FILES)
add_executable(${QTPTH_TESTS_NAME} ${QTPTH_LIBRARY_SOURCE_FILES} ${QTPTH_TESTS_SOURCE_FILES})
target_link_libraries(${QTPTH_TESTS_NAME} ${THPTY_LIBRARIES})


