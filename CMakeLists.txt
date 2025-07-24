cmake_minimum_required(VERSION 3.10)
project(PhotoEditor)

set(CMAKE_CXX_STANDARD 17)

# Указываем директорию для заголовочных файлов
include_directories(include)

# Добавляем все исходники проекта
set(SOURCES
    src/main.cpp
    src/filter_parser.cpp
    src/image_processing.cpp
)

# Создаём исполняемый файл
add_executable(PhotoEditor ${SOURCES})
