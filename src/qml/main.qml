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

import QtQuick 2.1
import QtQuick.Dialogs 1.1

QtObject {
    id: terminalApp

    property var errorDialog: MessageDialog {
        modality: Qt.WindowModal
        title: qsTr("Error")
        icon: StandardIcon.Critical
    }

    property var profileDialog: ProfileDialog {
        modality: Qt.WindowModal
    }

    property var model: ListModel {
        id: model
    }

    readonly property alias windowCount: model.count

    function newWindow() {
        var component;

        var finishNewWindow = function() {
            switch (component.status) {
            case Component.Ready:
                var window = component.createObject(null);
                if (window === null)
                    console.error("Error creating a new window");
                else
                    model.append({"window": window});
                break;
            case Component.Null:
            case Component.Error:
                console.error("Error loading component to create a new window:", component.errorString());
                errorMessage(qsTr("Unable to create a new window"),
                             qsTr("Terminal is unable to create a new window for an internal error.\n" +
                                  "Please try again and in case this happens again report this issue."),
                             qsTr("Error reported during component creation: %1").arg(component.errorString()));
                break;
            default:
                break;
            }
        };

        component = Qt.createComponent("MainWindow.qml");
        if (component.status !== Component.Loading)
            finishNewWindow();
        else
            component.statusChanged.connect(finishNewWindow);
    }

    function editCurrentProfile() {
        profileDialog.open();
    }

    function errorMessage(text, informative, details) {
        errorDialog.text = text ? text : "";
        errorDialog.informativeText = informative ? informative : "";
        errorDialog.detailedText = details ? details : "";
        errorDialog.open();
    }
}
