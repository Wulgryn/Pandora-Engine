cmake_minimum_required(VERSION 3.21)
project(PandoraEngine VERSION 0.0.1 LANGUAGES C CXX)
set(PROJECT_VERSION 0.0.1-alpha)
set(CMAKE_VERBOSE_MAKEFILE ON)

include(CTest)
enable_testing()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${PROJECT_VERSION}/debug/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${PROJECT_VERSION}/debug/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${PROJECT_VERSION}/debug)
add_compile_definitions(DEBUG)
add_compile_definitions(BUILD_DLL)

if(NOT CMAKE_BUILD_TYPE)
    add_compile_definitions(UNKNOWN)
    message("Unknown build type.")
endif(NOT CMAKE_BUILD_TYPE)

file(GLOB_RECURSE HEADERS 
    src/**.hpp
    src/**.h
)
file(GLOB_RECURSE CS_HEADERS 
    "src/C# DLL/*.h"
    "src/C# DLL/*.hpp"
)
list(REMOVE_ITEM HEADERS ${CS_HEADERS})

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug build.")

    foreach(HEADER ${HEADERS})
        get_filename_component(HEADER_DIR ${HEADER} DIRECTORY)
        string(REPLACE "${PROJECT_SOURCE_DIR}/src" "" HEADER_DIR ${HEADER_DIR})
        set(HEADER_DESTINATION "${PROJECT_SOURCE_DIR}/bin/${PROJECT_VERSION}/debug/headers${HEADER_DIR}")
        file(COPY ${HEADER} DESTINATION ${HEADER_DESTINATION})
    endforeach()

    foreach(CS_HEADER ${CS_HEADERS})
        get_filename_component(HEADER_DIR ${CS_HEADER} DIRECTORY)
        string(REPLACE "${PROJECT_SOURCE_DIR}/src/C# DLL" "" HEADER_DIR ${HEADER_DIR})
        set(HEADER_DESTINATION "${PROJECT_SOURCE_DIR}/bin/${PROJECT_VERSION}/debug/C# headers${HEADER_DIR}")
        file(COPY ${CS_HEADER} DESTINATION ${HEADER_DESTINATION})
    endforeach()
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message("Release build.")
    remove_definitions(DEBUG)
    add_compile_definitions(RELEASE)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${PROJECT_VERSION}/release/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${PROJECT_VERSION}/release/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${PROJECT_VERSION}/release)
    
    file(GLOB_RECURSE OUT_HEADERS 
        ${PROJECT_SOURCE_DIR}/bin/${PROJECT_VERSION}/release/*.[h]pp
    )  
    file(REMOVE ${OUT_HEADERS})



    foreach(HEADER ${HEADERS})
        get_filename_component(HEADER_DIR ${HEADER} DIRECTORY)
        string(REPLACE "${PROJECT_SOURCE_DIR}/src" "" HEADER_DIR ${HEADER_DIR})
        set(HEADER_DESTINATION "${PROJECT_SOURCE_DIR}/bin/${PROJECT_VERSION}/release/headers${HEADER_DIR}")
        file(COPY ${HEADER} DESTINATION ${HEADER_DESTINATION})
    endforeach()

    foreach(CS_HEADER ${CS_HEADERS})
        get_filename_component(HEADER_DIR ${CS_HEADER} DIRECTORY)
        string(REPLACE "${PROJECT_SOURCE_DIR}/src/C# DLL" "" HEADER_DIR ${HEADER_DIR})
        set(HEADER_DESTINATION "${PROJECT_SOURCE_DIR}/bin/${PROJECT_VERSION}/release/C# headers${HEADER_DIR}")
        file(COPY ${CS_HEADER} DESTINATION ${HEADER_DESTINATION})
    endforeach()
endif(CMAKE_BUILD_TYPE MATCHES Debug)
    

file(GLOB_RECURSE SOURCES 
    ${PROJECT_SOURCE_DIR}/src/*.[hc]pp
    ${PROJECT_SOURCE_DIR}/src/*.[hc]
)

foreach(SOURCE ${SOURCES})
    message(${SOURCE})
endforeach()


file(GLOB_RECURSE CS_SOURCES_ONLY
    "${PROJECT_SOURCE_DIR}/src/C# DLL/*.[hc]pp"
)

list(REMOVE_ITEM SOURCES ${CS_SOURCES_ONLY})

file(GLOB_RECURSE CS_SOURCES 
    ${PROJECT_SOURCE_DIR}/src/*.[hc]pp
    ${PROJECT_SOURCE_DIR}/src/*.[hc]
)

file(GLOB_RECURSE LIBS
    ${CMAKE_SOURCE_DIR}/libs/*.a
)

file(GLOB_RECURSE DLLS
    ${CMAKE_SOURCE_DIR}/dlls/*.dll
)


include_directories("src")
include_directories("include")

#link_directories("libs")
#link_directories("dlls")
#link_libraries("libs")
set(CMAKE_IMPORT_LIBRARY_SUFFIX ".a")

# add_library(PandoraEngine SHARED ${SOURCES} ${DLLS})
# target_link_libraries(PandoraEngine ${LIBS} SOIL)
# target_include_directories(PandoraEngine PUBLIC src)
# target_link_options(PandoraEngine PRIVATE -static-libgcc -static-libstdc++ -static)
# set_target_properties(PandoraEngine PROPERTIES
#     OUTPUT_NAME "PandoraEngine"
#     PREFIX ""
#     PUBLIC_HEADER "${HEADERS}"
# )

add_library(PandoraEngineStatic STATIC ${SOURCES} ${LIBS} ${DLLS})
target_link_libraries(PandoraEngineStatic PUBLIC ${LIBS} SOIL)
target_include_directories(PandoraEngineStatic PUBLIC src)
target_link_options(PandoraEngineStatic PRIVATE -static-libgcc -static-libstdc++ -static)
set_target_properties(PandoraEngineStatic PROPERTIES
    OUTPUT_NAME "PandoraEngineStatic"
    PUBLIC_HEADER "${HEADERS}"
)


# add_library(PandoraEngineCS SHARED ${CS_SOURCES})
# set_target_properties(PandoraEngineCS PROPERTIES PREFIX "")
# target_link_libraries(PandoraEngineCS ${LIBS})

# if(NOT CMAKE_BUILD_TYPE MATCHES Release)
# add_executable(Pandora ${SOURCES})
# target_link_libraries(Pandora ${LIBS})
# target_link_options(Pandora PRIVATE -static-libgcc -static-libstdc++ -static)
# endif(NOT CMAKE_BUILD_TYPE MATCHES Release)


if(NOT CMAKE_BUILD_TYPE MATCHES Release)
    add_executable(PandoraTest test/src/main.cpp)
    target_link_directories(PandoraTest PUBLIC ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib)
    target_link_libraries(PandoraTest PandoraEngineStatic)
    target_link_options(PandoraTest PRIVATE -static-libgcc -static-libstdc++ -static)
endif(NOT CMAKE_BUILD_TYPE MATCHES Release)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)