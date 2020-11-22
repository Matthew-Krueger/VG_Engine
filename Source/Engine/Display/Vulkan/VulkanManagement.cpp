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

#include <sstream>
#include "../DisplaysAPI.hpp"

namespace VG{

    void GraphicsInstance::createInstance(const std::string &applicationName, uint32_t appVersion_major,
                                          uint32_t appVersion_minor, uint32_t appVersion_patch) {


        /* Create information about our application */
        VG_CORE_INFO_NOSTRIP("Creating new Vulkan Application Info for Application: {} - V{}.{}.{}\n\twith Engine {} - V{}.{}.{} using Vulkan API: V{}",
                             applicationName, appVersion_major, appVersion_minor, appVersion_patch, VG_ENGINE_NAME, VG_VERSION_MAJOR, VG_VERSION_MINOR, VG_VERSION_PATCH, "1.0");
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = applicationName.c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(appVersion_major, appVersion_minor, appVersion_patch);
        appInfo.pEngineName = VG_ENGINE_NAME;
        appInfo.engineVersion = VK_MAKE_VERSION(VG_VERSION_MAJOR,VG_VERSION_MINOR,VG_VERSION_PATCH);
        appInfo.apiVersion = VK_API_VERSION_1_0;


        /* Define Create info of the instance */
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        /* let GLFW handle extensions */
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        /* disable layers */
        createInfo.enabledLayerCount = 0;

        /* Create the instance */
        VULKAN_CALL(vkCreateInstance(&createInfo, nullptr, &instance));

    }

    VG::GraphicsInstance::~GraphicsInstance() {

        vkDestroyInstance(instance, nullptr);

    }

    void GraphicsInstance::initVulkan(const std::string &applicationName, uint32_t appVersion_major,
                                      uint32_t appVersion_minor, uint32_t appVersion_patch) {

        createInstance(applicationName, appVersion_major, appVersion_minor, appVersion_patch);

    }


}