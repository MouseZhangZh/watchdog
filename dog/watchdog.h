/*
    Created by Mouse Zhang on 2024/2/8.
    This file is part of the watchdog project.

    SPDX-FileCopyrightText: 2024 Mouse Zhang <mousezhang7@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "watchdog.grpc.pb.h"

class WatchDogPrivate;

class WatchDogImpl final : public WatchDog::Service {
public:
    WatchDogImpl();
    ~WatchDogImpl() = default;

    grpc::Status FeedDog(grpc::ServerContext* context, const FeedDogRequest* request, FeedDogResponse* response) override;

private:
    std::unique_ptr<WatchDogPrivate> d;
};

