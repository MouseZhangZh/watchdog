include(../common/common.cmake)

get_filename_component(dog_proto "watchdog.proto" ABSOLUTE)
get_filename_component(dog_proto_path "${dog_proto}" PATH)

message("${dog_proto}")
message("${dog_proto_path}")

set(dog_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/watchdog.pb.cc")
set(dog_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/watchdog.pb.h")
set(dog_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/watchdog.grpc.pb.cc")
set(dog_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/watchdog.grpc.pb.h")

add_custom_command(
        OUTPUT "${dog_proto_srcs}" "${dog_proto_hdrs}" "${dog_grpc_srcs}" "${dog_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${dog_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${dog_proto}"
        DEPENDS "${dog_proto}")

include_directories("${CMAKE_CURRENT_BINARY_DIR}")
include_directories(../common)

add_library(dog_grpc_proto
        SHARED
        ${dog_grpc_srcs}
        ${dog_grpc_hdrs}
        ${dog_proto_srcs}
        ${dog_proto_hdrs})

target_link_libraries(dog_grpc_proto
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})

add_library(dog
        SHARED
        watchdog.cpp)

target_link_libraries(dog
        dog_grpc_proto)

add_executable(watchdog
        main.cpp)

target_link_libraries(watchdog dog)

if (BUILD_TEST)
    add_executable(feeder feeder.cpp)
    target_link_libraries(feeder
            dog_grpc_proto)
else ()
    message("If you want to build feeder, set BUILD_TEST ON")
endif ()