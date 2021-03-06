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


#ifndef VG_ENGINE_PRIVATELOG_HPP
#define VG_ENGINE_PRIVATELOG_HPP

#include "PublicLog.hpp"

// core log macros
#ifdef NDEBUG
#   define VG_CORE_TRACE
#   define VG_CORE_INFO
#   define VG_CORE_WARN
#   define VG_CORE_ERROR
#   define VG_CORE_CRITICAL
#else
#   define VG_CORE_TRACE(...)  ::VG::Log::getCoreLogger()->trace(__VA_ARGS__);
#   define VG_CORE_INFO(...)   ::VG::Log::getCoreLogger()->info(__VA_ARGS__);
#   define VG_CORE_WARN(...)   ::VG::Log::getCoreLogger()->warn(__VA_ARGS__);
#   define VG_CORE_ERROR(...)  ::VG::Log::getCoreLogger()->error(__VA_ARGS__);
#   define VG_CORE_CRITICAL(...)  ::VG::Log::getCoreLogger()->critical(__VA_ARGS__);
#endif
#define VG_CORE_TRACE_NOSTRIP(...)  ::VG::Log::getCoreLogger()->trace(__VA_ARGS__);
#define VG_CORE_INFO_NOSTRIP(...)   ::VG::Log::getCoreLogger()->info(__VA_ARGS__);
#define VG_CORE_WARN_NOSTRIP(...)   ::VG::Log::getCoreLogger()->warn(__VA_ARGS__);
#define VG_CORE_ERROR_NOSTRIP(...)  ::VG::Log::getCoreLogger()->error(__VA_ARGS__);
#define VG_CORE_CRITICAL_NOSTRIP(...)  ::VG::Log::getCoreLogger()->critical(__VA_ARGS__);



#endif //VG_ENGINE_PRIVATELOG_HPP
