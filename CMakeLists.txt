cmake_minimum_required(VERSION 3.25)
project(iotAPI)

set(CMAKE_CXX_STANDARD 17)

include_directories("/usr/include/mariadb")
link_directories("/usr/local/lib/mariadb")
add_library(mariadbcpp STATIC IMPORTED)
set_property(TARGET mariadbcpp PROPERTY IMPORTED_LOCATION "/usr/local/lib/mariadb/libmariadbcpp.so")

set(JWT_BUILD_EXAMPLES OFF)
include_directories("/usr/local/include/jwt-cpp")
add_library(jwt-cpp STATIC IMPORTED)
set_property(TARGET jwt-cpp PROPERTY IMPORTED_LOCATION "/usr/local/include/jwt-cpp/jwt.h")

add_executable(iotAPI main.cpp aux/tools.cpp aux/tools.h aux/middleware.cpp aux/middleware.h)

target_link_libraries(iotAPI mariadbcpp jwt-cpp)

