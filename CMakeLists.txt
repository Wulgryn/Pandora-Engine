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

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug build.")
    file(GLOB_RECURSE HEADERS 
        src/*.[h]pp
    )

    foreach(HEADER ${HEADERS})
        get_filename_component(HEADER_DIR ${HEADER} DIRECTORY)
        string(REPLACE "${PROJECT_SOURCE_DIR}/src" "" HEADER_DIR ${HEADER_DIR})
        set(HEADER_DESTINATION "${PROJECT_SOURCE_DIR}/bin/debug/headers${HEADER_DIR}")
        file(COPY ${HEADER} DESTINATION ${HEADER_DESTINATION})
    endforeach()
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message("Release build.")
    add_compile_definitions(RELEASE)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/release/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/release/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/release)
    
    file(GLOB_RECURSE OUT_HEADERS 
    ${PROJECT_SOURCE_DIR}/bin/release/headers/*.[h]pp
    )  
    file(REMOVE ${OUT_HEADERS})



    file(GLOB_RECURSE HEADERS 
        src/*.[h]pp
    )

    foreach(HEADER ${HEADERS})
        get_filename_component(HEADER_DIR ${HEADER} DIRECTORY)
        string(REPLACE "${PROJECT_SOURCE_DIR}/src" "" HEADER_DIR ${HEADER_DIR})
        set(HEADER_DESTINATION "${PROJECT_SOURCE_DIR}/bin/release/headers${HEADER_DIR}")
        file(COPY ${HEADER} DESTINATION ${HEADER_DESTINATION})
    endforeach()
endif(CMAKE_BUILD_TYPE MATCHES Debug)
    

file(GLOB_RECURSE SOURCES 
    ${PROJECT_SOURCE_DIR}/src/*.[hc]pp
)




include_directories("src")
include_directories("include")

add_library(PandoraEngine SHARED ${SOURCES})
if(NOT CMAKE_BUILD_TYPE MATCHES Release)
    add_executable(Pandora ${SOURCES})
endif(NOT CMAKE_BUILD_TYPE MATCHES Release)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

