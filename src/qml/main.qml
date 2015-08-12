/****************************************************************************
 * This file is part of Terminal.
 *
 * Copyright (C) 2013-2015 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

import QtQuick 2.1
import QtQuick.Window 2.1
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.1

ApplicationWindow {
    id: terminalWindow
    title: qsTr("Terminal")
    minimumWidth: 800
    minimumHeight: 600
    visible: true

    MessageDialog {
        id: errorDialog
        modality: Qt.WindowModal
        title: qsTr("Error")
        icon: StandardIcon.Critical
    }

    TerminalSettings {
        id: settings
    }

    TerminalComponent {
        id: terminalComponent
    }

    TabView {
        id: tabs
        anchors.fill: parent
        tabsVisible: count > 1
        onCurrentIndexChanged: getTab(currentIndex).children[0].terminal.forceActiveFocus()
        onCountChanged: {
            // Quit when the last tab is closed
            if (count == 0)
                Qt.quit();
        }

        Tab {
            title: qsTr("Shell %1").arg(1)

            TerminalComponent {}

            //onLoaded: title = item.session.title || item.session.initialWorkingDirectory
        }

        function addNewTab(component) {
            tabs.insertTab(tabs.count, qsTr("Shell %1").arg(tabs.count + 1), component);
            tabs.currentIndex = tabs.count - 1;
        }

        function removeTabWithSession(session) {
            var i, currentTab;
            for (i = 0; i < count; i++) {
                currentTab = getTab(i);
                if (currentTab.children.length == 0)
                    continue;
                if (currentTab.children[0].session == session) {
                    removeTab(i);
                    return;
                }
            }
        }
    }

    function newWindow() {
        var component;

        var finishNewWindow = function() {
            if (component.status == Component.Ready) {
                var window = component.createObject(null);
                if (window == null)
                    console.error("Error creating a new window");
            } else if (component.status == Component.Error) {
                console.error("Error loading component to create a new window:", component.errorString());
                errorMessage(qsTr("Unable to create a new window"),
                             qsTr("Terminal is unable to create a new window for an internal error.\n" +
                                  "Please try again and in case this happens again report this issue."),
                             qsTr("Error reported during component creation: %1").arg(component.errorString()));
            }
        };

        component = Qt.createComponent("main.qml");
        if (component.status == Component.Ready)
            finishNewWindow();
        else
            component.statusChanged.connect(finishNewWindow);
    }

    function errorMessage(text, informative, details) {
        errorDialog.text = text;
        errorDialog.informativeText = informative;
        errorDialog.detailedText = details;
        errorDialog.open();
    }
}
