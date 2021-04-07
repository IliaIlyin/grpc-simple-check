//
// Created by Illia Ilin on 07.04.2021.
//
#include <string>
#include <iostream>

#include "KeepAliveService.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include "HelloClient.h"

int main(int argc, char** argv) {
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint specified by
    // the argument "--target=" which is the only expected argument.
    // We indicate that the channel isn't authenticated (use of
    // InsecureChannelCredentials()).
        std::string target_str = "localhost:50051";
        const int kKeepAliveTimeMs = 5000; //5 sec.
        const int kKeepAliveTimeoutMs = 5000;//5 sec
        const int kReconnectBackoffMs = 10000;//10 sec

        grpc::ChannelArguments args;
        args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, kKeepAliveTimeMs);
        args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, kKeepAliveTimeoutMs);
        args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);
        args.SetInt(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA, 0);
        args.SetInt(GRPC_ARG_ENABLE_RETRIES,0);
        args.SetInt(GRPC_ARG_MIN_RECONNECT_BACKOFF_MS, kReconnectBackoffMs);
        args.SetInt(GRPC_ARG_MAX_RECONNECT_BACKOFF_MS, kReconnectBackoffMs);

     HelloClient greeter(
        grpc::CreateCustomChannel(target_str, grpc::InsecureChannelCredentials(),args));

    greeter.RunClient();

    return 0;
}