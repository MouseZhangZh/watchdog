/*
    Created by Mouse Zhang on 2024/2/13.
    This file is part of the watchdog project.

    SPDX-FileCopyrightText: 2024 Mouse Zhang <mousezhang7@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/
#include <atomic>
#include <thread>

#include "timer.h"

class TimerPrivate {
public:
    std::chrono::milliseconds interval_{};
    std::function<void ()> callback_;
    std::atomic_bool single_shot_{};
    std::atomic_bool running_{};
    std::mutex mutex_for_condition_;
    std::mutex mutex_for_stop_;
    std::condition_variable condition_;
    std::thread thread_;
};

Timer::Timer(const std::chrono::milliseconds& interval, const std::function<void()>& callback, bool single_shot)
    : d(std::make_unique<TimerPrivate>()) {
    d->interval_ = interval;
    d->callback_ = callback;
    d->single_shot_ = single_shot;
    d->running_ = false;
}

Timer::~Timer() {
    stop();
}

void Timer::start() const {
    stop();
    d->running_ = true;
    d->thread_ = std::thread([this] {
        while (d->running_) {
            std::unique_lock<std::mutex> lock(d->mutex_for_condition_);
            if (const bool wait_res = d->condition_.wait_for(lock, d->interval_, [this] { return !d->running_; });
                d->running_ && !wait_res) {
            d->callback_();
            }
            if (d->single_shot_) {
                d->running_ = false;
            }
        }
    });
}

void Timer::stop() const {
    std::unique_lock<std::mutex> lock(d->mutex_for_stop_);
    d->running_ = false;
    d->condition_.notify_all();
    if (d->thread_.joinable()) {
        d->thread_.join();
    }
}

void Timer::set_single_shot(const bool single_shot) const {
    d->single_shot_ = single_shot;
}

bool Timer::is_running() const {
    return d->running_;
}