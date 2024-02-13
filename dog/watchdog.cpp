/*
    Created by Mouse Zhang on 2024/2/8.
    This file is part of the watchdog project.

    SPDX-FileCopyrightText: 2024 Mouse Zhang <mousezhang7@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/
#include <string>

#include <grpcpp/server_builder.h>

#include "watchdog.h"
#include "watchdog_export.h"

class WatchDogPrivate {
public:
    std::string name_;
    std::string version_;
    std::string host_ { "0.0.0.0" };
    uint32_t port_ { 50051 };
};

WatchDogImpl::WatchDogImpl() : d { std::make_unique<WatchDogPrivate>() } {
    d->version_ = "0.0.1";
}

grpc::Status WatchDogImpl::FeedDog(grpc::ServerContext* context, const FeedDogRequest* request, FeedDogResponse* response) {
    std::cout << "request has food: " << request->has_food() << std::endl;
    if (request->has_food()) {
        std::cout << "request->food(): " << request->food() << std::endl;
        d->name_ = request->food();
        response->set_message(d->name_);
    }
    return grpc::Status::OK;
}

int dog_main(int argc, char* argv[]) {
    std::ios::sync_with_stdio(false);
    WatchDogImpl watchdog;
    grpc::ServerBuilder builder;
    std::string server_address { "0.0.0.0:12345" };
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&watchdog);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
    return 0;
}
