cmake_minimum_required(VERSION 3.20)



project(Spider)

add_subdirectory("C:\\Users\\PC\\Desktop\\work\\libpqxx-7.8.1" libpqxx-build)
set(CMAKE_TOOLCHAIN_FILE "C:/Users/PC/Desktop/work/vcpkg-master/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")


find_package(CURL REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread system locale ) # Укажите необходимые компоненты

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(Spider main.cpp "ini_parser.h" "ini_parser.cpp" "BD.h" "BD.cpp" "Indexator.cpp" "Indexator.h" "ThreedPool.cpp" "ThreedPool.h" "URLQueue.h"  "URLQueue.cpp" "Spider.h" "Spider.cpp")  # Замените на имя вашего файла
    target_link_libraries(Spider ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Boost not found!")
endif()

target_compile_features (Spider PRIVATE cxx_std_17)

target_link_libraries(Spider pqxx CURL::libcurl)

