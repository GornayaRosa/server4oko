cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
add_definitions(-std=c++11)
project(server4oko)
include_directories(/usr/include/openssl)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(.)
include_directories(src)
add_subdirectory(config)
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

find_package(OpenSSL REQUIRED)
set(EXECUTABLE_OUTPUT_PATH bin)
set(CMAKE_C_FLAGS "-lssl -lcrypto -D MG_ENABLE_OPENSSL=1 -lprotobuf -pthread")
add_executable(server4oko
        src/main.cpp
        src/mongoose.h
        src/mongoose.c
        src/Params.cpp
        src/Params.h
        src/APIv1.cpp
        src/APIv1.h
        src/HomvHandler.cpp
        src/HomvHandler.h
)
target_link_libraries(server4oko config ${Protobuf_LIBRARIES} OpenSSL::SSL OpenSSL::Crypto)