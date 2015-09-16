/****************************************************************************
 * This file is part of Terminal.
 *
 * Copyright (C) 2015 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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
import QtQuick.Controls 1.1

Menu {
    MenuItem {
        text: qsTr("&Copy")
        shortcut: "Ctrl+Shift+C"
        onTriggered: terminal.copyClipboard()
    }

    MenuItem {
        text: qsTr("&Paste")
        shortcut: "Ctrl+Shift+V"
        onTriggered: terminal.pasteClipboard()
    }

    MenuItem {
        text: qsTr("Open File Manager")
        enabled: false
        onTriggered: Qt.openUrlExternally()
    }

    MenuSeparator {}

    MenuItem {
        text: qsTr("&New Tab")
        //shortcut: "Ctrl+Shift+T"
        onTriggered: tabs.addNewTab(terminalComponent)
    }

    MenuItem {
        text: qsTr("C&lose Tab")
        //shortcut: "Ctrl+Shift+W"
        onTriggered: tabs.removeTabWithSession(terminal.session)
    }

    MenuSeparator {}

    MenuItem {
        text: qsTr("Split Horizontally")
        onTriggered: splitter.splitHorizontally()
    }

    MenuItem {
        text: qsTr("Split Vertically")
        onTriggered: splitter.splitVertically()
    }

    MenuItem {
        text: qsTr("Collapse Subterminal")
        onTriggered: splitter.collapse()
    }

    MenuSeparator {}

    MenuItem {
        text: qsTr("Edit Current P&rofile...")
        onTriggered: terminalApp.editCurrentProfile()
    }
}
