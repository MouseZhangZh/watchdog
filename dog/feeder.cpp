/*
    Created by Mouse Zhang on 2024/2/8.
    This file is part of the watchdog project.

    SPDX-FileCopyrightText: 2024 Mouse Zhang <mousezhang7@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/
#include <grpcpp/create_channel.h>

#include "feeder.h"

Feeder::Feeder(std::shared_ptr<grpc::ChannelInterface> channel)
    : stub_(WatchDog::NewStub(channel)) {
}

void Feeder::FeedDog(const std::string_view& food) {
    grpc::ClientContext context;
    FeedDogRequest request;
    FeedDogResponse response;
    request.set_food(food.data());
    if (stub_->FeedDog(&context, request, &response).ok()) {
        std::cout << "feed dog response message: " << response.message() << std::endl;
    } else {
        std::cout << "feed dog failed" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::ios::sync_with_stdio(false);
    Feeder feeder {
        grpc::CreateChannel("0.0.0.0:12345", grpc::InsecureChannelCredentials())
    };
    feeder.FeedDog("just input your food after the command.");
    for (int i = 1; i < argc; ++i) {
        feeder.FeedDog(argv[i]);
    }
    feeder.FeedDog("feed end.");
    return 0;
}
