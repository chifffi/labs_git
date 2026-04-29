cmake_minimum_required(VERSION 3.10)
project(Lab2 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к папкам
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Список исходных файлов для библиотеки
set(LIB_SOURCES
    ${SOURCES_DIR}/mystring.cpp
    ${SOURCES_DIR}/basefile.cpp
    ${SOURCES_DIR}/base32file.cpp
    ${SOURCES_DIR}/rlefile.cpp
    ${SOURCES_DIR}/base32file2.cpp
    ${SOURCES_DIR}/rlefile2.cpp
)

# Заголовочные файлы
set(LIB_HEADERS
    ${SOURCES_DIR}/mystring.hpp
    ${SOURCES_DIR}/basefile.hpp
    ${SOURCES_DIR}/ifile.hpp
    ${SOURCES_DIR}/base32file.hpp
    ${SOURCES_DIR}/rlefile.hpp
    ${SOURCES_DIR}/base32file2.hpp
    ${SOURCES_DIR}/rlefile2.hpp
)

# Создание статической библиотеки
add_library(core STATIC ${LIB_SOURCES})

# Указание директории с заголовками
target_include_directories(core PUBLIC ${SOURCES_DIR})

# Исполняемый файл (основная программа)
add_executable(lab2 ${SOURCES_DIR}/lab2.cpp)

# подключение библиотеки к программе
target_link_libraries(lab2 core)

# подключение папки с тестами
add_subdirectory(tests)