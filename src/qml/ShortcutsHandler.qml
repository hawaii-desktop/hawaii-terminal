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
import QtQuick.Window 2.0

Item {
    function handle(event) {
        // Full screen
        if (event.key == Qt.Key_F11) {
            event.accepted = true;
            if (terminalWindow.visibility == Window.FullScreen)
                terminalWindow.visibility = Window.Windowed;
            else
                terminalWindow.visibility = Window.FullScreen;
        }

        if (event.modifiers & Qt.ControlModifier) {
            if (event.modifiers & Qt.ShiftModifier) {
                // Always accept Ctrl+Shift as a shortcut
                event.accepted = true;

                switch (event.key) {
                // Tabs
                case Qt.Key_N:
                    terminalApp.newWindow();
                    break;
                case Qt.Key_T:
                    tabs.addNewTab(terminalComponent);
                    break;
                case Qt.Key_W:
                    tabs.removeTabWithSession(terminal.session);
                    break;
                case Qt.Key_Q:
                    for (var i = tabs.count - 1; i >= 0; i--)
                        tabs.removeTab(i);
                    break;
                // Clipboard
                case Qt.Key_C:
                    terminal.copyClipboard();
                    break;
                case Qt.Key_V:
                    terminal.pasteClipboard();
                    break;
                default:
                    break;
                }
            }

            switch (event.key) {
            // Zoom in
            case Qt.Key_Plus:
                event.accepted = true;
                settings.fontSize = Math.min(settings.fontSize + 1, settings.maxFontSize);
                break;
            // Zoom out
            case Qt.Key_Minus:
                event.accepted = true;
                settings.fontSize = Math.max(settings.fontSize - 1, settings.minFontSize);
                break;
            // Normal size
            case Qt.Key_0:
                event.accepted = true;
                settings.fontSize = settings.defaultFontSize;
                break;
            }
        } else if (event.modifiers & Qt.ShiftModifier) {
            switch (event.key) {
            // Tab switching
            case Qt.Key_Left:
                event.accepted = true;
                if (tabs.currentIndex > 0)
                    tabs.currentIndex--;
                else
                    tabs.currentIndex = tabs.count - 1;
                break;
            case Qt.Key_Right:
                event.accepted = true;
                tabs.currentIndex = (tabs.currentIndex + 1) % tabs.count
                break;
            default:
                break;
            }
        }
    }
}
