cmake_minimum_required(VERSION 3.5...3.21)
project(PandoraEngine VERSION 0.0.1 LANGUAGES C CXX)


include(CTest)
enable_testing()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/debug/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/debug/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/debug)
add_compile_definitions(DEBUG)

if(NOT CMAKE_BUILD_TYPE)
    add_compile_definitions(UNKNOWN)
    message("Unknown build type.")
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    message("Debug build.")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message("Release build.")
    add_compile_definitions(RELEASE)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/release/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/release/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/release)
endif(CMAKE_BUILD_TYPE MATCHES DEBUG)
    

file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.c"
)

include_directories("src")
include_directories("include")

add_library(PandoraEngine SHARED ${SOURCES})
add_executable(Pandora ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
