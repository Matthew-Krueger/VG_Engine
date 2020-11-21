set(MODULE_NAME VKGame)

add_executable(${MODULE_NAME} Test.cpp)
add_dependencies(${MODULE_NAME} VG_Engine)
target_link_libraries(${MODULE_NAME} VG_Engine)

set_target_properties(${MODULE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/
        )
