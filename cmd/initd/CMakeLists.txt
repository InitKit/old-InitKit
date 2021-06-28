FlexCXXComp(idb_parse.l)
LemonCXXComp(idb_parse.y)

add_executable(initd main.cc idb_readline.cc idb.cc
  ${CMAKE_CURRENT_BINARY_DIR}/idb_parse.tab.cc ${CMAKE_CURRENT_BINARY_DIR}/idb_parse.l.cc)
target_include_directories(initd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/vendor/lemon)
target_link_libraries(initd ik-internal PkgConfig::Readline)