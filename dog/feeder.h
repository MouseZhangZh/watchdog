/*
    Created by Mouse Zhang on 2024/2/8.
    This file is part of the watchdog project.

    SPDX-FileCopyrightText: 2024 Mouse Zhang <mousezhang7@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <memory>

#include "watchdog.grpc.pb.h"

class Feeder{
public:
    Feeder(std::shared_ptr<grpc::ChannelInterface> channel);
    ~Feeder() = default;

    void FeedDog();

private:
    std::unique_ptr<WatchDog::Stub> stub_;
};
