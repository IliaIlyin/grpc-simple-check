cmake_minimum_required(VERSION 3.17)
project(KeepAliveTest)

set(CMAKE_CXX_STANDARD 14)

set(PROTO_DIR ${PROJECT_SOURCE_DIR}/proto)
file(GLOB PROTO_SOURCES CONFIGURE_DEPENDS ${PROTO_DIR}/*.proto)

find_package(gRPC REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")
find_package(OpenSSL REQUIRED)

set(GENERATED_DIR    ${CMAKE_CURRENT_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_DIR})

include_directories(${GENERATED_DIR})
include_directories(${Protobuf_INCLUDE_DIRS})

find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin REQUIRED)


macro(compile_proto_file filename output_dir)
    get_filename_component(dirname ${filename} DIRECTORY)
    get_filename_component(basename ${filename} NAME_WE)

    add_custom_command(
            OUTPUT ${output_dir}/${basename}.pb.cc ${output_dir}/${basename}.grpc.pb.cc
            COMMAND ${Protobuf_PROTOC_EXECUTABLE} ${filename}
            --cpp_out=${output_dir}
            --grpc_out=${output_dir}
            --plugin=protoc-gen-grpc=${_GRPC_CPP_PLUGIN_EXECUTABLE}
            -I ${dirname}
            DEPENDS ${filename}
            VERBATIM
    )
    set(proto_generated_files ${proto_generated_files} ${output_dir}/${basename}.pb.cc ${output_dir}/${basename}.grpc.pb.cc)
endmacro(compile_proto_file)

macro(compile_proto_dir generated_cpp_dir file_list)
    foreach(proto_file ${file_list})
        message("working on ${proto_file}")
        compile_proto_file(${proto_file} ${generated_cpp_dir})
    endforeach(proto_file)
endmacro(compile_proto_dir)

SET_SOURCE_FILES_PROPERTIES(${proto_generated_files} PROPERTIES GENERATED TRUE)

compile_proto_dir(${GENERATED_DIR} "${PROTO_SOURCES}")
add_library(proto_files STATIC ${proto_generated_files})
target_include_directories(proto_files PRIVATE ${GRPC_ROOT}/include)

add_executable(KeepAliveTest main.cpp)

target_link_libraries(KeepAliveTest
        ${OPENSSL_LIBRARIES}
        ${OPENSSL_CRYPTO_LIBRARY}
        ${proto_files}
        proto_files gRPC::grpc++
        gRPC::grpc++_reflection
        )

add_executable(ServerTest ServiceMain.cpp HelloService.cpp)
target_link_libraries(ServerTest
        ${OPENSSL_LIBRARIES}
        ${OPENSSL_CRYPTO_LIBRARY}
        ${proto_files}
        proto_files gRPC::grpc++
        gRPC::grpc++_reflection
        )

add_executable(ClientTest ClientMain.cpp HelloClient.cpp)
target_link_libraries(ClientTest
        ${OPENSSL_LIBRARIES}
        ${OPENSSL_CRYPTO_LIBRARY}
        ${proto_files}
        proto_files gRPC::grpc++
        gRPC::grpc++_reflection
        )