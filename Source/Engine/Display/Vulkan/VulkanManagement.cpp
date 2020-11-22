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
#include <map>
#include "../DisplaysAPI.hpp"
#include <optional>

namespace VG{

    std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
    };

#ifdef NDEBUG
    bool enableValidationLayers = false;
#else
    bool enableValidationLayers = true;
#endif

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {

        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }else{
            VG_CORE_CRITICAL_NOSTRIP("DestroyDebugUtilsMessengerEXT requested but not found");
        }
    }

    void GraphicsInstance::createInstance(const std::string &applicationName, uint32_t appVersion_major,
                                          uint32_t appVersion_minor, uint32_t appVersion_patch) {


        /* Make sure validation layers are available */
        if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

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

        /* let vulkan decide if validation layers should be enabled */
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;

        } else {

            createInfo.enabledLayerCount = 0;

            createInfo.pNext = nullptr;

        }

        /* handle extensions */
        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        /* Create the instance */
        VULKAN_CALL(vkCreateInstance(&createInfo, nullptr, &instance));

    }

    void GraphicsInstance::setupDebugMessenger() {

        if(!enableValidationLayers) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        populateDebugMessengerCreateInfo(createInfo);

        if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
            VG_CORE_CRITICAL_NOSTRIP("Failed to set up debug messenger!");
            throw std::runtime_error("failed to set up debug messenger!");
        }

    }

    void GraphicsInstance::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo) {

        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;

    }

    void GraphicsInstance::pickPhysicalDevice() {

        VG_CORE_INFO("Finding number of suitable GPUs with Vulkan.");

        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        VG_CORE_INFO_NOSTRIP("Found {} GPU that supports Vulkan. Finding which is most suitable.", deviceCount);

        if(deviceCount == 0){
            VG_CORE_CRITICAL_NOSTRIP("No suitable GPU for Vulkan Rendering!");
            throw std::runtime_error("Failed to find GPU with Vulkan Support!");
        }

        /* Rate suitability of all devices */
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
        std::multimap<int, VkPhysicalDevice> candidates;

        for (const auto& device : devices) {
            int score = rateDeviceSuitability(device);
            candidates.insert(std::make_pair(score,device));
        }

        /* Find most suitable GPU */
        if(candidates.rbegin()->first > 0){
            physicalDevice = candidates.rbegin()->second;
        }else{
            goto VG_VK_NO_GPU;
        }

        if(physicalDevice == VK_NULL_HANDLE){

            VG_VK_NO_GPU:
            VG_CORE_CRITICAL_NOSTRIP("Failed to find a suitable GPU, but a GPU was found.");
            throw std::runtime_error("Filed to find a suitable GPU, but a GPU was found");

        }

        {
            VkPhysicalDeviceProperties deviceProperties;
            vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
            VG_CORE_INFO_NOSTRIP("Selected {} as the GPU", deviceProperties.deviceName);
        }

    }

    void GraphicsInstance::createLogicalDevice() {

        /* Create a queue family from the required indices */
        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
        float queuePriority = 1.0f;

        /* mention the queues we need */
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        /* mention the features we need */
        VkPhysicalDeviceFeatures deviceFeatures{};

        /* Actually create the logical device */
        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = &queueCreateInfo;
        createInfo.queueCreateInfoCount = 1;

        createInfo.pEnabledFeatures = &deviceFeatures;

        /* Even though these are now ignored, the tutorial suggusted that I do this */
        createInfo.enabledExtensionCount = 0;

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        VULKAN_CALL(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device));

        /* and lastly create the graphics queue */
        vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);

    }

    bool GraphicsInstance::checkValidationLayerSupport() {
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

    VKAPI_ATTR VkBool32 VKAPI_CALL VG::GraphicsInstance::debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData) {

        if(messageSeverity > VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            VG_CORE_CRITICAL_NOSTRIP("validation layer: {}",pCallbackData->pMessage);
        }

        return VK_FALSE;
    }

    QueueFamilyIndices GraphicsInstance::findQueueFamilies(VkPhysicalDevice device) {

        struct QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
        VG_CORE_INFO_NOSTRIP("Querying Queue Families. {} found.", queueFamilyCount);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            if(indices.isComplete()){
                break;
            }

            i++;
        }

        return indices;
    }

    int GraphicsInstance::rateDeviceSuitability(VkPhysicalDevice device) {

        /* Ask driver for properties */
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        /* Ask driver for features */
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        int score = 0;

        /* Discrete GPUs have a significant performance advantage */
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            score += 1000;
        }

        /* Maximum possible size of textures affects graphics quality */
        score += deviceProperties.limits.maxImageDimension2D;

        VG_CORE_INFO("GPU {} has score of {}.", deviceProperties.deviceName, score);

        /* Application can't function without geometry shaders */
        if (!deviceFeatures.geometryShader) {
            return 0;
        }

        return score;

    }

    bool GraphicsInstance::isDeviceSuitable(VkPhysicalDevice device) {
        if(!findQueueFamilies(device).isComplete()){
            VG_CORE_CRITICAL_NOSTRIP("Could not find queues");
            return false;
        }
        return true;
    }

    VG::GraphicsInstance::~GraphicsInstance() {

        vkDestroyDevice(device, nullptr);

        if(enableValidationLayers){
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }
        vkDestroyInstance(instance, nullptr);

    }

    void GraphicsInstance::initVulkan(const std::string &applicationName, uint32_t appVersion_major,
                                      uint32_t appVersion_minor, uint32_t appVersion_patch) {

        createInstance(applicationName, appVersion_major, appVersion_minor, appVersion_patch);
        setupDebugMessenger();
        pickPhysicalDevice();
        createLogicalDevice();

    }




}