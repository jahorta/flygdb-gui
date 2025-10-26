cmake_minimum_required(VERSION 3.26)
project(FlyGdbGui LANGUAGES CXX)

# ---- Global language/compile settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Make sure CMake honors the MSVC runtime library property
cmake_policy(SET CMP0091 NEW)


if(MSVC)
  add_compile_options(/permissive- /W4 /EHsc)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

option(FLYGDB_ENABLE_LTO "Enable IPO/LTO for Release where supported" ON)

# ---- Cache-configurable defaults (no env/package managers)
set(FLYGDB_GDB_PATH "gdb-multiarch" CACHE STRING "Path to gdb-multiarch executable")
set(FLYGDB_DEFAULT_HOST "127.0.0.1" CACHE STRING "Default remote host")
set(FLYGDB_DEFAULT_PORT "3263" CACHE STRING "Default remote port")

# ---- Configure a tiny config header available to all targets
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/flygdb/include/flygdb/config.hpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/generated/flygdb/config.hpp
  @ONLY
)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/generated)

# ---- Third-party (submodules) ----------------------------------------------

# FLTK (build as subproject; turn off extras in presets)
set(FLTK_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(FLTK_BUILD_TEST OFF CACHE BOOL "" FORCE)
set(OPTION_USE_SYSTEM_LIBJPEG OFF CACHE BOOL "" FORCE)
set(OPTION_USE_SYSTEM_ZLIB OFF CACHE BOOL "" FORCE)
set(OPTION_USE_SYSTEM_LIBPNG OFF CACHE BOOL "" FORCE)
add_subdirectory(third_party/fltk)

# spdlog (header-only)
add_subdirectory(third_party/spdlog)

# reproc (C & C++ libs)
set(REPROC++ ON CACHE BOOL "" FORCE)
add_subdirectory(third_party/reproc)

# Helper var so we don’t care how FLTK names its target
if(TARGET FLTK::FLTK)
  set(FLTK_TARGET FLTK::FLTK)
elseif(TARGET fltk)
  set(FLTK_TARGET fltk)
else()
  message(FATAL_ERROR "FLTK target not found after add_subdirectory()")
endif()

# ---- Subprojects
add_subdirectory(flygdb)
add_subdirectory(flygdb_gui)

# ---- IPO/LTO (optional)
if(FLYGDB_ENABLE_LTO)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT ipo_ok OUTPUT ipo_msg)
  if(ipo_ok)
    set_property(TARGET flygdb flygdb_gui PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
  endif()
endif()
