include_directories(
    ${VibeWidgets_INCLUDE_DIRS}
)

add_definitions(-DHAVE_POSIX_OPENPT)
#add_definitions(-DHAVE_GETPT)
add_definitions(${VibeWidgets_DEFINITIONS})

set(TERMWIDGET_SOURCES
    lib/terminalcharacterdecoder.cpp
    lib/keyboardtranslator.cpp
    lib/screen.cpp
    lib/history.cpp
    lib/blockarray.cpp
    lib/wcwidth.cpp
    lib/screenwindow.cpp
    lib/emulation.cpp
    lib/vt102emulation.cpp
    lib/terminaldisplay.cpp
    lib/filter.cpp
    lib/pty.cpp
    lib/kpty.cpp
    lib/k3process.cpp
    lib/k3processcontroller.cpp
    lib/session.cpp
    lib/shellcommand.cpp
    lib/termwidget.cpp
)

set(TERMWIDGET_HEADERS
    lib/terminalcharacterdecoder.h
    lib/character.h
    lib/charactercolor.h
    lib/keyboardtranslator.h
    lib/extendeddefaulttranslator.h
    lib/screen.h
    lib/history.h
    lib/blockarray.h
    lib/wcwidth.h
    lib/screenwindow.h
    lib/emulation.h
    lib/vt102emulation.h
    lib/terminaldisplay.h
    lib/filter.h
    lib/linefont.h
    lib/pty.h
    lib/kpty.h
    lib/kpty_p.h
    lib/k3process.h
    lib/k3processcontroller.h
    lib/session.h
    lib/shellcommand.h
    lib/termwidget.h
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

add_executable(Terminal ${SOURCES} ${UI_FILES})
set_target_properties(Terminal PROPERTIES COMPILE_FLAGS "-fPIC")
target_link_libraries(Terminal ${VibeWidgets_LIBRARIES})

install(FILES terminal.desktop DESTINATION ${CMAKE_INSTALL_APPSDIR})
install(TARGETS Terminal DESTINATION ${CMAKE_INSTALL_PROGSDIR})
