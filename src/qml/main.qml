/****************************************************************************
 * This file is part of Terminal.
 *
 * Copyright (C) 2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright (C) 2013 Jørgen Lind <jorgen.lind@gmail.com>
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
import Yat 1.0 as Yat

ApplicationWindow {
    id: terminalWindow
    title: qsTr("Terminal")
    minimumWidth: 640
    minimumHeight: 480

    Action {
        id: newTabAction
        shortcut: "Ctrl+Shift+T"
        onTriggered: tabView.addTerminalView()
    }

    Action {
        id: nextTabAction
        shortcut: "Ctrl+Alt+Right"
        onTriggered: tabView.currentIndex = (tabView.currentIndex + 1) % tabView.count
    }

    Action {
        id: previousTabAction
        shortcut: "Ctrl+Alt+Left"
        onTriggered: {
            if (tabView.currentIndex > 0)
                tabView.currentIndex--;
            else
                tabView.currentIndex = tabView.count - 1;
        }
    }

    TabView {
        id: tabView
        anchors.fill: parent
        tabsVisible: count > 1
        focus: true
        onCurrentIndexChanged: setCurrentTerminalView(tabView.currentIndex)

        Component {
            id: terminalScreenComponent

            Yat.Screen {}
        }

        function addTerminalView() {
            var tab = tabView.addTab("", terminalScreenComponent);
            tab.active = true;
            tab.title = Qt.binding(function() { return tab.item.screen.title; });
            tab.item.aboutToBeDestroyed.connect(destroyTab);
            tabView.currentIndex = tabView.count - 1;
        }

        function destroyTab(screenItem) {
            if (tabView.count == 1) {
                Qt.quit();
                return;
            }

            var i;
            for (i = 0; i < tabView.count; i++) {
                if (tabView.getTab(i).item === screenItem) {
                    if (i == 0)
                        tabView.currentIndex = 1;
                    tabView.getTab(i).item.parent = null;
                    tabView.removeTab(i);
                    break;
                }
            }
        }

        function setCurrentTerminalView(index) {
            terminalWindow.color = Qt.binding(function() { return tabView.getTab(index).item.screen.defaultBackgroundColor; });
            tabView.getTab(index).item.forceActiveFocus();
        }

        Component.onCompleted: {
            addTerminalView();
            setCurrentTerminalView(0);
            terminalWindow.visible = true;
        }
    }
}
