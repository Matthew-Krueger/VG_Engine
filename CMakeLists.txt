#####################################################################################
#  VG Engine is licensed under a BSD 3-Clause License                               #
#                                                                                   #
#  BSD 3-Clause License                                                             #
#                                                                                   #
#  Copyright (c) 2020, Matthew Krueger                                              #
#  All rights reserved.                                                             #
#                                                                                   #
#  Redistribution and use in source and binary forms, with or without               #
#  modification, are permitted provided that the following conditions are met:      #
#                                                                                   #
#  1. Redistributions of source code must retain the above copyright notice, this   #
#  list of conditions and the following disclaimer.                                 #
#                                                                                   #
#  2. Redistributions in binary form must reproduce the above copyright notice,     #
#  this list of conditions and the following disclaimer in the documentation        #
#  and/or other materials provided with the distribution.                           #
#                                                                                   #
#  3. Neither the name of the copyright holder nor the names of its                 #
#  contributors may be used to endorse or promote products derived from             #
#  this software without specific prior written permission.                         #
#                                                                                   #
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"      #
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE        #
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE   #
#  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE     #
#  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL       #
#  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR       #
#  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER       #
#  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,    #
#  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    #
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.             #
#####################################################################################
cmake_minimum_required(VERSION 3.16.3)
project(VG_Engine C CXX)

set(VG_VERSION_MAJOR "0")
set(VG_VERSION_MINOR "0")
set(VG_VERSION_PATCH "0")
set(VG_VERSION_TWEAK "1")
set(VG_VERSION "${VG_VERSION_MAJOR}.${VG_VERSION_MINOR}")
set(VG_VERSION_FULL "${VG_VERSION}.${VG_VERSION_PATCH}-${VG_VERSION_TWEAK}")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


##############################
#     Build Dependencies     #
##############################
add_subdirectory(Dependencies/GLFW)
include_directories(Dependencies/GLFW/include)

add_subdirectory(Dependencies/STB)
include_directories(Dependencies/STB/include)

##############################
#       Build Engine DLL     #
##############################
add_subdirectory(Source/Engine)

##############################
#      Build Application     #
##############################
add_subdirectory(Source/VKGame)