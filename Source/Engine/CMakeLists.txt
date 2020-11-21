set(MODULE_NAME ${PROJECT_NAME})

add_library(${MODULE_NAME} SHARED Test.cpp)
add_dependencies(${MODULE_NAME} glfw STB_LIB)
target_link_libraries(${MODULE_NAME} glfw STB_LIB)