/****************************************************************************
 * This file is part of Terminal.
 *
 * Copyright (C) 2010-2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>

#include "config.h"
#include "register_qml_types.h"
#if 0
#include "windowcontroller.h"
#else
#include "terminal_item.h"
#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setApplicationName("Terminal");
    app.setApplicationVersion(TERMINAL_VERSION);
    app.setOrganizationDomain("maui-project.org");
    app.setOrganizationName("Hawaii");

    register_qml_types();

#if 0
    WindowController *controller = new WindowController();
    controller->create();
#else
    QQuickView view(QUrl("qrc:/qml/yat_declarative/main.qml"));
    qobject_cast<TerminalItem *>(view.rootObject())->createScreen(view.engine());

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();
#endif

    return app.exec();
}
