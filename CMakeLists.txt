cmake_minimum_required(VERSION 3.5)
#------
# SETUP
#
set(project_name "Project")
set(project_version "0.0.1")
set(project_type "APP")
set(copy_headers "False")
set(lib_collection "externals/libs")
set(dll_collection "externals/dlls")
set(header_collection "externals/headers")
set(use_default_linkers "True")
set(custom_linkers "")

set(default_linkers "-static-libgcc;-static-libstdc++;-static;-Wl,--allow-multiple-definition")

file(GLOB cfg_files "${CMAKE_SOURCE_DIR}/*.cfg")

if(cfg_files)
    list(GET cfg_files 0 cfg_file)
    file(STRINGS ${cfg_file} config_lines)

	foreach(line IN LISTS config_lines)
        string(REGEX MATCH "name=(.*)" name_match ${line})

		# A nevet kinyerjük a ${CMAKE_MATCH_1} segítségével
		if(name_match)
			string(REPLACE " " "" modified_project_name ${CMAKE_MATCH_1})
			set(project_name ${modified_project_name})
			file(RENAME ${cfg_file} ${project_name}.cfg)
		endif()
		
		string(REGEX MATCH "version=(.*)" version_match ${line})

		# A nevet kinyerjük a ${CMAKE_MATCH_1} segítségével
		if(version_match)
			set(project_version "${CMAKE_MATCH_1}")
		endif()

        string(REGEX MATCH "type=(.*)" type_match ${line})

		# A nevet kinyerjük a ${CMAKE_MATCH_1} segítségével
		if(type_match)
			set(project_type "${CMAKE_MATCH_1}")
		endif()
		
		string(REGEX MATCH "copy_headers=(.*)" copy_headers_match ${line})

		# A nevet kinyerjük a ${CMAKE_MATCH_1} segítségével
		if(copy_headers_match)
			set(copy_headers "${CMAKE_MATCH_1}")
		endif()

        string(REGEX MATCH "lib_paths=(.*)" lib_paths_match ${line})

		# A nevet kinyerjük a ${CMAKE_MATCH_1} segítségével
		if(lib_paths_match)
            string(REPLACE "\\" "/" output "${CMAKE_MATCH_1}")
            string(REPLACE "|" ";" output_list "${output}")
			set(lib_collection "${output_list}")
		endif()

        string(REGEX MATCH "dll_paths=(.*)" dll_paths_match ${line})

		# A nevet kinyerjük a ${CMAKE_MATCH_1} segítségével
		if(dll_paths_match)
            string(REPLACE "\\" "/" output "${CMAKE_MATCH_1}")
            string(REPLACE "|" ";" output_list "${output}")
			set(dll_collection "${output_list}")
		endif()

        string(REGEX MATCH "include_headers=(.*)" include_headers_match ${line})

		# A nevet kinyerjük a ${CMAKE_MATCH_1} segítségével
		if(include_headers_match)
        string(REPLACE "|" ";" output_list "${CMAKE_MATCH_1}")
			set(header_collection "${output_list}")
		endif()

        string(REGEX MATCH "use_default_linkers=(.*)" use_default_linkers_match ${line})

		# A nevet kinyerjük a ${CMAKE_MATCH_1} segítségével
		if(use_default_linkers_match)
			set(use_default_linkers "${CMAKE_MATCH_1}")
		endif()

        string(REGEX MATCH "custom_linkers=(.*)" custom_linkers_match ${line})

		# A nevet kinyerjük a ${CMAKE_MATCH_1} segítségével
		if(custom_linkers_match)
            string(REPLACE "\"" "" custom_linkers "${CMAKE_MATCH_1}")
            string(REPLACE " " ";" custom_linkers "${custom_linkers}")
			set(custom_linkers "${custom_linkers}")
		endif()

    endforeach()

    # Kiírjuk az eredményeket a konzolon
    message("-- Project Name: ${project_name}")
    message("-- Project Version: ${project_version}")
    message("-- Project Type: ${project_type}")
	message("-- Copy Headers: ${copy_headers}")
    message("-- LIB COLLECTION: ${lib_collection}")
    message("-- DLL COLLECTION: ${dll_collection}")
    message("-- HEADER COLLECTION: ${header_collection}")
    if(use_default_linkers MATCHES "True")
        message("-- Linkers: ${default_linkers}")
    else()
        message("-- Custom linkers: ${custom_linkers}")
    endif()
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
    string(REPLACE " " "" modified_project_name ${current_dir_name})
    set(project_name ${modified_project_name})
    file(WRITE ${CMAKE_SOURCE_DIR}/${project_name}.cfg 
"#Without spaces
name=${project_name}
version=0.0.1
author=none
#APP / STATIC_LIB / SHARED_LIB
#
#APP: .exe
#Executeable file.
#
#STATIC_LIB: .a 
#Stand alone lib file. Other libs used in this project won't be included in final file.
#
#SHARED_LIB: .a/.dll
#Creates 2 file. But other libs included this project will be included in final files.
type=APP
#True / False
copy_headers=False
#Path of containing folders of libraries.
#To include multiple: libs1|libs2
lib_paths=externals/libs
#Path of containing folders of dlls.
#To include multiple: dlls1|dlls2
dll_paths=externals/dlls
#Path of containing folders of headers.
#To include multiple: headers1|headers2
include_headers=externals/headers
#Default linker flags
#-static-libgcc;-static-libstdc++;-static;-Wl,--allow-multiple-definition
use_default_linkers=True
#Custom linker flags
#You can use spaces in between flags.
custom_linkers=\"\""
    )
endif()

set(headers_ "")
foreach(header ${header_collection})
    string(REPLACE "\\" "/" header "${header}")
    if("${header}" MATCHES ":")
        # Perform actions when the string contains ":"
        # ...
        string(REPLACE "${header}" "\t\t\t\t\"${header}\",\n" str_ "${header}")
    else()
        # Perform actions when the string does not contain ":"
        # ...
        string(REPLACE "${header}" "\t\t\t\t\"\${workspaceFolder}/${header}\",\n" str_ "${header}")
    endif()
    list(APPEND headers_ "${str_}")
endforeach()

string(REPLACE ";" "" headers_ "${headers_}")

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/.vscode/c_cpp_properties.json")
    file(WRITE "${CMAKE_SOURCE_DIR}/.vscode/c_cpp_properties.json" 
    "{\n"
    "    \"configurations\": [\n"
    "        {\n"
    "            \"name\": \"Windows\",\n"
    "            \"includePath\": [\n"
    "                \"\${workspaceFolder}/src/\",\n"
    "                \"\${workspaceFolder}/externals/headers/\",\n${headers_}"
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
    "    \"cmake.debugConfig\": {\n"
    "        \"externalConsole\": true\n"
    "    }\n"
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

file(GLOB_RECURSE HEADERS 
    ${CMAKE_SOURCE_DIR}/src/**.hpp
    ${CMAKE_SOURCE_DIR}/src/**.h
)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug build.")
	
	if(copy_headers MATCHES "True") 
		file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/bin/${PROJECT_VERSION}/debug/headers")
		foreach(HEADER ${HEADERS})
			get_filename_component(HEADER_DIR ${HEADER} DIRECTORY)
			string(REPLACE "${CMAKE_SOURCE_DIR}/src" "" HEADER_DIR ${HEADER_DIR})
			set(HEADER_DESTINATION "${PROJECT_SOURCE_DIR}/bin/${PROJECT_VERSION}/debug/headers/${project_name}/${HEADER_DIR}")
			file(COPY ${HEADER} DESTINATION ${HEADER_DESTINATION})
		endforeach()
	endif()
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message("Release build.")
    remove_definitions(DEBUG)
    add_compile_definitions(RELEASE)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_VERSION}/release/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_VERSION}/release/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_VERSION}/release)
	
	if(copy_headers MATCHES "True")
		file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/bin/${PROJECT_VERSION}/release/headers")
		foreach(HEADER ${HEADERS})
			get_filename_component(HEADER_DIR ${HEADER} DIRECTORY)
			string(REPLACE "${CMAKE_SOURCE_DIR}/src" "" HEADER_DIR ${HEADER_DIR})
			set(HEADER_DESTINATION "${PROJECT_SOURCE_DIR}/bin/${PROJECT_VERSION}/release/headers/${project_name}/${HEADER_DIR}")
			file(COPY ${HEADER} DESTINATION ${HEADER_DESTINATION})
		endforeach()
	endif()
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


include_directories("src")

message("HEADERS")
message("-- MAIN HEADERS: src")

foreach(header ${header_collection})
    message("-- HEADER: ${header}")
    include_directories("${header}")
endforeach(header ${header_collection})

message("SOURCES")

file(GLOB_RECURSE SOURCES 
    ${CMAKE_SOURCE_DIR}/src/**.[hc]pp
    ${CMAKE_SOURCE_DIR}/src/**.[hc]
)

foreach(SOURCE ${SOURCES})
    message("-- SOURCE: ${SOURCE}")
endforeach(SOURCE ${SOURCES})



message("LIBS")

set(LIBS)

foreach(lib_path ${lib_collection})
    file(GLOB_RECURSE LIBS
        ${lib_path}/*.a
        ${lib_path}/*.lib
    )
endforeach(lib_path ${lib_collection})
foreach(LIB ${LIBS})
    message("-- LIB: ${LIB}")
    
endforeach(LIB ${SOURCES})


message("DLLS")

set(DLLS)

foreach(dll_path ${dll_collection})
    file(GLOB_RECURSE DLLS
        ${dll_path}/*.dll
    )
endforeach(dll_path ${dll_collection})

foreach(DLL ${DLLS})
    message("-- DLL: ${DLL}")
endforeach(DLL ${DLLS})

foreach(DLL ${DLLS})
    file(COPY ${DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()




if(SOURCES)
    if(project_type MATCHES "APP")
        add_executable(${PROJECT_NAME} ${SOURCES} ${DLLS})
        target_link_directories(${PROJECT_NAME} PUBLIC externals/libs)
        target_link_libraries(${PROJECT_NAME} ${LIBS})
        if(use_default_linkers MATCHES "True")
            target_link_options(${PROJECT_NAME} PRIVATE ${default_linkers})
        else()
            target_link_options(${PROJECT_NAME} PRIVATE ${custom_linkers})
        endif()
        set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            OUTPUT_NAME "${PROJECT_NAME}"
            PREFIX ""
        )
    elseif(project_type MATCHES "SHARED_LIB")
        add_library(${PROJECT_NAME} SHARED ${SOURCES})
        target_link_directories(${PROJECT_NAME} PUBLIC externals/libs)
        target_link_libraries(${PROJECT_NAME} ${LIBS})
        if(use_default_linkers MATCHES "True")
            target_link_options(${PROJECT_NAME} PRIVATE ${default_linkers})
        else()
            target_link_options(${PROJECT_NAME} PRIVATE ${custom_linkers})
        endif()
        set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            OUTPUT_NAME "${PROJECT_NAME}"
            PREFIX ""
        )
	elseif(project_type MATCHES "STATIC_LIB")
        add_library(${PROJECT_NAME} STATIC ${SOURCES})
        target_link_directories(${PROJECT_NAME} PUBLIC externals/libs)
        target_link_libraries(${PROJECT_NAME} ${LIBS})
        if(use_default_linkers MATCHES "True")
            target_link_options(${PROJECT_NAME} PRIVATE ${default_linkers})
        else()
            target_link_options(${PROJECT_NAME} PRIVATE ${custom_linkers})
        endif()
        set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            OUTPUT_NAME "${PROJECT_NAME}"
        )
    endif()
endif()
