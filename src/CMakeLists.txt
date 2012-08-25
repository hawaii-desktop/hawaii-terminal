include_directories(${VibeWidgets_INCLUDE_DIRS})

#check_function_exists(updwtmpx HAVE_UPDWTMPX)
#if (HAVE_UPDWTMPX)
#    add_definitions(-DHAVE_UPDWTMPX)
#endif()

add_definitions(${VibeWidgets_DEFINITIONS})

set(KB_LAYOUT_DIR ${CMAKE_INSTALL_FULL_DATADIR}/terminal/kb-layouts)
message(STATUS "Keyboard layouts will be installed in: ${KB_LAYOUT_DIR}")

set(COLORSCHEMES_DIR ${CMAKE_INSTALL_FULL_DATADIR}/terminal/color-schemes)
message(STATUS "Color schemes will be insatlled in: ${COLORSCHEMES_DIR}")

configure_file(config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

set(TERMWIDGET_SOURCES
    lib/BlockArray.cpp
    lib/ColorScheme.cpp
    lib/Emulation.cpp
    lib/Filter.cpp
    lib/History.cpp
    lib/KeyboardTranslator.cpp
    lib/konsole_wcwidth.cpp
    lib/kprocess.cpp
    lib/kpty.cpp
    lib/kptydevice.cpp
    lib/kptyprocess.cpp
    lib/Pty.cpp
    lib/qtermwidget.cpp
    lib/Screen.cpp
    lib/ScreenWindow.cpp
    lib/Session.cpp
    lib/ShellCommand.cpp
    lib/terminalCharacterDecoder.cpp
    lib/terminalDisplay.cpp
    lib/tools.cpp
    lib/Vt102Emulation.cpp
)

set(SOURCES
    mainwindow.cpp
    main.cpp
    ${TERMWIDGET_SOURCES}
)

set(HEADERS
    mainwindow.h
)

set(UI_SOURCES
    mainwindow.ui
)

qt5_wrap_ui(UI_FILES ${UI_SOURCES})

add_executable(terminal ${SOURCES} ${UI_FILES})
set_target_properties(terminal PROPERTIES COMPILE_FLAGS ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS})
target_link_libraries(terminal ${VibeWidgets_LIBRARIES})

install(FILES terminal.desktop DESTINATION ${CMAKE_INSTALL_APPSDIR})
install(TARGETS terminal DESTINATION ${CMAKE_INSTALL_PROGSDIR})

install(DIRECTORY lib/kb-layouts/ DESTINATION ${KB_LAYOUT_DIR} FILES_MATCHING PATTERN "*.keytab" )
install(DIRECTORY lib/color-schemes/ DESTINATION ${COLORSCHEMES_DIR} FILES_MATCHING PATTERN "*.*schem*")
