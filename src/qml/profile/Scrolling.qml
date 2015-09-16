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

import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ColumnLayout {
    anchors {
        fill: parent
        margins: 8
    }
    spacing: 6

    CheckBox {
        text: qsTr("Show scrollbar")
    }

    CheckBox {
        text: qsTr("Scroll on output")
    }

    RowLayout {
        CheckBox {
            id: historyLimited
            text: qsTr("Limit scrollback to:")
            onCheckedChanged: {
                if (checked)
                    historyLimitedTo.forceActiveFocus();
            }
        }

        SpinBox {
            id: historyLimitedTo
            enabled: historyLimited.checked

            Layout.minimumWidth: 100
        }
    }

    Item {
        Layout.fillHeight: true
    }
}
