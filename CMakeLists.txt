cmake_minimum_required(VERSION 2.8) #Проверка версии CMake
project(CImg_app) #Название проекта
set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}") #Установка ROOT_DIR
message("this CMAKE_CURRENT_SOURCE_DIR " ${CMAKE_CURRENT_SOURCE_DIR}) #Выводит значение CMAKE_CURRENT_SOURCE_DIR в консоль
set(ARCH "x64")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include) #Установка пути до заголовочных файлов
add_executable(main src/main.cpp include/CImg.h) #Создает исполняемый файл с именем main из исходника main.cpp и заголовочного файла