#include <reproc++/reproc.hpp>  // not used yet; ensures link correctness
#include <spdlog/spdlog.h>
#include <string>
#include "flygdb/config.hpp"

namespace flygdb {
std::string hello() {
  spdlog::info("flygdb ready. gdb path={}, host={}, port={}",
               FLYGDB_GDB_PATH, FLYGDB_DEFAULT_HOST, FLYGDB_DEFAULT_PORT);
  return std::string("gdb: ") + FLYGDB_GDB_PATH +
         "  target " + FLYGDB_DEFAULT_HOST + ":" + FLYGDB_DEFAULT_PORT;
}
} // namespace flygdb
