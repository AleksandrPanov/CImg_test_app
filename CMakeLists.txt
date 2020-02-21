cmake_minimum_required(VERSION 2.8) #Проверка версии CMake
project(CImg_app) #Название проекта
set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}") #Установка ROOT_DIR
message("this CMAKE_CURRENT_SOURCE_DIR " ${CMAKE_CURRENT_SOURCE_DIR}) #Выводит значение CMAKE_CURRENT_SOURCE_DIR в консоль
set(ARCH "x64")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include) #Установка пути до заголовочных файлов
add_executable(test1 src/test1.cpp include/CImg.h) #Создает исполняемый файл с именем test1 из исходника test1.cpp и заголовочного файла
add_executable(test2 src/test2.cpp include/CImg.h) #Создает исполняемый файл с именем test2 из исходника test2.cpp и заголовочного файла