list(APPEND M4_SOURCES system/dbstab.m4 system/cpstab.m4)

foreach(m4_source IN LISTS M4_SOURCES)
    remove_chars_end(m4_source m4_out 3)
    build_m4(${m4_source} ${m4_out})
    list(APPEND M4_OUTPUTS ${CMAKE_CURRENT_BINARY_DIR}/${m4_out})
endforeach()

add_custom_target(m4_generate ALL DEPENDS ${M4_OUTPUTS})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/system/dbstab
    DESTINATION ${IK_PKG_SYSCONFDIR}/system)