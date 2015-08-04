include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_definitions(-DHAVE_POSIX_OPENPT -DHAVE_SYS_TIME_H -DHAVE_UPDWTMPX)

set(SOURCES
    src/ksession.h
    src/ksession.cpp
    src/qmltermwidget_plugin.h
    src/qmltermwidget_plugin.cpp
    lib/BlockArray.h 
    lib/CharacterColor.h 
    lib/Character.h 
    lib/ColorScheme.h 
    lib/ColorTables.h 
    lib/DefaultTranslatorText.h 
    lib/Emulation.h 
    lib/ExtendedDefaultTranslator.h 
    lib/Filter.h 
    lib/History.h 
    lib/HistorySearch.h 
    lib/KeyboardTranslator.h 
    lib/konsole_wcwidth.h 
    lib/kprocess.h 
    lib/kptydevice.h 
    lib/kpty.h 
    lib/kpty_p.h 
    lib/kptyprocess.h 
    lib/LineFont.h 
    lib/Pty.h 
    lib/Screen.h 
    lib/ScreenWindow.h 
    lib/Session.h 
    lib/ShellCommand.h 
    lib/TerminalCharacterDecoder.h 
    lib/TerminalDisplay.h 
    lib/tools.h 
    lib/Vt102Emulation.h 
    lib/BlockArray.cpp 
    lib/ColorScheme.cpp 
    lib/Emulation.cpp 
    lib/Filter.cpp 
    lib/History.cpp 
    lib/HistorySearch.cpp 
    lib/KeyboardTranslator.cpp 
    lib/konsole_wcwidth.cpp 
    lib/kprocess.cpp 
    lib/kpty.cpp 
    lib/kptydevice.cpp 
    lib/kptyprocess.cpp 
    lib/Pty.cpp 
    lib/Screen.cpp 
    lib/ScreenWindow.cpp 
    lib/Session.cpp 
    lib/ShellCommand.cpp 
    lib/TerminalCharacterDecoder.cpp 
    lib/TerminalDisplay.cpp 
    lib/tools.cpp 
    lib/Vt102Emulation.cpp
)

add_library(qmltermwidget SHARED ${SOURCES})
target_link_libraries(qmltermwidget
                      Qt5::Gui
                      Qt5::Qml
                      Qt5::Quick
                      Qt5::Widgets)

install(TARGETS qmltermwidget
        DESTINATION ${QML_INSTALL_DIR}/Hawaii/Terminal/QMLTermWidget)
install(FILES src/qmldir
        DESTINATION ${QML_INSTALL_DIR}/Hawaii/Terminal/QMLTermWidget)
install(DIRECTORY lib/color-schemes
        DESTINATION ${QML_INSTALL_DIR}/Hawaii/Terminal/QMLTermWidget)
install(DIRECTORY lib/kb-layouts
        DESTINATION ${QML_INSTALL_DIR}/Hawaii/Terminal/QMLTermWidget)
install(FILES src/QMLTermScrollbar.qml
        DESTINATION ${QML_INSTALL_DIR}/Hawaii/Terminal/QMLTermWidget)
