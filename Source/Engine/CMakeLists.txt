set(MODULE_NAME ${PROJECT_NAME})

add_library(${MODULE_NAME} SHARED  "Win32Exports.hpp" "include/VG_Engine/Engine.hpp" "Display/DisplayManagement.cpp" "Display/DisplaysAPI.hpp" "MetaHeader.hpp")
add_dependencies(${MODULE_NAME} glfw STB_LIB)
target_link_libraries(${MODULE_NAME} glfw STB_LIB ${VULKAN_LIB_LIST})

target_compile_definitions("${MODULE_NAME}" PRIVATE VG_BUILD_LIBRARY)

set_target_properties(${MODULE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/
        )
