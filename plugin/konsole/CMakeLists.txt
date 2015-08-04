include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(PLUGIN_DIR org/kde/konsole)
add_definitions(-DHAVE_POSIX_OPENPT -DHAVE_SYS_TIME_H -DHAVE_UPDWTMPX)
add_definitions(-DQ_WS_UBUNTU)

set(konsole_SRCS
    BlockArray.cpp
    BlockArray.h
    CharacterColor.h
    Character.h
    ColorScheme.cpp
    ColorScheme.h
    ColorTables.h
    DefaultTranslatorText.h
    Emulation.cpp
    Emulation.h
    ExtendedDefaultTranslator.h
    Filter.cpp
    Filter.h
    History.cpp
    History.h
    KeyboardTranslator.cpp
    KeyboardTranslator.h
    konsole_wcwidth.cpp
    konsole_wcwidth.h
    kprocess.cpp
    kprocess.h
    kpty.cpp
    kptydevice.cpp
    kptydevice.h
    kpty.h
    kpty_p.h
    kptyprocess.cpp
    kptyprocess.h
    ksession.cpp
    ksession.h
    LineFont.h
    plugin.cpp
    plugin.h
    Pty.cpp
    Pty.h
    Screen.cpp
    Screen.h
    ScreenWindow.cpp
    ScreenWindow.h
    Session.cpp
    Session.h
    ShellCommand.cpp
    ShellCommand.h
    TerminalCharacterDecoder.cpp
    TerminalCharacterDecoder.h
    TerminalDisplay.cpp
    TerminalDisplay.h
    tools.cpp
    tools.h
    Vt102Emulation.cpp
    Vt102Emulation.h
)

add_library(kdekonsole MODULE
    ${konsole_SRCS}
)

qt5_use_modules(kdekonsole Gui Qml Quick Widgets)

# Copy the plugin, the qmldir file and other assets to the build dir for running in QtCreator
if(NOT "${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
    add_custom_target(konsole-qmldir ALL
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/qmldir ${CMAKE_CURRENT_BINARY_DIR}/../${PLUGIN_DIR}
        DEPENDS ${QMLFILES}
    )
    add_custom_target(konsole-layouts-schemes ALL
        COMMAND cp -a ${CMAKE_CURRENT_SOURCE_DIR}/assets/color-schemes ${CMAKE_CURRENT_BINARY_DIR}/../${PLUGIN_DIR}
        COMMAND cp -a ${CMAKE_CURRENT_SOURCE_DIR}/assets/kb-layouts ${CMAKE_CURRENT_BINARY_DIR}/../${PLUGIN_DIR}
        DEPENDS ${QMLFILES}
    )
    add_custom_command(TARGET kdekonsole POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/../${PLUGIN_DIR}
        COMMENT "Creating plugin directory layout in the build dir"
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:kdekonsole> ${CMAKE_CURRENT_BINARY_DIR}/../${PLUGIN_DIR}
        COMMENT "Copying to output directory"
    )
endif(NOT "${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")


install(TARGETS kdekonsole DESTINATION ${QT_IMPORTS_DIR}/${PLUGIN_DIR})
install(FILES qmldir DESTINATION ${QT_IMPORTS_DIR}/${PLUGIN_DIR})
install(DIRECTORY assets/color-schemes DESTINATION ${QT_IMPORTS_DIR}/${PLUGIN_DIR})
install(DIRECTORY assets/kb-layouts DESTINATION ${QT_IMPORTS_DIR}/${PLUGIN_DIR})

