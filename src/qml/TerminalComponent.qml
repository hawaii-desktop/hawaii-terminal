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
import Hawaii.Terminal.QMLTermWidget 1.0

Component {
    QMLTermWidget {
        signal sessionFinished(var session);

        id: terminal
        width: parent.width
        height: parent.height
        font.family: settings.fontStyle
        font.pointSize: settings.fontSize
        colorScheme: settings.colorScheme
        session: QMLTermSession {
            id: terminalSession
            initialWorkingDirectory: "$HOME"
            onFinished: tabs.removeTabWithSession(terminalSession)
        }

        Keys.onPressed: shortcutsHandler.handle(event)

        ShortcutsHandler {
            id: shortcutsHandler
        }

        QMLTermScrollbar {
            z: parent.z + 2
            terminal: parent
            width: 20

            Rectangle {
                anchors.fill: parent
                color: "orange"
            }
        }

        Component.onCompleted: {
            terminalSession.startShellProgram();
            forceActiveFocus();
        }
    }
}
