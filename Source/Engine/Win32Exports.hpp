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

#ifndef WIN32EXPORTS_VG_ENGINE
#define WIN32EXPORTS_VG_ENGINE

#if defined _WIN32 || defined __CYGWIN__
#   ifdef VG_BUILD_LIBRARY
// Exporting...
#       ifdef __GNUC__
#           define VG_API __attribute__ ((dllexport))
#       else
#           define VG_API __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#       endif
#   else
#       ifdef __GNUC__
#           define VG_API __attribute__ ((dllimport))
#       else
#           define VG_API __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#       endif
#   endif
#   define VG_API_HIDDEN
#else
#   if __GNUC__ >= 4
#       define VG_API __attribute__ ((visibility ("default"))) extern
#       define VG_API_HIDDEN  __attribute__ ((visibility ("hidden")))
#   else
#       define VG_API
#       define VG_API_HIDDEN
#       error Problem configuring
#   endif
#endif

#endif