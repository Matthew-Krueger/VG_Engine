/************************************************************************************
* VG Engine is licensed under a BSD 3-Clause License                                *
*                                                                                   *
* BSD 3-Clause License                                                              *
*                                                                                   *
* Copyright (c) 2020, Matthew Krueger                                               *
* All rights reserved.                                                              *
*                                                                                   *
* Redistribution and use in source and binary forms, with or without                *
* modification, are permitted provided that the following conditions are met:       *
*                                                                                   *
* 1. Redistributions of source code must retain the above copyright notice, this    *
*    list of conditions and the following disclaimer.                               *
*                                                                                   *
* 2. Redistributions in binary form must reproduce the above copyright notice,      *
*    this list of conditions and the following disclaimer in the documentation      *
*    and/or other materials provided with the distribution.                         *
*                                                                                   *
* 3. Neither the name of the copyright holder nor the names of its                  *
*    contributors may be used to endorse or promote products derived from           *
*    this software without specific prior written permission.                       *
*                                                                                   *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"       *
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE         *
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE    *
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE      *
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL        *
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR        *
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER        *
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,     *
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE     *
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.              *
************************************************************************************/

#include "PublicLog.hpp"
#include "PrivateLog.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace VG{

    std::shared_ptr<spdlog::logger> Log::coreLogger;
    std::shared_ptr<spdlog::logger> Log::clientLogger;

    void Log::Init(const std::string& filePath) {

        //spdlog::set_pattern("%^[%T] %n: %v%$");
        //coreLogger = spdlog::stdout_color_mt("f");


        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filePath);
        file_sink->set_level(spdlog::level::trace);
        file_sink->set_pattern("%^[%T] %n: %v%$");
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::trace);
        console_sink->set_pattern("%^[%T] %n: %v%$");

        coreLogger = std::make_shared<spdlog::logger>(VG_ENGINE_NAME, spdlog::sinks_init_list{console_sink, file_sink});
        clientLogger = std::make_shared<spdlog::logger>("Client", spdlog::sinks_init_list{console_sink, file_sink});

        /*{
            auto core_console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            core_console_sink->set_level(spdlog::level::trace);
            core_console_sink->set_pattern("%^[%T] %n: %v%$");

            coreLogger = std::make_shared<spdlog::logger>(VG_ENGINE_NAME, spdlog::sinks_init_list{core_console_sink, file_sink});
        }

        {
            auto client_console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            client_console_sink->set_level(spdlog::level::trace);
            client_console_sink->set_pattern("%^[%T] %n: %v%$");

            clientLogger = std::make_shared<spdlog::logger>("Client", spdlog::sinks_init_list{client_console_sink, file_sink});
        }*/

    }

}
