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

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

Dialog {
    id: profileDialog
    title: qsTr("Edit Profile")
    modality: Qt.WindowModal
    contentItem: Item {
        implicitWidth: 600
        implicitHeight: 600

        ColumnLayout {
            anchors {
                fill: parent
                margins: 8
            }
            spacing: 6

            TabView {
                Tab {
                    title: qsTr("General")
                    source: "profile/General.qml"
                }

                Tab {
                    title: qsTr("Title")
                }

                Tab {
                    title: qsTr("Scrolling")
                    source: "profile/Scrolling.qml"
                }

                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            RowLayout {
                spacing: 6

                Item {
                    Layout.fillWidth: true
                }

                Button {
                    text: qsTr("Close")
                    onClicked: profileDialog.close()

                    Layout.alignment: Qt.AlignRight
                }

                Layout.fillWidth: true
            }
        }
    }
}
