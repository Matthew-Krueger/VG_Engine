set(MODULE_NAME VG_Engine_Tester)

add_executable(${MODULE_NAME} TestMain.cpp PCH.hpp PCH.cpp TestGlobals.hpp WindowTests.cpp)
set_source_files_properties(TestMain.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
add_dependencies(${MODULE_NAME} VG_Engine)
target_link_libraries(${MODULE_NAME} VG_Engine)
target_include_directories(${MODULE_NAME} PRIVATE ../Engine/include)

target_precompile_headers(${MODULE_NAME} PRIVATE PCH.hpp)

set_target_properties(${MODULE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/
        )
