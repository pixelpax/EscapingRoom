cmake_minimum_required (VERSION 2.6)
project (UE4)
set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_USE_RESPONSE_FILE_FOR_OBJECTS 1 CACHE BOOL "" FORCE)
SET(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES 1 CACHE BOOL "" FORCE)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_C_COMPILER "/usr/bin/clang")

include("/Users/gabriel/Documents/Unreal Projects/EscapingRoom/Intermediate/ProjectFiles/IncludeDirectories.cmake")
include("/Users/gabriel/Documents/Unreal Projects/EscapingRoom/Intermediate/ProjectFiles/Definitions.cmake")
include("/Users/gabriel/Documents/Unreal Projects/EscapingRoom/Intermediate/ProjectFiles/EscapingRoomEditor.cmake")

set(MONO_ROOT_PATH "/Users/Shared/Epic Games/UE_4.18/Engine/Binaries/DotNET")
set(BUILD cd "${MONO_ROOT_PATH}")

# Custom target for EscapingRoomEditor project, Development configuration
#add_custom_target(EscapingRoomEditor-Development ${BUILD} && mono UnrealBuildTool.exe EscapingRoomEditor Mac Development -project="/Users/gabriel/Documents/Unreal Projects/EscapingRoom/EscapingRoom.uproject" -game -progress)
add_custom_target(EscapingRoomEditor-Development cd /Users/Shared/Epic\ Games/UE_4.18/Engine/Binaries/DotNET && mono UnrealBuildTool.exe EscapingRoomEditor Mac Development -project=/Users/gabriel/Documents/Unreal\ Projects/EscapingRoom/EscapingRoom.uproject -game -progress)
add_custom_target(EscapingRoomEditor-Development-CLEAN ${BUILD} && mono UnrealBuildTool.exe EscapingRoomEditor Mac Development -project="/Users/gabriel/Documents/Unreal Projects/EscapingRoom/EscapingRoom.uproject" -clean)

add_executable(PleaseIgnoreMe ${EscapingRoomEditor_FILES})