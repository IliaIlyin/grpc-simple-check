//
// Created by Illia Ilin on 07.04.2021.
//

#include "HelloClient.h"

void HelloClient::RunClient()
{
    test::Response stream;
    auto request = test::Request();
    request.set_id(3);
    std::unique_ptr<grpc::ClientReader<test::Response>> reader;

        grpc::ClientContext context;
        //      std::chrono::system_clock::time_point timePoint(std::chrono::system_clock::now() + std::chrono::seconds(30));
        //    context_->set_deadline(timePoint);

        assert(stub_);
        reader = stub_->test(&context, request);
        /*
         * ToFix: We want to read forever and drop out only if stop_ is true. Meanwhile, if we dropped out of the reader,
         * we have to check whether the context_ deadline has ended or the connection has broken. If the deadline has ended,
         * reconnection is not needed, only reader->Read request should be provided.
         * Suggested solution: wrap this while into
         * while(!stop && CheckChannelReadiness(channel_))
         */

        while (reader->Read(&stream))
        {
            std::cout << "Received response, id: " << stream.id() << std::endl;
        }

}

HelloClient::HelloClient(std::shared_ptr<grpc::Channel> channel)
{
    stub_ = test::TestService::NewStub(channel);
}
