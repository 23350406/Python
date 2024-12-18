cmake_minimum_required(VERSION 3.22.1)
project(Python)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 14)

# Поиск SFML
find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)

# Добавление исполняемого файла
add_executable(Python
src/Python.cpp
include/fileForLink.h
include/functionsFullProject.h
include/DrawingFunctions.h
include/GameInfo.h
include/ProcessingFunctions.h
include/CellClass.h
include/FieldClass.h
include/PlayerClass.h
include/SnakeClass.h
)

# Линковка с SFML
target_link_libraries(Python sfml-graphics sfml-window sfml-system)