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

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

Dialog {
    property alias title: textField.text

    id: renameDialog
    title: qsTr("Rename")
    modality: Qt.WindowModal
    standardButtons: StandardButton.Cancel | StandardButton.Ok
    onVisibleChanged: {
        if (visible)
            textField.forceActiveFocus();
    }

    ColumnLayout {
        width: parent ? parent.width : 100
        spacing: 6

        RowLayout {
            spacing: 6

            Label {
                text: qsTr("Title:")
            }

            TextField {
                id: textField
                onEditingFinished: renameDialog.click(StandardButton.Ok)

                Layout.alignment: Qt.AlignRight
            }
        }
    }
}
