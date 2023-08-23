cmake_minimum_required(VERSION 3.1)

project(cpp_project)

# Import LCM via pkgconfig.
find_package(PkgConfig REQUIRED)
find_package(RapidJSON)

pkg_check_modules(LCM REQUIRED lcm)

# Use lcm-gen to generate headers.
find_program(LCM_GEN_EXECUTABLE lcm-gen)
add_custom_target(exlcm
  COMMAND ${LCM_GEN_EXECUTABLE} -x *.lcm)
include_directories("${cpp_project_BINARY_DIR}")

# Everything from here on needs these flags.
include_directories(${LCM_INCLUDE_DIRS})
link_libraries(${LCM_LDFLAGS})

# Create executables for the example programs.

add_executable(listener "listener.cpp")
add_dependencies(listener exlcm)

add_executable(send_message "send_message.cpp")
add_dependencies(send_message exlcm)

