include_directories(
    ${CMAKE_SOURCE_DIR}/3rdparty/yat/backend
    ${CMAKE_SOURCE_DIR}/3rdparty/yat/yat_declarative
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/config.h"
    IMMEDIATE @ONLY)

set(YAT_BACKEND_SOURCES
    ${CMAKE_SOURCE_DIR}/3rdparty/yat/backend/yat_pty.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/yat/backend/text.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/yat/backend/parser.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/yat/backend/screen.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/yat/backend/line.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/yat/backend/color_palette.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/yat/backend/text_style.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/yat/backend/update_action.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/yat/backend/screen_data.cpp
)

set(YAT_DECLARATIVE_SOURCES
    ${CMAKE_SOURCE_DIR}/3rdparty/yat/yat_declarative/terminal_item.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/yat/yat_declarative/register_qml_types.cpp
)

set(SOURCES
    main.cpp
    ${YAT_BACKEND_SOURCES}
    ${YAT_DECLARATIVE_SOURCES}
)

set(QM_SOURCES
    translations/it.ts
)

set(QRC_SOURCES
#    ${CMAKE_SOURCE_DIR}/3rdparty/yat/yat_declarative/qml_sources.qrc
    terminal.qrc
)

#qt5_add_translation(QM_FILES ${QM_SOURCES})
qt5_add_resources(RESOURCES ${QRC_SOURCES})

add_executable(hawaii-terminal ${SOURCES} ${RESOURCES})
target_link_libraries(hawaii-terminal util)
qt5_use_modules(hawaii-terminal Gui Quick)

install(TARGETS hawaii-terminal
    DESTINATION ${CMAKE_INSTALL_BINDIR})
#install(FILES ${QM_FILES}
#    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-terminal/translations)
