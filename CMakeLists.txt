cmake_minimum_required(VERSION 3.5)
#------
# SETUP
#
set(project_name "Project")
set(project_version "0.0.1")

file(GLOB cfg_files "${CMAKE_SOURCE_DIR}/*.cfg")

if(cfg_files)
    list(GET cfg_files 0 cfg_file)
    file(STRINGS ${cfg_file} config_lines)

    list(GET config_lines 0 first_line)
    # "name=" utáni rész kiolvasása
    string(REGEX MATCH "name=(.*)" name_match ${first_line})

    # A nevet kinyerjük a ${CMAKE_MATCH_1} segítségével
    if(name_match)
        set(project_name "${CMAKE_MATCH_1}")
        file(RENAME ${cfg_file} ${project_name}.cfg)
    endif()

    list(GET config_lines 1 first_line)
    # "name=" utáni rész kiolvasása
    string(REGEX MATCH "version=(.*)" version_match ${first_line})

    # A nevet kinyerjük a ${CMAKE_MATCH_1} segítségével
    if(version_match)
        set(project_version "${CMAKE_MATCH_1}")
    endif()

    # Kiírjuk az eredményeket a konzolon
    message(STATUS "Project Name: ${project_name}")
    message(STATUS "Project Version: ${project_version}")
endif()

file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/.vscode")
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/assets")
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/externals")
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/externals/headers")
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/externals/libs")
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/externals/dlls")
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/src")

file(GLOB_RECURSE cpps
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)
if(NOT cpps)
message(STATUS "Creating main.cpp")
    file(WRITE ${CMAKE_SOURCE_DIR}/src/main.cpp "#include <iostream>\n\nint main(int argc, char** argv) {\n    std::cout << \"Hello World!\" << std::endl;\n    return 0;\n}\n")
endif()

get_filename_component(current_dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)



if(NOT EXISTS ${CMAKE_SOURCE_DIR}/${project_name}.cfg)
    set(project_name ${current_dir_name})
    file(WRITE ${CMAKE_SOURCE_DIR}/${project_name}.cfg "name=${project_name}\nversion=0.0.1\nauthor=none")
endif()

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/.vscode/c_cpp_properties.json")
    file(WRITE "${CMAKE_SOURCE_DIR}/.vscode/c_cpp_properties.json" 
    "{\n"
    "    \"configurations\": [\n"
    "        {\n"
    "            \"name\": \"Windows\",\n"
    "            \"includePath\": [\n"
    "                \"\${workspaceFolder}/src/\",\n"
    "                \"\${workspaceFolder}/externals/headers/\"\n"
    "            ],\n"
    "            \"defines\": [],\n"
    "            \"cStandard\": \"c23\",\n"
    "            \"cppStandard\": \"c++17\",\n"
    "            \"intelliSenseMode\": \"\${default}\"\n"
    "        }\n"
    "    ],\n"
    "    \"version\": 4\n"
    "}\n"
    )
endif()

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/.vscode/settings.json")
    file(WRITE "${CMAKE_SOURCE_DIR}/.vscode/settings.json"
    "{\n"
    "    \"files.exclude\": {\n"
    "        \"**/.git\": true,\n"
    "        \"**/build\": true,\n"
    "    },\n"
    "    \"cmake.configureOnOpen\": true,\n"
    "    \"cmake.configureOnStart\": true,\n"
    "    \"cmake.configureSettings\": {\n"
    "        \"CMAKE_BUILD_TYPE\": \"Debug\"\n"
    "    },\n"
    "    \"cmake.configureOnEdit\": true,\n"
    "    \"cmake.buildDirectory\": \"\${workspaceFolder}/build\",\n"
    "}\n"
    )
endif()

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/.vscode/tasks.json")
    file(WRITE "${CMAKE_SOURCE_DIR}/.vscode/tasks.json"
    "{
    \"version\": \"2.0.0\",
    \"tasks\": [
        {
            \"label\": \"cmake\",
            \"type\": \"shell\",
            \"windows\": {
                \"command\": \"cmake --build \\\\\\\"\${workspaceFolder}/build\\\\\\\" --config Debug --target all -- -j 4\",
            },
            \"linux\": {
                \"command\": \"cmake --build \\\\\\\"\${workspaceFolder}/build\\\\\\\" --config Debug --target all -- -j 4\",
            },
            \"command\": \"cmake --build \\\\\\\"\${workspaceFolder}/build\\\\\\\" --config Debug --target all -- -j 4\",
            \"options\": {
                \"cwd\": \"build\"
            },
            \"group\": {
                \"kind\": \"build\",
                \"isDefault\": true
            },
            \"dependsOn\": [
                \"cmake: configure\"
            ]
        },
        {
            \"label\": \"cmake: configure\",
            \"type\": \"shell\",
            \"command\": \"cmake -S . -B \\\\\\\"build\\\\\\\" -G Ninja -DCMAKE_BUILD_TYPE=Debug\",
            \"group\": {
                \"kind\": \"build\",
                \"isDefault\": true
            }
        }
    ]
    }"
    )
endif()

project(${project_name} VERSION ${project_version} LANGUAGES CXX C)
include(CTest)
enable_testing()

# set(PROJECT_NAME ${project_name})
# set(PROJECT_VERSION ${project_version})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_VERSION}/debug/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_VERSION}/debug/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_VERSION}/debug)
add_compile_definitions(DEBUG)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug build.")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message("Release build.")
    remove_definitions(DEBUG)
    add_compile_definitions(RELEASE)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_VERSION}/release/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_VERSION}/release/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_VERSION}/release)
endif(CMAKE_BUILD_TYPE MATCHES Debug)

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/.vscode/launch.json")
    file(WRITE "${CMAKE_SOURCE_DIR}/.vscode/launch.json" 
    "{
    \"configurations\": [
        {
            \"name\": \"(gdb) Launch\",
            \"type\": \"cppdbg\",
            \"request\": \"launch\",
            \"windows\": {
                \"program\": \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${current_dir_name}.exe\",
            },
            \"linux\": {
                \"program\": \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${current_dir_name}\",
            },
            \"osx\": {
                \"program\": \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${current_dir_name}\",
            },
            \"program\": \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${current_dir_name}.exe\",
            \"args\": [],
            \"stopAtEntry\": false,
            \"cwd\": \"\${workspaceFolder}\",
            \"environment\": [],
            \"externalConsole\": false,
            \"MIMode\": \"gdb\",
            \"miDebuggerPath\": \"gdb\",
            \"setupCommands\": [
                {
                    \"description\": \"Enable pretty-printing for gdb\",
                    \"text\": \"-enable-pretty-printing\",
                    \"ignoreFailures\": true
                },
                {
                    \"description\": \"Set Disassembly Flavor to Intel\",
                    \"text\": \"-gdb-set disassembly-flavor intel\",
                    \"ignoreFailures\": true
                }
            ],
            \"preLaunchTask\": \"cmake\"
        }
    ]
    }"
    )
endif()

#
# SETUP
#------



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)



file(GLOB_RECURSE SOURCES 
    ${CMAKE_SOURCE_DIR}/src/*.[hc]pp
    ${CMAKE_SOURCE_DIR}/src/*.[hc]
)



file(GLOB_RECURSE LIBS
    ${CMAKE_SOURCE_DIR}/externals/libs/*.a
)

file(GLOB_RECURSE DLLS
    ${CMAKE_SOURCE_DIR}/externals/dlls/*.dll
)

foreach(DLL ${DLLS})
    file(COPY ${DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()



include_directories("externals/headers")


# if(SOURCES)
#     add_executable(${PROJECT_NAME} ${SOURCES} ${DLLS})
#     target_link_directories(${PROJECT_NAME} PUBLIC externals/libs)
#     target_link_libraries(${PROJECT_NAME} ${LIBS})
#     target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++ -static)
#     set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
# endif()

