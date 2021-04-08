//
// Created by Illia Ilin on 07.04.2021.
//

#include "HelloService.h"

#include <chrono>
#include <ctime>
#include <memory>
#include <thread>

void RunServer()
{
    std::string server_address("0.0.0.0:50051");
    GreeterServiceImpl service;

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.AddChannelArgument(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA,0);
    builder.AddChannelArgument(GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS,5000);
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}


Status GreeterServiceImpl::test(ServerContext* context, const Request* request, grpc::ServerWriter<Response>* server_writer)
{
    int i=0;
    while(true)
    {
/*
        Response resp;
        resp.set_id(i++);
        server_writer->Write(resp);
      */
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    return Status::OK;
}
