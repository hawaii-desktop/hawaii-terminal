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

MouseArea {
    signal mouseMoveDetected(int x, int y, int button, int buttons, int modifiers)
    signal doubleClickDetected(int x, int y, int button, int buttons, int modifiers)
    signal mousePressDetected(int x, int y, int button, int buttons, int modifiers)
    signal mouseReleaseDetected(int x, int y, int button, int buttons, int modifiers)
    signal mouseWheelDetected(int x, int y, int buttons, int modifiers, point angleDelta)

    signal alternateAction(int x, int y)

    anchors.fill: parent
    acceptedButtons: Qt.AllButtons
    onDoubleClicked: {
        doubleClickDetected(mouse.x, mouse.y, mouse.button, mouse.buttons, mouse.modifiers);
    }
    onPositionChanged: {
        mouseMoveDetected(mouse.x, mouse.y, mouse.button, mouse.buttons, mouse.modifiers);
    }
    onPressed: {
        // Do not handle the right click if the terminal needs them.
        if (mouse.button === Qt.RightButton && !terminal.terminalUsesMouse) {
            alternateAction(mouse.x, mouse.y);
        } else {
            terminal.forceActiveFocus();
            mousePressDetected(mouse.x, mouse.y, mouse.button, mouse.buttons, mouse.modifiers);
        }
    }
    onReleased: {
        mouseReleaseDetected(mouse.x, mouse.y, mouse.button, mouse.buttons, mouse.modifiers);
    }
    onWheel: {
        mouseWheelDetected(wheel.x, wheel.y, wheel.buttons, wheel.modifiers, wheel.angleDelta);
    }
}
