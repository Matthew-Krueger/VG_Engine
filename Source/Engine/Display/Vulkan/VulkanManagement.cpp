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

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            VG_CORE_ERROR_NOSTRIP("Vulkan CreateDebugUtilsMessengerEXT not present but requested");
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }else{
            VG_CORE_ERROR_NOSTRIP("Vulkan DestroyDebugUtilsMessengerEXT not present but requested.");
        }
    }

    /*static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData) {

        //std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
        switch(messageSeverity){
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                VG_CORE_WARN_NOSTRIP("Validation Layer warning: {}", pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                VG_CORE_INFO("Validation Layer info: {}", pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                VG_CORE_ERROR_NOSTRIP("Validation Layer error: {}", pCallbackData->pMessage);
                break;
            default:
                (void(0));
        }

        return VK_FALSE;
    }*/

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData) {

        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }

    #ifdef NDEBUG
        bool enableValidationLayers = false;
    #else
        bool enableValidationLayers = true;
    #endif

    GraphicsInstance::GraphicsInstance(const std::string& applicationName, uint32_t appVersion_major, uint32_t appVersion_minor, uint32_t appVersion_patch, std::vector<const char*> validationLayers){

        if(enableValidationLayers){
            VG_CORE_INFO("Validation layers requested. Checking with driver to make sure they are available");
        }

        if(enableValidationLayers && !checkValidationLayerSupport()){
            VG_CORE_CRITICAL_NOSTRIP("Validation layers requested, but not available.");
        }

        instance = nullptr;
        debugMessenger = nullptr;

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

        /* Create information about our info (why, I don't know. They told me to */
        auto requiredExtentions = getRequiredExtensions();
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtentions.size());
        createInfo.ppEnabledExtensionNames = requiredExtentions.data();
        if(enableValidationLayers){
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }else{
            createInfo.enabledLayerCount = 0;
        }

        /* Get the window layer extensions from GLFW */
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        /* set the create info to include Extensions */
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        /* Disbale all validation layers */
        //createInfo.enabledLayerCount = 0;

        VULKAN_CALL(vkCreateInstance(&createInfo, nullptr, &instance));

        setupDebugMessanger();

        /*{
            VG_CORE_INFO_NOSTRIP("Asking driver for supported extensions");
            uint32_t extensionCount = 0;
            vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
            std::vector<VkExtensionProperties> extensions(extensionCount);
            vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
            std::ostringstream oss;
            oss << '\n';
            for(const auto& extension:extensions){
                oss << '\t' << extension.extensionName<<'\n';
            }

            VG_CORE_INFO_NOSTRIP("Available extensions: {}", oss.str());
        }*/

    }

    GraphicsInstance::~GraphicsInstance() {

        if (enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }

        VG_CORE_TRACE("Deleting Graphics Interface");
        vkDestroyInstance(instance, nullptr);



    }

    void GraphicsInstance::setupDebugMessanger() {

        if(!enableValidationLayers) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr; // Optional

        if(CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS){
            VG_CORE_ERROR_NOSTRIP("Failed to set up debug messenger");
        }

    }

    void GraphicsInstance::addValidationLayer(const char *) {

    }

    std::vector<const char *> GraphicsInstance::getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    bool GraphicsInstance::checkValidationLayerSupport() const{

        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;

    }

}