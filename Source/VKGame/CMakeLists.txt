set(MODULE_NAME VKGame)

add_executable(${MODULE_NAME} Test.cpp)
add_dependencies(${MODULE_NAME} VG_Engine)
target_link_libraries(${MODULE_NAME} VG_Engine)