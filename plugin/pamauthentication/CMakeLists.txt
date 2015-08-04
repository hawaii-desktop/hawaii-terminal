include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(SOURCES
    pamauthentication.cpp
    pamauthentication.h
    pamauthentication_plugin.cpp
    pamauthentication_plugin.h
)

add_library(pamauthentication SHARED ${SOURCES})
target_link_libraries(pamauthentication
                      Qt5::DBus
                      Qt5::Gui
                      Qt5::Qml
                      Qt5::Quick
                      Qt5::Widgets
                      pam)

install(TARGETS pamauthentication
        DESTINATION ${QML_INSTALL_DIR}/Hawaii/Terminal/PamAuthentication)
install(FILES qmldir
        DESTINATION ${QML_INSTALL_DIR}/Hawaii/Terminal/PamAuthentication)
