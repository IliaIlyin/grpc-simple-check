//
// Created by Illia Ilin on 07.04.2021.
//

#ifndef KEEPALIVETEST__HELLOCLIENT_H_
#define KEEPALIVETEST__HELLOCLIENT_H_

#include "KeepAliveService.grpc.pb.h"
#include <grpcpp/grpcpp.h>

class HelloClient
{
public:
    HelloClient(std::shared_ptr<grpc::Channel> channel);

    void RunClient();

private:
    std::unique_ptr<test::TestService::Stub> stub_;
};

#endif //KEEPALIVETEST__HELLOCLIENT_H_
