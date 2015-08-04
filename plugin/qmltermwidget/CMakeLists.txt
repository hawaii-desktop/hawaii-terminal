include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR} lib src
)

set(PLUGIN_DIR QMLTermWidget)
add_definitions(-DHAVE_POSIX_OPENPT -DHAVE_SYS_TIME_H -DHAVE_UPDWTMPX)
add_definitions(-DQ_WS_UBUNTU)

set(qmltermwidget_SRCS
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

add_library(qmltermwidget MODULE
    ${qmltermwidget_SRCS}
)

qt5_use_modules(qmltermwidget Gui Qml Quick Widgets)

# Copy the plugin, the qmldir file and other assets to the build dir for running in QtCreator
if(NOT "${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
    add_custom_target(qmltermwidget-qmldir ALL
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/src/qmldir ${CMAKE_CURRENT_BINARY_DIR}/../${PLUGIN_DIR}
        DEPENDS ${QMLFILES}
    )
    add_custom_target(qmltermwidget-layouts-schemes ALL
        COMMAND cp -a ${CMAKE_CURRENT_SOURCE_DIR}/lib/color-schemes ${CMAKE_CURRENT_BINARY_DIR}/../${PLUGIN_DIR}
        COMMAND cp -a ${CMAKE_CURRENT_SOURCE_DIR}/lib/kb-layouts ${CMAKE_CURRENT_BINARY_DIR}/../${PLUGIN_DIR}
        DEPENDS ${QMLFILES}
    )
    add_custom_command(TARGET qmltermwidget POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/../${PLUGIN_DIR}
        COMMENT "Creating plugin directory layout in the build dir"
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:qmltermwidget> ${CMAKE_CURRENT_BINARY_DIR}/../${PLUGIN_DIR}
        COMMENT "Copying to output directory"
    )
    add_custom_target(qmltermwidget-qmlfiles ALL
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/src/QMLTermScrollbar.qml ${CMAKE_CURRENT_BINARY_DIR}/../${PLUGIN_DIR}
        DEPENDS ${QMLFILES}
    )
endif(NOT "${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")


install(TARGETS qmltermwidget DESTINATION ${QT_IMPORTS_DIR}/${PLUGIN_DIR})
install(FILES src/qmldir DESTINATION ${QT_IMPORTS_DIR}/${PLUGIN_DIR})
install(DIRECTORY lib/color-schemes DESTINATION ${QT_IMPORTS_DIR}/${PLUGIN_DIR})
install(DIRECTORY lib/kb-layouts DESTINATION ${QT_IMPORTS_DIR}/${PLUGIN_DIR})
install(FILES src/QMLTermScrollbar.qml DESTINATION ${QT_IMPORTS_DIR}/${PLUGIN_DIR})
