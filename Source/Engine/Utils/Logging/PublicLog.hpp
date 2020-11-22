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

/* This file is also used for private log, but I don't care, so, it goes here. */


#ifndef VG_ENGINE_PUBLICLOG_HPP
#define VG_ENGINE_PUBLICLOG_HPP

#include <spdlog/spdlog.h>
#include "../../Win32Exports.hpp"

namespace VG{


    class VG_API Log{
    private:
        static std::shared_ptr<spdlog::logger> coreLogger;
        static std::shared_ptr<spdlog::logger> clientLogger;

    public:
        static void Init(const std::string& filePath);

        inline static std::shared_ptr<spdlog::logger>& getCoreLogger(){ return coreLogger; }
        inline static std::shared_ptr<spdlog::logger>& getClientLogger(){ return clientLogger; }

    };

}

// client log macros
#ifdef NDEBUG
#   define VG_TRACE
#   define VG_INFO
#   define VG_WARN
#   define VG_ERROR
#   define VG_CRITICAL
#else
#   define VG_TRACE(...)       ::VG::Log::getClientLogger()->trace(__VA_ARGS__);
#   define VG_INFO(...)        ::VG::Log::getClientLogger()->info(__VA_ARGS__);
#   define VG_WARN(...)        ::VG::Log::getClientLogger()->warn(__VA_ARGS__);
#   define VG_ERROR(...)       ::VG::Log::getClientLogger()->error(__VA_ARGS__);
#   define VG_CRITICAL(...)       ::VG::Log::getClientLogger()->critical(__VA_ARGS__);
#endif

#define VG_TRACE_NOSTRIP(...)       ::VG::Log::getClientLogger()->trace(__VA_ARGS__);
#define VG_INFO_NOSTRIP(...)        ::VG::Log::getClientLogger()->info(__VA_ARGS__);
#define VG_WARN_NOSTRIP(...)        ::VG::Log::getClientLogger()->warn(__VA_ARGS__);
#define VG_ERROR_NOSTRIP(...)       ::VG::Log::getClientLogger()->error(__VA_ARGS__);
#define VG_FATAL_CRITICAL(...)       ::VG::Log::getClientLogger()->critical(__VA_ARGS__);



#endif //VG_ENGINE_PUBLICLOG_HPP
