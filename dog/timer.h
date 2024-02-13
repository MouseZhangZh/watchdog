/*
    Created by Mouse Zhang on 2024/2/13.
    This file is part of the watchdog project.

    SPDX-FileCopyrightText: 2024 Mouse Zhang <mousezhang7@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <chrono>
#include <functional>
#include <condition_variable>

class TimerPrivate;

class Timer {
public:
    Timer(const std::chrono::milliseconds& interval,
        const std::function<void ()>& callback,
        bool single_shot = false);
    ~Timer();

    void start() const;
    void stop() const;
    void set_single_shot(bool single_shot = true) const;
    [[nodiscard("why you use is_running?")]] bool is_running() const;

private:

    std::unique_ptr<TimerPrivate> d;
};
