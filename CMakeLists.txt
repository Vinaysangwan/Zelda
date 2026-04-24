cmake_minimum_required(VERSION 3.28)
project(Zelda)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME})

# pch
target_precompile_headers(${PROJECT_NAME} PRIVATE include/pch.hpp)

# include directories
target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/vendor/raylib/include
  ${CMAKE_SOURCE_DIR}/vendor/entt
)

# sub directories
add_subdirectory(src)

# libs
target_link_libraries(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/vendor/raylib/lib/raylib.lib
  winmm
)
