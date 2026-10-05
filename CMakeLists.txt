cmake_minimum_required(VERSION 4.4.0)

project(cpp20test)

# Enable IAR Compiler extensions (-e)
set(CMAKE_CXX_EXTENSIONS ON)

# add the executable target
add_executable(cpp20test)

# Set C++20 standard
target_compile_features(cpp20test PRIVATE cxx_std_20)

# target sources
target_sources(cpp20test PRIVATE
  main.cpp
  foo.cpp
  foo2.cpp
)

# compiler options
target_compile_options(cpp20test PRIVATE
  --no_wrap_diagnostics
  --cpu=cortex-m4
  --no_rtti
  --libc++
)

# linker options
target_link_options(cpp20test PRIVATE
  --no_wrap_diagnostics
  --cpu=cortex-m4
  --semihosting
  --map .
)

# Setup TOOLKIT_DIR
cmake_path(GET CMAKE_CXX_COMPILER PARENT_PATH BIN_DIR)
cmake_path(GET BIN_DIR PARENT_PATH TOOLKIT_DIR)


# Generate an IAR-compatible compile database
add_custom_target(clangd_compile_commands ALL
  COMMAND ${TOOLKIT_DIR}/../common/bin/iarbuild${CMAKE_HOST_EXECUTABLE_SUFFIX}
    -E clangd_compile_commands
    --output $<TARGET_FILE_DIR:${PROJECT_NAME}>/compile_commands.json
    --build_dir ${CMAKE_CURRENT_BINARY_DIR}
    --configuration $<CONFIG>
    --parallel 4
  COMMENT "Generating $<TARGET_FILE_DIR:${PROJECT_NAME}>/compile_commands.json"
)