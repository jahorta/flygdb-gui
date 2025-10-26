add_library(flygdb STATIC
  src/flygdb_stub.cpp
)

target_include_directories(flygdb
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/../..  # for generated/flygdb/config.hpp
)

target_link_libraries(flygdb
  PUBLIC
    spdlog::spdlog_header_only
  PRIVATE
    reproc++          # we’ll use it when we spawn gdb-multiarch
)

target_compile_definitions(flygdb PUBLIC FLYGDB_VERSION="0.1.0")
