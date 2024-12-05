cmake_minimum_required (VERSION 3.8)

project (${PROJECT_NAME} "Python")

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_DEFAULT_STARTUP_PROJECT ${PROJECT_NAME})

add_executable (${PROJECT_NAME} "src/Python.cpp" "src/DrawingFunctions.h" "src/GameInfo.h" "src/ProcessingFunctions.h")

find_package(SFML 2.6.2 COMPONENTS system window graphics audio network REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-audio sfml-network sfml-window sfml-system)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()
