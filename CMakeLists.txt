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
# 指定头文件查找目录
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/fltk-dist-1.3.8/include")



link_libraries(${LCM_LDFLAGS})
LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/fltk-dist-1.3.8/lib/Linux-release")

# Create executables for the example programs.

add_executable(listener "listener.cpp")
add_dependencies(listener exlcm)

TARGET_LINK_LIBRARIES(
            listener
            PRIVATE
            fltk # 链接的静态库名称，这里只需要写fltk，在运行时自动查找.a/.lib
            X11 # Linux环境需要指定X11以及dl两个库才能正常显示
            dl
            Xft
            fontconfig
            Xrender
            Xfixes
            Xcursor
            Xinerama
            pthread
            Xext
            X11
            m
            dl
    )





