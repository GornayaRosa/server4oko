include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
# protobuf_generate_cpp(CONFIG_SRC CONFIG_HEADER config.proto)
#   headers configured with command:
#   $ protoc --cpp_out=. config.proto
add_library(config config.pb.h config.pb.cc)