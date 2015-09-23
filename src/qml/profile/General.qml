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
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.1

GridLayout {
    anchors {
        fill: parent
        margins: 8
    }
    columns: 2
    rows: 1
    rowSpacing: 6
    columnSpacing: 6

    FontDialog {
        id: fontDialog
        title: qsTr("Choose custom font")
        font: Qt.font({family: terminalWindow.profile.fontStyle, pointSize: terminalWindow.profile.fontSize, weight: Font.Normal})
        monospacedFonts: true
        nonScalableFonts: false
        proportionalFonts: false
        scalableFonts: true
        onAccepted: {
            terminalWindow.profile.fontStyle = font.family;
            terminalWindow.profile.fontSize = font.pointSize;
        }
    }

    Label {
        text: qsTr("Profile")
    }

    TextField {
        id: profileTextField

        Layout.minimumWidth: 350
    }

    GroupBox {
        title: qsTr("Text Appearance")

        ColumnLayout {
            spacing: 6

            RowLayout {
                spacing: 6

                CheckBox {
                    id: customFontCheckBox
                    text: qsTr("Custom font")
                }

                Button {
                    text: "%1 %2".arg(fontDialog.font.family).arg(fontDialog.font.pointSize)
                    enabled: customFontCheckBox.checked
                    onClicked: fontDialog.open()
                }
            }
        }

        Layout.columnSpan: 2
    }

    Item {
        Layout.fillHeight: true
    }
}
