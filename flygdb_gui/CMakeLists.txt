add_executable(flygdb_gui
  src/main.cpp
)

target_link_libraries(flygdb_gui
  PRIVATE
    flygdb
    ${FLTK_TARGET}
    spdlog::spdlog_header_only
)

# On Windows, hide console for a cleaner GUI app; drop this if you want console logs.
if(WIN32)
  set_target_properties(flygdb_gui PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
