configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/config.h"
    IMMEDIATE @ONLY)

set(SOURCES
    main.cpp
)

set(QM_SOURCES
    translations/it.ts
)

set(QRC_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/qml.qrc
)

#qt5_add_translation(QM_FILES ${QM_SOURCES})
qt5_add_resources(RESOURCES ${QRC_SOURCES})

add_executable(hawaii-terminal ${SOURCES} ${RESOURCES})
target_link_libraries(hawaii-terminal
                      Qt5::Qml
                      Qt5::Quick
                      Qt5::Widgets)

install(TARGETS hawaii-terminal
    DESTINATION ${CMAKE_INSTALL_BINDIR})
#install(FILES ${QM_FILES}
#    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-terminal/translations)
