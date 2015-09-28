project(qlith)
cmake_minimum_required(VERSION 2.8)

include(ExternalProject)

set(QLITH_DIR "${CMAKE_CURRENT_BINARY_DIR}/thirdparty")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
add_definitions(-DLOG_LEVEL=4)

# Qt components
set(QLITH_QT_VERSION "4.8" CACHE STRING "Used Qt version")
set(QT_USE_QTTEST TRUE)
set(QT_DONT_USE_QTGUI TRUE)
find_package(Qt4 ${QLITH_QT_VERSION} REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
set(CMAKE_AUTOMOC TRUE)
include_directories(${QT_INCLUDE_DIRS})


# External projects
set(QLITH_PTH_NAME pth)
externalproject_add(
    ${QLITH_PTH_NAME}
    PREFIX ${QLITH_DIR}
    URL ftp://ftp.gnu.org/gnu/pth/pth-2.0.7.tar.gz
    CONFIGURE_COMMAND CFLAGS=-fPIC ./configure --prefix=<INSTALL_DIR>
    BUILD_COMMAND $(MAKE) install
    INSTALL_COMMAND ""
    BUILD_IN_SOURCE 1
)
externalproject_get_property(${QLITH_PTH_NAME} INSTALL_DIR)
set(QLITH_PTH_LIB_DIR ${INSTALL_DIR}/lib)
set(QLITH_PTH_INCLUDE_DIR ${INSTALL_DIR}/include)
set(QLITH_PTH_LIBRARY_NAME ${CMAKE_STATIC_LIBRARY_PREFIX}pth${CMAKE_STATIC_LIBRARY_SUFFIX})
set(QLITH_PTH_LIBRARY ${INSTALL_DIR}/lib/${QLITH_PTH_LIBRARY_NAME})
include_directories(${QLITH_PTH_INCLUDE_DIR})



set(QLITH_LIBRARIES
    ${QLITH_PTH_LIBRARY}
    ${QT_LIBRARIES}
)

# Library
set(QLITH_LIBRARY_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
include_directories(${QLITH_LIBRARY_SOURCE_DIR})
aux_source_directory(${QLITH_LIBRARY_SOURCE_DIR} QLITH_LIBRARY_SOURCE_FILES)
add_library(${PROJECT_NAME} SHARED ${QLITH_LIBRARY_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${QLITH_LIBRARIES})

# Tests
enable_testing(true)
set(QLITH_TESTS_NAME qlithtests)
set(QLITH_TESTS_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/test)
include_directories(${QLITH_TESTS_SOURCE_DIR})
aux_source_directory(${QLITH_TESTS_SOURCE_DIR} QLITH_TESTS_SOURCE_FILES)
add_executable(${QLITH_TESTS_NAME} ${QLITH_LIBRARY_SOURCE_FILES} ${QLITH_TESTS_SOURCE_FILES})
target_link_libraries(${QLITH_TESTS_NAME} ${QLITH_LIBRARIES})


