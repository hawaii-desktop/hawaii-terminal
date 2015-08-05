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

import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

SplitView {
    property alias terminal: terminalHolder.terminal
    property alias session: terminalHolder.session
    property bool splitted: false

    id: splitter

    TerminalHolder {
        id: terminalHolder
    }

    Layout.minimumWidth: 100
    Layout.minimumHeight: 100

    function createTerminal() {
        var component = Qt.createComponent("TerminalLayout.qml");
        return component.createObject(splitter);
    }

    function splitHorizontally() {
        var term;

        if (!splitter.splitted) {
            splitter.orientation = Qt.Horizontal;
            terminalHolder.Layout.minimumWidth = 100;
            terminalHolder.Layout.maximumWidth = terminalHolder.width / 2;
            term = createTerminal();
            splitter.addItem(term);
            splitter.splitted = true;
            terminalHolder.Layout.maximumWidth = 10000000;
        } else if (splitter.orientation == Qt.Horizontal) {
            term = createTerminal();
            splitter.addItem(term);
        } else {

        }
    }

    function splitVertically() {
        var term;

        if (!splitter.splitted) {
            splitter.orientation = Qt.Vertical;
            terminalHolder.Layout.minimumHeight = 100;
            terminalHolder.Layout.maximumHeight = terminalHolder.height / 2;
            term = createTerminal();
            splitter.addItem(term);
            splitter.splitted = true;
            terminalHolder.Layout.maximumHeight = 10000000;
        } else if (splitter.orientation == Qt.Vertical) {
            term = createTerminal();
            splitter.addItem(term);
        } else {

        }
    }

    function collapse() {
        splitter.removeItem(splitter);
    }
}
