//
// Created by Illia Ilin on 07.04.2021.
//

#ifndef KEEPALIVETEST__HELLOSERVICE_H_
#define KEEPALIVETEST__HELLOSERVICE_H_

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "KeepAliveService.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using test::Request;
using test::Response;

class GreeterServiceImpl final : public test::TestService::Service {
    Status test(ServerContext* context, const Request* request,
                    grpc::ServerWriter<Response>* server_writer) override;
};

void RunServer();

#endif //KEEPALIVETEST__HELLOSERVICE_H_
