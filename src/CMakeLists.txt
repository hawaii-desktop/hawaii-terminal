include_directories(${VibeWidgets_INCLUDE_DIRS})

include(CheckFunctionExists)
check_function_exists(updwtmpx HAVE_UPDWTMPX)

set(KB_LAYOUT_DIR ${CMAKE_INSTALL_FULL_DATADIR}/terminal/kb-layouts)
message(STATUS "Keyboard layouts will be installed in: ${KB_LAYOUT_DIR}")

set(COLOR_SCHEMES_DIR ${CMAKE_INSTALL_FULL_DATADIR}/terminal/color-schemes)
message(STATUS "Color schemes will be insatlled in: ${COLOR_SCHEMES_DIR}")

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
    lib/TerminalCharacterDecoder.cpp
    lib/TerminalDisplay.cpp
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

add_executable(hawaii-terminal ${SOURCES} ${UI_FILES})
qt5_use_modules(hawaii-terminal Widgets)
target_link_libraries(hawaii-terminal ${VibeWidgets_LIBRARIES})

install(FILES hawaii-terminal.desktop
    DESTINATION ${CMAKE_INSTALL_APPLICATIONSDIR})
install(TARGETS hawaii-terminal
    DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY lib/kb-layouts/
    DESTINATION ${KB_LAYOUT_DIR} FILES_MATCHING PATTERN "*.keytab" )
install(DIRECTORY lib/color-schemes/
    DESTINATION ${COLOR_SCHEMES_DIR} FILES_MATCHING PATTERN "*.*schem*")
