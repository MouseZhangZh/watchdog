/*
    Created by Mouse Zhang on 2024/2/12.
    This file is part of the watchdog project.

    SPDX-FileCopyrightText: 2024 Mouse Zhang <mousezhang7@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

class ConfigHelper {
public:
    static ConfigHelper& GetInstance() {
        static ConfigHelper instance;
        return instance;
    }

};
