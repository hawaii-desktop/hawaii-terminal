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

ApplicationWindow {
    id: terminalWindow
    title: qsTr("Terminal")
    minimumWidth: 800
    minimumHeight: 600
    visible: true

    TerminalSettings {
        id: settings
    }

    TerminalComponent {
        id: terminalComponent
    }

    RenameDialog {
        id: renameDialog
        onAccepted: tabs.getTab(tabs.currentIndex).title = renameDialog.title
    }

    TabView {
        id: tabs
        anchors.fill: parent
        tabsVisible: count > 1
        onCurrentIndexChanged: getTab(currentIndex).children[0].terminal.forceActiveFocus()
        onCountChanged: {
            // Close this window when the last tab is closed or quit
            // if there are no other windows open
            if (count == 0) {
                if (terminalApp.windowCount === 0)
                    Qt.quit();
                else
                    terminalWindow.close();
            }
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

        function renameCurrentTab() {
            renameDialog.title = getTab(currentIndex).title;
            renameDialog.open();
        }
    }
}
