list(APPEND SRCS cjson_ex.cc)

if(PLATFORM_Linux)
    list(APPEND SRCS proc_lin.cc)
elseif(PLATFORM_BSD)
    list(APPEND SRCS proc_bsd.cc)
    list(APPEND LibKVM kvm)
else()
    message(FATAL_ERROR "No process utilities for this platform - please port.")
endif()

add_library(ik-internal ${SRCS})
target_include_directories(ik-internal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/head)
target_link_libraries(ik-internal initkit ik-cjson ${LibKVM})