set(MODULE_NAME ${PROJECT_NAME})

add_library(${MODULE_NAME} SHARED  "Win32Exports.hpp" "include/VG_Engine/Core.hpp" "Display/WindowManagement.cpp" "Display/DisplaysAPI.hpp" Utils/UtilsAPI.hpp Utils/InitScripts.cpp Utils/PCH.hpp Utils/PCH.cpp Utils/EngineManagement.cpp ../EngineTests/TestMain.cpp ../EngineTests/PCH.cpp ../EngineTests/PCH.hpp EngineGlobals.hpp EngineExceptions.hpp Display/Vulkan/VulkanManagement.cpp Utils/Logging/PublicLog.hpp Utils/Logging/PrivateLog.hpp Utils/Logging/LoggingFunctions.cpp)
add_dependencies(${MODULE_NAME} glfw STB_LIB spdlog)
target_link_libraries(${MODULE_NAME} glfw STB_LIB ${VULKAN_LIB_LIST} spdlog)

target_compile_definitions("${MODULE_NAME}" PRIVATE VG_BUILD_LIBRARY)
target_compile_definitions("${MODULE_NAME}" PRIVATE VG_VERSION_MAJOR=${VG_VERSION_MAJOR})
target_compile_definitions("${MODULE_NAME}" PRIVATE VG_VERSION_MINOR=${VG_VERSION_MINOR})
target_compile_definitions("${MODULE_NAME}" PRIVATE VG_VERSION_PATCH=${VG_VERSION_PATCH})
target_compile_definitions("${MODULE_NAME}" PRIVATE VG_ENGINE_NAME="${PROJECT_NAME}")

target_precompile_headers("${MODULE_NAME}" PRIVATE Utils/PCH.hpp)

set_target_properties(${MODULE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/
        )
